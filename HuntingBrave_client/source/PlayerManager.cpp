
#include	"iextreme.h"
#include	"system/System.h"
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
			if( gameParam->GetPlayerActive( p ) == false )	continue;
			
			player[p] = nullptr;
			SetPlayer( p );
		}

		return	true;
	}

	//	解放
	void	PlayerManager::Release( void )
	{
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			SafeDelete( player[i] );
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
			if ( gameParam->GetPlayerActive( p ) == false )		continue;
			
			//	更新
			player[p]->Update();
		}
	}

	//	描画
	void	PlayerManager::Render( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( gameParam->GetPlayerActive( p ) == false )		continue;
			
			//	描画
			player[p]->Render( shader, "damageEffect" );
		}
	}

	//	HPバー描画
	void	PlayerManager::RenderHp( void )
	{
		return;
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( gameParam->GetPlayerActive( p ) == false )	continue;
			
			//	バー描画
			player[p]->BarRender();
		}
	}

//-------------------------------------------------------------------------------------
//	動作関数
//-------------------------------------------------------------------------------------

	//	クラスチェンジ
	void	PlayerManager::ClassChange( int id, char nextClass )
	{
		if ( gameParam->GetPlayerActive( id ) == false )	return;

		//	クラスチェンジ
		player[id]->ChangeModel( nextClass );
	}

	//	受信
	void	PlayerManager::Receive( const LPSTR& data )
	{
		ReceiveClassChangeData* receiveData = 
			( ReceiveClassChangeData* )data;
		ClassChange( receiveData->id, receiveData->nextClass );
	}

//-------------------------------------------------------------------------------------
//	情報設定
//-------------------------------------------------------------------------------------

	//	プレイヤー生成
	void	PlayerManager::SetPlayer( int id )
	{
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
