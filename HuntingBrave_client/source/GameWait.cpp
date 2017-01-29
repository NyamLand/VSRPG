
#include	"iextreme.h"
#include	"system/System.h"
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

#define	VS_SIZE	100

#define	TITLE_UI_POS_X			1115
#define	TITLE_INIT_HEIGHT	65
#define	TITLE_POS_SPACE		240

#define	NAME_UI_POS_X			1115
#define	NAME_INIT_HEIGHT	175
#define	NAME_POS_SPACE		240	

//----------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------

	//	コンストラクタ
	GameWait::GameWait( void ) : back( nullptr ), view( nullptr ),
		index( -1 )
	{
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			obj[i] = nullptr;
			targetTex[i] = nullptr;
			nameUI[i] = nullptr;
			playerTitleUI[i]= nullptr;
		}
	}

	//	デストラクタ
	GameWait::~GameWait( void )
	{
		SafeDelete( back );
		SafeDelete( view );

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			SafeDelete( targetTex[i] );
			SafeDelete( obj[i] );
			SafeDelete( nameUI[i] );
			SafeDelete( playerTitleUI[i] );
		}
	}

	//	初期化
	void	GameWait::Initialize( int index )
	{
		this->index = index;

		//	背景画像読み込み
		back = new iex2DObj( "DATA/UI/BackGround/matching_gamen_parts.png" );

		//	バックバッファポインタ退避
		iexSystem::GetDevice()->GetRenderTarget( 0, &backBuffer );

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

			//	NameUI初期化
			NameUIInitialize( i );

			//	playerTitleUI初期化
			PlayerTitleUIInitialize( i );
		}
	}
	
	//	オブジェクト初期化
	void	GameWait::ObjInitialize( int index )
	{
		//	テクスチャ初期化
		obj[index] = nullptr;
		obj[index] = new iex3DObj( "DATA/CHR/suppin/suppin.IEM" );

		//	テクスチャ差替え
		char	fileName[256] = "DATA/CHR/suppin/body_";
		char playerNum[8] = "";
		sprintf_s( playerNum, "%d.png", index + 1 );
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
			obj[index]->SetAngle( D3DX_PI * 0.2f );
			obj[index]->SetPos( 0.8f, 0.0f, 0.0f );
		}
		obj[index]->SetScale( 0.1f );
		obj[index]->Update();
	}

	//	カメラ初期化
	void	GameWait::ViewInitialize( int index )
	{
			//	カメラ初期化
			view = nullptr;
			view = new iexView();
			view->Set( Vector3( 0.0f, 2.0f, 5.0f ), Vector3( 0.0f, 1.5f, 0.0f ) );
	}

	//	テクスチャ初期化
	void	GameWait::TextureInitialize( int index )
	{
		targetTex[index] = nullptr;
		targetTex[index] = new iex2DObj( iexSystem::ScreenWidth, iexSystem::ScreenHeight, IEX2D_RENDERTARGET );
	}

	//	NameUI初期化
	void	GameWait::NameUIInitialize( int index )
	{
		//	nameUI設定
		nameUI[index] = new NameUI();

		nameUI[index]->Initialize(
			iexSystem::ScreenWidth / 4, ( int )( iexSystem::ScreenHeight * 0.89f ),
			50, 50 );
	}

	//	PlayerTitleUI初期化
	void	GameWait::PlayerTitleUIInitialize( int index )
	{
		//	playerTitleUI初期化
		playerTitleUI[index] = new PlayerTitleUI();
		playerTitleUI[index]->Initialize( 
			0, 0, 
			iexSystem::ScreenWidth / 4, 
			65, 
			150, 100 );
	}

//----------------------------------------------------------------------------------
//	更新
//----------------------------------------------------------------------------------

	//	更新
	void	GameWait::Update( void )
	{
		//	名前更新
		UpdateName();

		//	称号更新
		UpdatePlayerTitle();

		//	モデル情報更新
		UpdateInfo();
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

	//	名前UI更新
	void	GameWait::UpdateName( void )
	{
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			if ( i != 0 )
				nameUI[order[i]]->SetPos( NAME_UI_POS_X, NAME_INIT_HEIGHT + NAME_POS_SPACE * ( i - 1 ) );
			
			char*	nameText = gameParam->GetPlayerName()->GetName( order[i] );
			nameUI[order[i]]->Update( gameParam->GetPlayerName()->GetNameIndex( order[i] ) );
		}
	}

	//	プレイヤー称号更新
	void	GameWait::UpdatePlayerTitle( void )
	{
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			if ( i != 0 )
				playerTitleUI[order[i]]->SetPos( 
					TITLE_UI_POS_X, 
					TITLE_INIT_HEIGHT + TITLE_POS_SPACE * ( i - 1 ) );
			playerTitleUI[order[i]]->SetTitle( 
				gameParam->GetPlayerInfo( order[i] ).frontTitle,
				gameParam->GetPlayerInfo( order[i] ).backTitle );
		}
	}

//----------------------------------------------------------------------------------
//	更新
//----------------------------------------------------------------------------------

	//	描画
	void	GameWait::Render( void )
	{
		//	自キャラ描画
		MyCharacterRender();

		//	他プレイヤー描画
		for ( int i = 1; i < PLAYER_MAX; i++ )
		{
			OtherPlayerRender( i );
		}

		//	名前描画
		NameUIRender();

		//	称号描画
		PlayerTitleUIRender();

		//	VS描画
		VSRender();
	}

	//	自キャラ描画
	void	GameWait::MyCharacterRender( void )
	{
		//	レンダーターゲット設定
		targetTex[index]->RenderTarget( 0 );

		//	画面クリア
		view->Activate();
		view->Clear();

		//	背景描画
		iexSystem::GetDevice()->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
		back->Render( 320, 0, 640, iexSystem::ScreenHeight, 0, 0, 650, 720, RS_COPY, GetColor( 0.7f, 0.7f, 0.9f, 1.0f ) );
		iexSystem::GetDevice()->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

		//	キャラクター描画
		obj[index]->Render();

		//	フレームバッファへ切り替え
		iexSystem::GetDevice()->SetRenderTarget( 0, backBuffer );

		//	テクスチャ描画
		targetTex[index]->Render( 
			0, 0, iexSystem::ScreenWidth / 2, iexSystem::ScreenHeight,
			iexSystem::ScreenWidth / 4, 0,
			iexSystem::ScreenWidth / 2, iexSystem::ScreenHeight );
	}

	//	他キャラ描画
	void	GameWait::OtherPlayerRender( int index )
	{
		//	レンダーターゲット設定
		targetTex[order[index]]->RenderTarget( 0 );

		//	画面クリア
		view->Activate();
		view->Clear();

		//	背景描画
		iexSystem::GetDevice()->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
		back->Render( iexSystem::ScreenWidth / 4, iexSystem::ScreenHeight / 4, 
			iexSystem::ScreenWidth / 2, iexSystem::ScreenHeight / 3, 650, 0, 630, 240, RS_COPY, GetColor( 0.7f, 0.7f, 1.0f, 1.0f ) );
			iexSystem::GetDevice()->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );

		//	キャラクター描画
		bool active = gameParam->GetPlayerActive( order[index] );
		if( active )obj[order[index]]->Render();
		//obj[order[index]]->Render();

		//	フレームバッファへ切り替え
		iexSystem::GetDevice()->SetRenderTarget( 0, backBuffer );
		
		//	テクスチャ描画
		targetTex[order[index]]->Render( 
			iexSystem::ScreenWidth / 2, ( iexSystem::ScreenHeight / 3 ) * ( index - 1 ), 
			iexSystem::ScreenWidth / 2, iexSystem::ScreenHeight / 3,
			iexSystem::ScreenWidth / 4, iexSystem::ScreenHeight / 4,
			iexSystem::ScreenWidth / 2, iexSystem::ScreenHeight / 3 );
	}

	//	VS描画
	void	GameWait::VSRender( void )
	{
		back->Render( 
			iexSystem::ScreenWidth / 2 - ( VS_SIZE / 2 ), 
			iexSystem::ScreenHeight / 2 - ( VS_SIZE / 2 ),
			VS_SIZE, VS_SIZE,
			650, 480, 325, 240 );
	}

	//	名前UI描画
	void	GameWait::NameUIRender( void )
	{
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			bool active = gameParam->GetPlayerActive( order[i] );
			if ( active )
				nameUI[order[i]]->Render();
		}
	}

	//	プレイヤー称号UI描画
	void	GameWait::PlayerTitleUIRender( void )
	{
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			bool active = gameParam->GetPlayerActive( order[i] );
			if ( active )
				playerTitleUI[order[i]]->Render();
		}
	}


