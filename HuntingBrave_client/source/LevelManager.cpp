
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

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	LevelManager::LevelManager( void )
	{
		//	経験値初期化
		levelInfo.exp = 0;

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
		levelInfo.exp = 0;

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
		switch ( data[1] )
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
		ReceiveAllStatusData*	allStatusData = ( ReceiveAllStatusData* )data;
		gameParam->GetPlayerStatus().power = allStatusData->attack;
		gameParam->GetPlayerStatus().defense = allStatusData->defense;
		gameParam->GetPlayerStatus().magicPower = allStatusData->magicAttack;
		gameParam->GetPlayerStatus().magicDefense = allStatusData->magicDefense;
		gameParam->GetPlayerStatus().speed = allStatusData->speed;
	}

	//	全ステータス計算
	void	LevelManager::CulcAllStatus( const ReceiveAllStatusData& statusData )
	{
		gameParam->GetPlayerStatus().power = statusData.attack;
		gameParam->GetPlayerStatus().defense = statusData.defense;
		gameParam->GetPlayerStatus().magicPower = statusData.magicAttack;
		gameParam->GetPlayerStatus().magicDefense = statusData.magicDefense;
		gameParam->GetPlayerStatus().maxLife = statusData.life;
		gameParam->GetPlayerStatus().speed = statusData.speed;
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







