
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"system\System.h"
#include	"Stage.h"

//*************************************************************************
//
//	Stageクラス
//
//*************************************************************************

//----------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------

#define	STAGE_SCALE	0.1f
#define	STAGE_DOWN	Vector3( 0.0f, -5.0f, 0.0f )

namespace
{
	const LPSTR fileName[] =
	{
		"DATA/BG/soto.IMO",		//	外周
		"DATA/BG/stage.IMO",		//	土台
		"DATA/BG/tree.IMO",		//	木
		"DATA/BG/toride.IMO",	//	砦
		"DATA/BG/depari.IMO",	//	高台
		"DATA/BG/hei.IMO",			//	塀
		"DATA/BG/mountain.IMO"	//	山
	};
}

//----------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------

	//	コンストラクタ
	Stage::Stage( void ) : view( nullptr ), viewTex( nullptr )
	{
		collisionMesh = new iexMesh( "DATA/BG/stage_atari.IMO" );

		//	各モデル調整
		for ( int i = 0; i < PARTS_MAX; i++ )
		{
			stage[i] = nullptr;
			stage[i] = new iexMesh( fileName[i] );
			stage[i]->SetScale( STAGE_SCALE );
			stage[i]->SetPos( STAGE_DOWN );
			stage[i]->Update();
		}
		view = new iexView();
		view->Set( Vector3( 0.0f, 650.0f, 0.0f ), Vector3( 0.0f, 0.0f, 0.1f ) );

		//	テクスチャ初期化
		viewTex = new Image();
		viewTex->obj = new iex2DObj( 1280, 720, IEX2D_RENDERTARGET );
		viewTex->x = 500;
		viewTex->y = 300;
		viewTex->w= 200;
		viewTex->h = 200;
		viewTex->sx = 280;
		viewTex->sy = 0;
		viewTex->sw = 1280 - 560;
		viewTex->sh = 720;
		initState = false;

		//	バックバッファポインタ退避
		iexSystem::GetDevice()->GetRenderTarget( 0, &backBuffer );
	}

	//	デストラクタ
	Stage::~Stage( void )
	{
		for ( int i = 0; i < PARTS_MAX; i++ )
		{
			SafeDelete( stage[i] );
		}

		SafeDelete( collisionMesh );
		SafeDelete( view );
		SafeDelete( viewTex );
		backBuffer->Release();
	}
	
//----------------------------------------------------------------------------------------
//	描画
//----------------------------------------------------------------------------------------

	//	描画
	void	Stage::Render( void )
	{
		RenderTexture();
		//collisionMesh->Render();

		for ( int i = 0; i < PARTS_MAX; i++ )
		{
			stage[i]->Render();
		}
	}

	//	テクスチャ描画
	void	Stage::RenderTexture( void )
	{
		if ( initState == true )	return;
		viewTex->obj->RenderTarget( 0 );
		view->Activate();
		view->Clear();

		for ( int i = 0; i < PARTS_MAX; i++ )
		{
			stage[i]->Render();
			if (i == 2)	stage[i]->Render( shader3D, "alpha" );
		}

		//	フレームバッファへ切り替え
		iexSystem::GetDevice()->SetRenderTarget( 0, backBuffer );

		initState = true;
	}
	
//----------------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------------

	//	テクスチャ取得
	Image*&	Stage::GetTexture( void )
	{
		return	viewTex;
	}





