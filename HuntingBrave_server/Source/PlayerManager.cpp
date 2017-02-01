
#include	"iextreme.h"
#include	<vector>
#include	"PlayerManager.h"

//*****************************************************************************************************************************
//
//	PlayerManagerクラス
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

PlayerManager*	playerManager = nullptr;

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	PlayerManager::PlayerManager( GameParam* gameParam )
	{
		this->gameParam = gameParam;

		//	全プレイヤー初期化
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			player[p] = nullptr;
		}
	}

	//	デストラクタ
	PlayerManager::~PlayerManager( void )
	{	
		Release();
	}

	//	初期化
	bool	PlayerManager::Initialize( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	プレイヤーがアクティブ状態なら
			if ( gameParam->GetPlayerActive( p ) )	SetPlayer( p );
		}
		return	true;
	}

	//	解放
	void	PlayerManager::Release( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			ReleasePlayer( p );
		}
	}

//----------------------------------------------------------------------------------------------
//	更新
//----------------------------------------------------------------------------------------------

	//	更新
	void	PlayerManager::Update( int id )
	{
		PlayerParam	param = gameParam->GetPlayerParam( id );

		//	プレイヤー更新
		if (  gameParam->GetPlayerActive( id ) == false )
		{
			ReleasePlayer( id );
		}
		else
		{
			//	更新・情報を反映
			player[id]->Update( param );
			gameParam->SetPlayerParam( id, param.pos, param.angle, param.effParam, param.motion );
		}
	}

//----------------------------------------------------------------------------------------------
//	動作関数
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

	//	プレイヤー設定
	void	PlayerManager::SetPlayer( int id )
	{
		//	プレイヤー生成
		player[id] = new Player( id );
	}

	//	プレイヤー解放
	void	PlayerManager::ReleasePlayer( int id )
	{
		if ( player[id] != nullptr )
		{
			delete	player[id];
			player[id] = nullptr;
		}
	}

//----------------------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------------------

	//	座標取得
	Vector3	PlayerManager::GetPos( int id )
	{
		return	Vector3( 0.0f, 0.0f, 0.0f );
	}

	//	プレイヤー取得
	Player*&	PlayerManager::GetPlayer( int id )
	{
		return	player[id];
	}
