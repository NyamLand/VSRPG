
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	<vector>
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
		for ( int i = 0; i < PLAYER_TYPE::MODEL_MAX; i++ )
		{
			obj[i] = nullptr;
		}

		playerList.clear();
	}
		
	//	デストラクタ
	PlayerManager::~PlayerManager( void )
	{
		//Release();
	}

	//	初期化
	bool	PlayerManager::Initialize( void )
	{
		//	リスト初期化
		playerList.clear();

		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			SetPlayer( p );
		}
		return	true;
	}

	//	解放
	void	PlayerManager::Release( void )
	{
		for ( auto it = playerList.begin(); it != playerList.end(); )
		{
			it = playerList.erase( it );
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
			if ( gameParam->GetPlayerActive( p ) )
				playerList[p]->Update();
		}
	}

	//	描画
	void	PlayerManager::Render( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( gameParam->GetPlayerActive( p ) )
				playerList[p]->Render();
		}
	}

	//	HPバー描画
	void	PlayerManager::RenderHp( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( gameParam->GetPlayerActive( p ) )
				playerList[p]->BarRender();
		}
	}

//-------------------------------------------------------------------------------------
//	動作関数
//-------------------------------------------------------------------------------------

	//	クラスチェンジ
	void	PlayerManager::ClassChange( int id, char nextClass )
	{
		Player*	 player = nullptr;

		switch ( nextClass )
		{
		case PLAYER_TYPE::NORMAL:
			player = new Suppin();
			break;

		case PLAYER_TYPE::FIGHTER:
			player = new Fighter();
			break;

		case PLAYER_TYPE::MAGICIAN:
			player = new Magician();
			break;

		default:
			player = new Suppin();
		}

		//	モデルセット、初期化
		player->Initialize( id );

		//	リストに追加
		playerList.insert( playerList.begin() + id, player );
	}

//-------------------------------------------------------------------------------------
//	情報設定
//-------------------------------------------------------------------------------------

	//	プレイヤー生成
	void	PlayerManager::SetPlayer( int id )
	{
		//	プレイヤー生成
		ClassChange( id, PLAYER_TYPE::NORMAL );
	}

//-------------------------------------------------------------------------------------
//	情報取得
//-------------------------------------------------------------------------------------

	//	Player情報取得
	Player*&	PlayerManager::GetPlayer( int id )
	{
		return	playerList[id];
	}
