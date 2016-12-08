
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"Interpolation.h"
#include	"GameParam.h"
#include	"InputManager.h"
#include	"GameWait.h"

//***************************************************************
//
//	GameWaitクラス
//
//***************************************************************

//----------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------

	//	コンストラクタ
	GameWait::GameWait( void ) : back( nullptr ), nameUI( nullptr ),
		index( -1 )
	{
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			obj[i] = nullptr;
			targetTex[i] = nullptr;
			view[i] = nullptr;
		}
	}

	//	デストラクタ
	GameWait::~GameWait( void )
	{
		SafeDelete( back );
		SafeDelete( nameUI );

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			SafeDelete( targetTex[i] );
			SafeDelete( view[i] );
			SafeDelete( obj[i] );
		}
	}

	//	初期化
	void	GameWait::Initialize( int index, int* name )
	{
		this->index = index;

		//	背景画像読み込み
		back = new iex2DObj( "DATA/UI/BackGround/matching_gamen_parts.png" );

		//	バックバッファポインタ退避
		iexSystem::GetDevice()->GetRenderTarget( 0, &backBuffer );

		//	nameUI設定
		nameUI = new NameUI();
		nameUI->Initialize( 
			iexSystem::ScreenWidth / 4, ( int )( iexSystem::ScreenHeight * 0.8f ), 
			50, 50, name );

		//	順番設定
		order[0] = index;
		int	 orderNum = 1;

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			if ( i != index )	
			{
				order[orderNum] = i;
				orderNum++;
			}

			//	オブジェクト初期化
			ObjInitialize( i );

			//	カメラ初期化
			ViewInitialize( i );

			//	テクスチャ初期化
			TextureInitialize( i );
		}
	}
	
	//	オブジェクト初期化
	void	GameWait::ObjInitialize( int index )
	{
		//	テクスチャ初期化
		obj[index] = nullptr;
		obj[index] = new iex3DObj( "DATA/CHR/suppin/suppin.IEM" );

		//	テクスチャ差替え
		char	fileName[256] = "DATA/CHR/suppin/s_body_";
		char playerNum[8] = "";
		sprintf_s( playerNum, "%d.png", index );
		strcat_s( fileName, playerNum );
		obj[index]->SetTexture( 0, fileName );

		//	更新
		if ( this->index == index )
		{
			obj[index]->SetAngle( 0.0f );
			obj[index]->SetPos( 0.0f, 0.2f, 0.0f );
		}
		else
		{
			obj[index]->SetAngle( D3DX_PI * 0.25f );
			obj[index]->SetPos( -0.8f, 0.0f, 0.0f );
		}
		obj[index]->SetScale( 0.1f );
		obj[index]->Update();
	}

	//	カメラ初期化
	void	GameWait::ViewInitialize( int index )
	{
			//	カメラ初期化
			view[index] = nullptr;
			view[index] = new iexView();
			view[index]->Set( Vector3( 0.0f, 2.0f, 5.0f ), Vector3( 0.0f, 1.5f, 0.0f ) );
	}

	//	テクスチャ初期化
	void	GameWait::TextureInitialize( int index )
	{
		targetTex[index] = nullptr;
		targetTex[index] = new iex2DObj( iexSystem::ScreenWidth, iexSystem::ScreenHeight, IEX2D_RENDERTARGET );
	}

//----------------------------------------------------------------------------------
//	更新・描画
//----------------------------------------------------------------------------------

	//	更新
	void	GameWait::Update( void )
	{
		nameUI->Update();
		UpdateInfo();
	}

	//	描画
	void	GameWait::Render( void )
	{
		//	画面クリア
		MyCharacterRender();
		for ( int i = 1; i < PLAYER_MAX; i++ )
		{
			OtherPlayerRender( i );
		}

		nameUI->Render();
	}

	//	自キャラ描画
	void	GameWait::MyCharacterRender( void )
	{
		//	レンダーターゲット設定
		targetTex[index]->RenderTarget( 0 );

		//	画面クリア
		view[index]->Activate();
		view[index]->Clear();

		//	背景描画
		iexSystem::GetDevice()->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
		back->Render( iexSystem::ScreenWidth / 5, 0, iexSystem::ScreenWidth / 5 * 3, iexSystem::ScreenHeight, 0, 0, 650, 720 );
		iexSystem::GetDevice()->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

		//	キャラクター描画
		obj[index]->Render();

		//	フレームバッファへ切り替え
		iexSystem::GetDevice()->SetRenderTarget( 0, backBuffer );

		//	テクスチャ描画
		targetTex[index]->Render( 
			0, 0, iexSystem::ScreenWidth / 2, iexSystem::ScreenHeight,
			iexSystem::ScreenWidth / 5, 0,
			iexSystem::ScreenWidth / 5 * 3, iexSystem::ScreenHeight );
	}

	//	他キャラ描画
	void	GameWait::OtherPlayerRender( int index )
	{
		//	レンダーターゲット設定
		targetTex[order[index]]->RenderTarget( 0 );

		//	画面クリア
		view[order[index]]->Activate();
		view[order[index]]->Clear();

		//	背景描画
		iexSystem::GetDevice()->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
		back->Render( 0, iexSystem::ScreenHeight / 4, 
			iexSystem::ScreenWidth / 5 * 4, iexSystem::ScreenHeight / 3, 650, 0, 650, 240 );
		iexSystem::GetDevice()->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE );

		//	キャラクター描画
		bool active = gameParam->GetPlayerActive( order[index] );
		if( active )obj[order[index]]->Render();

		//	フレームバッファへ切り替え
		iexSystem::GetDevice()->SetRenderTarget( 0, backBuffer );
		
		//	テクスチャ描画
		targetTex[order[index]]->Render( 
			iexSystem::ScreenWidth / 2, ( iexSystem::ScreenHeight / 3 ) * ( index - 1 ), 
			iexSystem::ScreenWidth / 2, iexSystem::ScreenHeight / 3,
			0, iexSystem::ScreenHeight / 4,
			iexSystem::ScreenWidth / 5 * 4, iexSystem::ScreenHeight / 3 );
	}

	//	情報更新
	void	GameWait::UpdateInfo( void )
	{
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			obj[i]->Update();
			obj[i]->Animation();
		}
	}

//----------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------


