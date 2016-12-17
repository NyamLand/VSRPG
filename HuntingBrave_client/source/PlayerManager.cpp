
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

namespace
{
	//	定数
	#define	PLAYER_SCALE	0.2f

	//	ファイル名
	namespace
	{
		const LPSTR ModelFileName[] =
		{
			"DATA/CHR/suppin/suppin.IEM",			//	すっぴん
			"DATA/CHR/Magician/magician.IEM",	//	マジシャン
			"DATA/CHR/suppin/suppin.IEM",			//	プリースト
			"DATA/CHR/Fighter/fighter.IEM",			//	ファイター
			"DATA/CHR/suppin/suppin.IEM",			//	ナイト
			"DATA/CHR/suppin/suppin.IEM"			//	アサシン
		};
	}
}

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
		//	モデル読み込み
		LoadModel();

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

		for ( int i = 0; i < PLAYER_MODEL_TYPE::MODEL_MAX; i++ )
		{
			SafeDelete( obj[i] );
		}
	}

	//	モデル読み込み
	void	PlayerManager::LoadModel( void )
	{
		for ( int i = 0; i < PLAYER_MODEL_TYPE::MODEL_MAX; i++ )
		{
			obj[i] = nullptr;
			obj[i] = 	new iex3DObj( ModelFileName[i] );
			
			//	情報設定
			obj[i]->SetPos( Vector3( 0.0f, 0.0f, 0.0f ) );
			obj[i]->SetAngle( 0.0f );
			obj[i]->SetScale( PLAYER_SCALE );
			obj[i]->SetMotion( MOTION_NUM::POSUTURE );
			obj[i]->Update();
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
		player[id]->SetObj( obj[PLAYER_MODEL_TYPE::NORMAL]->Clone() );
		player[id]->SetPos( Vector3( 0.0f, 0.0f, 0.0f ) );
		player[id]->SetAngle( 0.0f );
		player[id]->SetScale( PLAYER_SCALE );
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
