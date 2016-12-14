
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"UIManager.h"
#include	"GameParam.h"
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
	PlayerManager::PlayerManager( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			player[p] = nullptr;
		}
	}
		
	//	デストラクタ
	PlayerManager::~PlayerManager( void )
	{
		//Release();
	}

	//	初期化
	bool	PlayerManager::Initialize( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			player[p] = nullptr;

			if ( gameParam->GetPlayerActive( p ) )
			{
				PlayerParam		playerParam = gameParam->GetPlayerParam( p );
				SetPlayer( p );
			}
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
	void	PlayerManager::Update( void )
	{
		//	全プレイヤー更新
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	存在チェック
			if ( player[p] == nullptr )	continue;
			
			//	プレイヤー更新
			player[p]->Update( gameParam->GetPlayerParam( p ) );
		}
	}

	//	描画
	void	PlayerManager::Render( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	存在チェック
			if ( player[p] == nullptr )	continue;

			//	描画
			player[p]->Render();
		}
	}


	void	PlayerManager::RenderHp(void)
	{
		for (int p = 0; p < PLAYER_MAX; p++)
		{
			if (player[p] == nullptr)	continue;
			player[p]->BarRender();

		}
	}
//-------------------------------------------------------------------------------------
//	動作関数
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//	情報設定
//-------------------------------------------------------------------------------------

	//	プレイヤー生成
	void	PlayerManager::SetPlayer( int id )
	{
		//	存在チェック
		if ( player[id] != nullptr )	return;

		//	プレイヤー生成
		player[id] = new Player();
		player[id]->Initialize( id );
	}

//-------------------------------------------------------------------------------------
//	情報取得
//-------------------------------------------------------------------------------------

	//	Player情報取得
	Player*&	PlayerManager::GetPlayer( int id )
	{
		return	player[id];
	}
