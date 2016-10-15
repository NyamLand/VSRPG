
#include	"iextreme.h"
#include	"GlobalFunction.h"
//#include	"GameManager.h"
#include	"PlayerManager.h"

//***************************************************************
//
//	PlayerManagerクラス
//
//***************************************************************

//-------------------------------------------------------------------------------------
//	グローバル
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//	初期化・解放
//-------------------------------------------------------------------------------------
	
	//	コンストラクタ
	PlayerManager::PlayerManager( void ) : gameParam( nullptr )
	{
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
	bool	PlayerManager::Initialize( GameParam* gameParam )
	{
		//	ゲームパラメータ取得
		this->gameParam = gameParam;

		//	全プレイヤー初期化
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			player[p] = nullptr;
		}
		return	true;
	}

	//	解放
	void	PlayerManager::Release( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			SafeDelete( player[p] );
		}
	}

//-------------------------------------------------------------------------------------
//	更新・描画
//-------------------------------------------------------------------------------------
	
	//	更新
	void	PlayerManager::Update( int id )
	{
		PlayerParam param = gameParam->GetPlayerParam( id );
		if ( !player[id]->Update( param ) ) 
		{
			SafeDelete( player[id] );
		}
		else
		{
			//	プレイヤー更新
			gameParam->SetPlayerParam( id, param.pos, param.angle );
		}
	}

//-------------------------------------------------------------------------------------
//	動作関数
//-------------------------------------------------------------------------------------

	//	プレイヤー生成
	void	PlayerManager::SetPlayer( int id, int type )
	{
		//	存在チェック
		if ( player[id] != nullptr )	return;

		//	プレイヤー生成
		player[id] = new Player();
	}

//-------------------------------------------------------------------------------------
//	情報設定
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//	情報取得
//-------------------------------------------------------------------------------------

	//	Player情報取得
	Vector3	PlayerManager::GetPos( int id )
	{
		return	player[id]->GetPos();
	}
