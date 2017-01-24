
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
		"DATA/BG/stage.IMO",
		"DATA/BG/soto.IMO",
		"DATA/BG/tree.IMO",
		"DATA/BG/toride.IMO",
		"DATA/BG/depari.IMO",
		"DATA/BG/hei.IMO",
		"DATA/BG/mountain.IMO"
	};
}

//----------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------

	//	コンストラクタ
	Stage::Stage( void ) : collisionMesh( nullptr )
	{
		//	stage初期化
		collisionMesh = new iexMesh( "DATA/BG/stage_atari.IMO" );
		collisionMesh->Update();

		//	各モデル調整
		for ( int i = 0; i < PARTS_MAX; i++ )
		{
			stage[i] = nullptr;
			stage[i] = new iexMesh( fileName[i] );
			stage[i]->SetScale( STAGE_SCALE );
			stage[i]->SetPos( STAGE_DOWN );
			stage[i]->Update();
		}
	}

	//	デストラクタ
	Stage::~Stage( void )
	{
		SafeDelete( collisionMesh );
		for ( int i = 0; i < PARTS_MAX; i++ )
		{
			SafeDelete( stage[i] );
		}
	}
	
//----------------------------------------------------------------------------------------
//	描画
//----------------------------------------------------------------------------------------

	//	描画
	void	Stage::Render( void )
	{
		//collisionMesh->Render();
		for ( int i = 0; i < PARTS_MAX; i++ )
		{
			stage[i]->Render();
		}
	}
	
//----------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------






