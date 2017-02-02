
#include	"iextreme.h"
#include	<vector>
#include	"GameManager.h"
#include	"GameParam.h"
#include	"LevelManager.h"

//***************************************************************
//
//	LevelManagerクラス
//
//***************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

//	実体
LevelManager*	levelManager = nullptr;

#define	LEVEL_MAX	6

namespace
{
	//	ステータス送信
	namespace RECEIVE_STATUS
	{
		enum
		{
			ATTACK,
			DEFENSE,
			MAGIC_ATTACK,
			MAGIC_DEFENSE,
			SPEED,
			LIFE,
			ALL
		};
	}

	//	ステータスタイプ
	namespace STATUS_TYPE
	{
		enum
		{
			LEVEL,
			EXP,
			STATUS
		};
	}
	
	//	レベル情報
	struct SendLevelData
	{
		char com = SEND_COMMAND::STATUS_INFO;
		char statusType = STATUS_TYPE::LEVEL;
		char levelType;
		char level;

		SendLevelData( char levelType, char level ) :
			levelType( levelType ), level( level ){}
	};

	//	経験値情報
	struct SendExpData
	{
		char com = SEND_COMMAND::STATUS_INFO;
		char statusType = STATUS_TYPE::EXP;
		int	exp;

		SendExpData( int exp ) : exp(exp){}
	};

	//	全パラメータ情報
	struct SendAllStatusData
	{
		char com = SEND_COMMAND::STATUS_INFO;
		char statusType = STATUS_TYPE::STATUS;
		char paramType = SEND_STATUS::ALL;
		int attack;
		int defense;
		int magicAttack;
		int magicDefense;
		int life;
		float speed;
		SendAllStatusData(int attack, int defense, int magicAttack, int magicDefense, int life, float speed) :
			attack(attack), defense(defense),
			magicAttack(magicAttack), magicDefense(magicDefense), life(life), speed(speed) {}
	};

	//	各パラメータ情報
	struct SendStatusData
	{
		char com = SEND_COMMAND::STATUS_INFO;
		char statusType = STATUS_TYPE::STATUS;
		char paramType;
		float status;
		SendStatusData( char paramType, float status ) :
			paramType( paramType), status( status ){}
		SendStatusData( void ){}
	};
}


//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	LevelManager::LevelManager( void )
	{
		//	レベル情報初期化
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	経験値初期化
			levelInfo[p].exp = 1000;
			levelInfo[p].total_level = 0;

			//	各レベル初期化
			for ( int i = 0; i < LEVEL_TYPE::TYPE_MAX; i++ )
			{
				levelInfo[p].level[i] = 0;
			}
		}

		expData[ENEMY_EXP::WOLF] = 10;
		expData[ENEMY_EXP::MOFFU] = 5;
		expData[ENEMY_EXP::BIG] = 40;
	}

	//	デストラクタ
	LevelManager::~LevelManager( void )
	{

	}

//----------------------------------------------------------------------------------------------
//	動作関数
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

	//	レベル加算
	void	LevelManager::AddLevel( int id, char levelType )
	{
		//	レベル加算
		levelInfo[id].level[levelType]++;

		//	レベル上限設定
		if ( levelInfo[id].level[levelType] >= LEVEL_MAX )
		{
			//	上限設定
			levelInfo[id].level[levelType] = LEVEL_MAX;

			//	クラスチェンジ
			SendClassChange( id, levelType + 1 );
		}

		else
		{
			//	必要経験値分減算
			levelInfo[id].exp -= 30 + levelInfo[id].total_level * 5;
			levelInfo[id].total_level++;
			SendExp(id);
		}

		//	ステータス計算
		CulcStatus( id, levelType );
		SendMaxLife( id );
	}

	//	経験値計算
	void	LevelManager::CalcExp( int id, char enemyType )
	{
		//	経験値加算
		levelInfo[id].exp += expData[enemyType];

		//	下限設定
		if ( levelInfo[id].exp <= 0 )	levelInfo[id].exp = 0;
	}

	//	経験値計算
	void	LevelManager::CalcExpPlayer( int killer, int dead )
	{
		//	経験値加算
		levelInfo[killer].exp += levelInfo[dead].total_level * 10;

		//	下限設定
		if ( levelInfo[killer].exp <= 0 )	levelInfo[killer].exp = 0;
	}

	//	レベル送信
	void	LevelManager::SendLevel( int id, char levelType )
	{
		//	情報設定
		SendLevelData	sendLevelData( levelType, levelInfo[id].level[levelType] );

		//	情報送信
		gameParam->send( id, ( LPSTR )&sendLevelData, sizeof( sendLevelData ) );
	}

	//	経験値送信
	void	LevelManager::SendExp( int id )
	{
		SendExpData	sendExpData( levelInfo[id].exp );
		gameParam->send( id, ( LPSTR )&sendExpData, sizeof( sendExpData ) );
	}

	//	クラスチェンジ情報送信
	void	LevelManager::SendClassChange( int id, char nextClass )
	{
		SendClassChangeData	sendData( id, nextClass );
		gameParam->GetPlayerParam(id).charType = nextClass;

		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			gameParam->send( p, ( LPSTR )&sendData, sizeof( sendData ) );
		}
	}

	//	全ステータス送信
	void	LevelManager::SendAllStatus( int id )
	{
		//	情報取得
		PlayerStatus		playerStatus = gameParam->GetPlayerStatus( id );
		SendAllStatusData	sendData(
			playerStatus.power,
			playerStatus.defense,
			playerStatus.magicAttack,
			playerStatus.magicDefense,
			gameParam->GetLifeInfo( id ).maxLife,
			playerStatus.speed );

		//	送信
		gameParam->send( id, ( LPSTR )&sendData, sizeof( sendData ) );
	}

	//	各ステータス送信
	void	LevelManager::SendStatus( int id, char paramType, float status )
	{
		//	情報取得
		PlayerStatus		playerStatus = gameParam->GetPlayerStatus( id );

		//	宣言
		SendStatusData	sendStatus;
		sendStatus.paramType = paramType;

		switch ( paramType )
		{
		case SEND_STATUS::ATTACK:
			sendStatus.status = ( float )playerStatus.power;
			break;

		case SEND_STATUS::DEFENSE:
			sendStatus.status = ( float )playerStatus.defense;
			break;

		case SEND_STATUS::MAGIC_ATTACK:
			sendStatus.status = ( float )playerStatus.magicAttack;
			break;

		case SEND_STATUS::MAGIC_DEFENSE:
			sendStatus.status = ( float )playerStatus.magicDefense;
			break;

		case SEND_STATUS::SPEED:
			sendStatus.status = playerStatus.speed;
			break;
			
		case SEND_STATUS::LIFE:
			sendStatus.status = ( float )gameParam->GetLifeInfo( id ).maxLife;
			break;

		default:
			return;
		}

		//	送信
		gameParam->send( id, ( LPSTR )&sendStatus, sizeof( sendStatus ) );
	}

	//	HP最大値送信
	void	LevelManager::SendMaxLife( int id )
	{
		static	struct
		{
			char		com;
			int		id;
			int		maxLife;
		}sendData;

		sendData.com = SEND_COMMAND::MAX_LIFE_INFO;
		sendData.id = id;
		sendData.maxLife = gameParam->GetPlayerStatus( id ).maxLife;

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			if ( gameParam->GetPlayerActive( i ) == false )	continue;
			gameParam->send( i, ( LPSTR )&sendData, sizeof( sendData ) );
		}
	}
	
//----------------------------------------------------------------------------------------------
//	受信
//----------------------------------------------------------------------------------------------

	//	討伐情報受信
	void	LevelManager::ReceiveHuntInfo( int client, const LPSTR& data )
	{
		//	構造体宣言
		static	struct HuntInfo
		{
			char com;
			char infoType;
			char enemyType;
		} *huntInfo;

		//	変換
		huntInfo = ( HuntInfo* )data;

		//	経験値計算
		levelManager->CalcExp( client, huntInfo->enemyType );
		levelManager->SendExp( client );
	}

//----------------------------------------------------------------------------------------------
//	レベル毎のステータス計算
//----------------------------------------------------------------------------------------------

	//	ステータス計算
	void	LevelManager::CulcStatus( int id, char levelType )
	{
		CulcPower( id, levelType );
		CulcDefense( id, levelType );
		CulcMagicAttack( id, levelType );
		CulcMagicDefense( id, levelType );
		CulcMaxLife( id, levelType );
		CulcSpeed( id, levelType );
	}

	//	攻撃力計算
	void	LevelManager::CulcPower( int id, char levelType )
	{
		int addParam = gameManager->GetUpGrade( 
			levelType, 
			UPGRADE_DATA::ATTACK,
			levelInfo[id].level[levelType] );
		gameParam->GetPlayerStatus( id ).CulcPower( addParam );
	}

	//	防御力計算
	void	LevelManager::CulcDefense( int id, char levelType )
	{
		int addParam = gameManager->GetUpGrade(
			levelType,
			UPGRADE_DATA::DEFENSE,
			levelInfo[id].level[levelType] );
		gameParam->GetPlayerStatus( id ).CulcDefense( addParam );
	}

	//	魔法攻撃力計算
	void	LevelManager::CulcMagicAttack( int id, char levelType )
	{
		int addParam = gameManager->GetUpGrade(
			levelType,
			UPGRADE_DATA::MAGIC_ATTACK,
			levelInfo[id].level[levelType] );
		gameParam->GetPlayerStatus( id ).CulcMagicAttack( addParam );
	}

	//	魔法防御力計算
	void	LevelManager::CulcMagicDefense( int id, char levelType )
	{
		int addParam = gameManager->GetUpGrade(
			levelType,
			UPGRADE_DATA::MAGIC_DIFENSE,
			levelInfo[id].level[levelType] );
		gameParam->GetPlayerStatus( id ).CulcMagicDefense( addParam );
	}

	//	最大HP計算
	void	LevelManager::CulcMaxLife( int id, char levelType )
	{
		int addParam = gameManager->GetUpGrade(
			levelType,
			UPGRADE_DATA::HP,
			levelInfo[id].level[levelType] );
		gameParam->GetPlayerStatus( id ).CulcMaxLife( addParam );
		gameParam->GetLifeInfo( id ).AddMaxLife( addParam );
		gameParam->GetLifeInfo( id ).CulcLife( addParam );
	}

	//	スピード計算
	void	LevelManager::CulcSpeed( int id, char levelType )
	{
		float doubleParam = gameManager->GetUpGradeSpeed(
			levelType,
			levelInfo[id].level[levelType] );

		if ( doubleParam >= 0.5f )
			gameParam->GetPlayerStatus( id ).DoubleSpeed( doubleParam );
	}

//----------------------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------------------

	//	各プレイヤーレベル情報取得
	LevelInfo&	LevelManager::GetLevelInfo( int id )
	{
		return	levelInfo[id];
	}

	//	各レベル取得
	char	LevelManager::GetLevel( int id, char levelType )const
	{
		return	levelInfo[id].level[levelType];
	}

	//	経験値取得
	int	LevelManager::GetExp( int id )const
	{
		return	levelInfo[id].exp;
	}

	//	合計レベル取得
	int	LevelManager::GetTotalLevel( int id )const
	{
		return	levelInfo[id].total_level;
	}






