
#include	"iextreme.h"
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
	
	//	レベル情報
	struct ReceiveLevelData
	{
		char com = RECEIVE_COMMAND::STATUS_INFO;
		char statusType;
		char levelType;
		char level;
	};

	//	経験値情報
	struct ReceiveExpData
	{
		char com = RECEIVE_COMMAND::STATUS_INFO;
		char statusType;
		int exp;
	};

	//	全ステータス情報
	struct ReceiveAllStatusData
	{
		char com = RECEIVE_COMMAND::STATUS_INFO;	//	1byte
		char statusType;	//	1byte
		char paramType;	//	1byte
		int attack;		//	4byte
		int defense;	//	4byte
		int magicAttack;	//	4byte
		int magicDefense;	//	4byte
		int life;	//	4byte
		float speed;	//	4byte
	};

	//	各ステータス情報
	struct ReceiveStatusData
	{
		char		com = RECEIVE_COMMAND::STATUS_INFO;
		char		statusType;
		char		paramType;
		float		status;
	};

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

		//	
		namespace STATUS_TYPE
		{
			enum
			{
				LEVEL,
				EXP,
				STATUS
			};
		}
	}

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	LevelManager::LevelManager( void )
	{
		//	経験値初期化
		levelInfo.exp = 1000;

		//	各レベル初期化
		for ( int i = 0; i < LEVEL_TYPE::TYPE_MAX; i++ )
		{
			levelInfo.level[i] = 0;
		}
	}

	//	デストラクタ
	LevelManager::~LevelManager( void )
	{

	}

	//	初期化
	bool	LevelManager::Initialize( void )
	{
		//	経験値初期化
		levelInfo.exp = 1000;

		//	各レベル初期化
		for (int i = 0; i < LEVEL_TYPE::TYPE_MAX; i++)
		{
			levelInfo.level[i] = 0;
		}

		return	true;
	}

//----------------------------------------------------------------------------------------------
//	動作関数
//----------------------------------------------------------------------------------------------

	//	受信処理
	void	LevelManager::Receive( const LPSTR& data )
	{
		switch ( data[1] )
		{
		case STATUS_TYPE::EXP:
			{
				ReceiveExpData*	receiveExpdata = ( ReceiveExpData* )data;
				levelManager->SetExp( receiveExpdata->exp );
			}
			break;

		case STATUS_TYPE::LEVEL:
			{
				ReceiveLevelData* receiveLevelData = ( ReceiveLevelData* )data;
				levelManager->SetLevelInfo( receiveLevelData->levelType, receiveLevelData->level );
			}
			break;

		case STATUS_TYPE::STATUS:
			levelManager->CulcStatus( data );
			break;

		default:
			break;
		}

	}

	//	レベル送信
	void	LevelManager::SendLevel( char levelType )
	{
		//	情報設定
		SendLevelData	sendLevelData( levelType );

		//	情報送信
		gameParam->send( ( LPSTR )&sendLevelData, sizeof( sendLevelData ) );
	}

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

	//	経験値情報設定
	void	LevelManager::SetExp( int exp )
	{
		levelInfo.exp = exp;
	}

	//	レベル情報設定
	void	LevelManager::SetLevelInfo( char levelType, char level )
	{
		levelInfo.level[levelType] = level;
	}

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

	//	ステータス計算
	void	LevelManager::CulcStatus( const LPSTR& data )
	{
		switch ( data[2] )
		{
		case RECEIVE_STATUS::ATTACK:
			CulcPower( data );
			break;

		case RECEIVE_STATUS::DEFENSE:
			CulcDefense( data );
			break;

		case RECEIVE_STATUS::MAGIC_ATTACK:
			CulcMagicAttack( data );
			break;

		case RECEIVE_STATUS::MAGIC_DEFENSE:
			CulcMagicDefense( data );
			break;

		case RECEIVE_STATUS::SPEED:
			CulcSpeed( data );
			break;

		case RECEIVE_STATUS::LIFE:
			CulcMaxLife( data );
			break;

		case RECEIVE_STATUS::ALL:
			CulcAllStatus( data );
			break;
		}
	}

	//	全ステータス計算
	void	LevelManager::CulcAllStatus( const LPSTR& data )
	{
		ReceiveAllStatusData*	statusData = ( ReceiveAllStatusData* )data;
		gameParam->GetPlayerStatus().power = statusData->attack;
		gameParam->GetPlayerStatus().defense = statusData->defense;
		gameParam->GetPlayerStatus().magicPower = statusData->magicAttack;
		gameParam->GetPlayerStatus().magicDefense = statusData->magicDefense;
		gameParam->GetPlayerStatus().maxLife = statusData->life;
		gameParam->GetPlayerStatus().speed = statusData->speed;
	}

	//	攻撃力計算
	void	LevelManager::CulcPower( const LPSTR& data )
	{
		ReceiveStatusData*	statusData = ( ReceiveStatusData* )data;
		gameParam->GetPlayerStatus().CulcPower( ( int )statusData->status );
	}

	//	防御力計算
	void	LevelManager::CulcDefense( const LPSTR& data )
	{
		ReceiveStatusData*	statusData = ( ReceiveStatusData* )data;
		gameParam->GetPlayerStatus().CulcDefense( ( int )statusData->status );
	}

	//	魔法攻撃力計算
	void	LevelManager::CulcMagicAttack( const LPSTR& data )
	{
		ReceiveStatusData*	statusData = ( ReceiveStatusData* )data;
		gameParam->GetPlayerStatus().CulcMagicPower( ( int )statusData->status );
	}
	
	//	魔法防御力計算
	void	LevelManager::CulcMagicDefense( const LPSTR& data )
	{
		ReceiveStatusData*	statusData = ( ReceiveStatusData* )data;
		gameParam->GetPlayerStatus().CulcMagicDefense( ( int )statusData->status );
	}

	//	最大HP計算
	void	LevelManager::CulcMaxLife( const LPSTR& data )
	{
		ReceiveStatusData*	statusData = ( ReceiveStatusData* )data;
		gameParam->GetPlayerStatus().CulcMaxLife( ( int )statusData->status );
	}

	//	スピード計算
	void	LevelManager::CulcSpeed( const LPSTR& data )
	{
		ReceiveStatusData*	statusData = ( ReceiveStatusData* )data;
		gameParam->GetPlayerStatus().DoubleSpeed( statusData->status );
	}

//----------------------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------------------

	//	各プレイヤーレベル情報取得
	LevelInfo&	LevelManager::GetLevelInfo( void )
	{
		return	levelInfo;
	}

	//	各レベル取得
	char	LevelManager::GetLevel( char levelType )const
	{
		return	levelInfo.level[levelType];
	}

	//	経験値取得
	int	LevelManager::GetExp( void )const
	{
		return	levelInfo.exp;
	}







