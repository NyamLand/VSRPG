
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
//	�������E���
//----------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	Stage::Stage( void ) : collisionMesh( nullptr )
	{
		//	stage������
		collisionMesh = new iexMesh( "DATA/BG/stage_atari.IMO" );
		collisionMesh->Update();

		//	�e���f������
		for ( int i = 0; i < PARTS_MAX; i++ )
		{
			stage[i] = nullptr;
			stage[i] = new iexMesh( fileName[i] );
			stage[i]->SetScale( STAGE_SCALE );
			stage[i]->SetPos( STAGE_DOWN );
			stage[i]->Update();
		}
	}

	//	�f�X�g���N�^
	Stage::~Stage( void )
	{
		SafeDelete( collisionMesh );
		for ( int i = 0; i < PARTS_MAX; i++ )
		{
			SafeDelete( stage[i] );
		}
	}
	
//----------------------------------------------------------------------------------------
//	�`��
//----------------------------------------------------------------------------------------

	//	�`��
	void	Stage::Render( void )
	{
		//collisionMesh->Render();
		for ( int i = 0; i < PARTS_MAX; i++ )
		{
			stage[i]->Render();
		}
	}
	
//----------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------






