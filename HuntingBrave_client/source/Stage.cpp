
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"Stage.h"

//*************************************************************************
//
//	Stage�N���X
//
//*************************************************************************

//----------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------

#define	STAGE_SCALE	0.1f
#define	STAGE_DOWN	Vector3( 0.0f, -5.0f, 0.0f )

//----------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	Stage::Stage( void ) : stage( nullptr ), soto( nullptr ), tree( nullptr ), toride( nullptr ), collisionMesh( nullptr )
	{
		//	stage������
		collisionMesh = new iexMesh( "DATA/BG/collision.IMO" );
		stage = new iexMesh( "DATA/BG/stage.IMO" );
		soto = new iexMesh( "DATA/BG/soto.IMO" );
		tree = new iexMesh( "DATA/BG/tree.IMO" );
		toride = new iexMesh( "DATA/BG/toride.IMO" );

		//	�X�P�[������
		collisionMesh->SetScale( STAGE_SCALE );
		stage->SetScale( STAGE_SCALE );
		tree->SetScale( STAGE_SCALE );
		toride->SetScale( STAGE_SCALE );
		soto->SetScale( STAGE_SCALE );

		//	���W����
		collisionMesh->SetPos( STAGE_DOWN );
		stage->SetPos( STAGE_DOWN );
		tree->SetPos( STAGE_DOWN );
		toride->SetPos( STAGE_DOWN );
		soto->SetPos( STAGE_DOWN );

		//	�X�V
		collisionMesh->Update();
		stage->Update();
		soto->Update();
		tree->Update();
		toride->Update();
	}

	//	�f�X�g���N�^
	Stage::~Stage( void )
	{
		SafeDelete( collisionMesh );
		SafeDelete( stage );
		SafeDelete( soto );
		SafeDelete( tree );
		SafeDelete( toride );
	}
	
//----------------------------------------------------------------------------------------
//	�`��
//----------------------------------------------------------------------------------------

	//	�`��
	void	Stage::Render( void )
	{
		//collisionMesh->Render();
		stage->Render();
		tree->Render();
		toride->Render();
		soto->Render();
	}
	
//----------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------






