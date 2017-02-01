
#include	"iextreme.h"
#include	"GlobalFunction.h"
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
		"DATA/BG/soto.IMO",
		"DATA/BG/tree.IMO",
		"DATA/BG/toride.IMO",
		"DATA/BG/depari.IMO",
		"DATA/BG/hei.IMO",
		"DATA/BG/stage.IMO",
		"DATA/BG/mountain.IMO"
	};
}

//----------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------

	//	コンストラクタ
	Stage::Stage( void ) : view( nullptr ), viewTex( nullptr )
	{
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
		viewTex->x = 0;
		viewTex->y = 0;
		viewTex->w= 0;
		viewTex->h = 0;
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





