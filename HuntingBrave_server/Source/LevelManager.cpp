
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
			levelInfo[p].exp = 0;
			levelInfo[p].total_level = 0;

			//	各レベル初期化
			for ( int i = 0; i < LEVEL_TYPE::TYPE_MAX; i++ )
			{
				levelInfo[p].level[i] = 0;
			}
		}

		expData[ENEMY_EXP::BIG_ENEMY] = 50;
		expData[ENEMY_EXP::SMALL_ENEMY] = 10;
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
	}

	//	経験値計算
	void	LevelManager::CalcExp( int id, char enemyType )
	{
		//	経験値加算
		levelInfo[id].exp += expData[enemyType];

		//	下限設定
		if ( levelInfo[id].exp <= 0 )	levelInfo[id].exp = 0;
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
	void	LevelManager::SendStatus( int id, char statusType, float status )
	{
		//	情報取得
		PlayerStatus		playerStatus = gameParam->GetPlayerStatus( id );

		//	宣言
		SendStatusData	sendStatus;
		sendStatus.statusType = statusType;

		switch ( statusType )
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
		gameParam->GetLifeInfo( id ).AddMaxLife( addParam );
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






