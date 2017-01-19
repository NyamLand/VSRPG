
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

//----------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------

	//	コンストラクタ
	Stage::Stage( void ) : stage( nullptr ), soto( nullptr ), tree( nullptr ), toride( nullptr ), collisionMesh( nullptr )
	{
		//	stage初期化
		collisionMesh = new iexMesh( "DATA/BG/collision.IMO" );
		stage = new iexMesh( "DATA/BG/stage.IMO" );
		soto = new iexMesh( "DATA/BG/soto.IMO" );
		tree = new iexMesh( "DATA/BG/tree.IMO" );
		toride = new iexMesh( "DATA/BG/toride.IMO" );

		//	スケール調整
		collisionMesh->SetScale( STAGE_SCALE );
		stage->SetScale( STAGE_SCALE );
		tree->SetScale( STAGE_SCALE );
		toride->SetScale( STAGE_SCALE );
		soto->SetScale( STAGE_SCALE );

		//	座標調整
		collisionMesh->SetPos( STAGE_DOWN );
		stage->SetPos( STAGE_DOWN );
		tree->SetPos( STAGE_DOWN );
		toride->SetPos( STAGE_DOWN );
		soto->SetPos( STAGE_DOWN );

		//	更新
		collisionMesh->Update();
		stage->Update();
		soto->Update();
		tree->Update();
		toride->Update();
	}

	//	デストラクタ
	Stage::~Stage( void )
	{
		SafeDelete( collisionMesh );
		SafeDelete( stage );
		SafeDelete( soto );
		SafeDelete( tree );
		SafeDelete( toride );
	}
	
//----------------------------------------------------------------------------------------
//	描画
//----------------------------------------------------------------------------------------

	//	描画
	void	Stage::Render( void )
	{
		//collisionMesh->Render();
		stage->Render();
		tree->Render();
		toride->Render();
		soto->Render();
	}
	
//----------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------






