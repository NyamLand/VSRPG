
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
//	�������E���
//----------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	Stage::Stage( void ) : view( nullptr ), viewTex( nullptr )
	{
		//	�e���f������
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

		//	�e�N�X�`��������
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

		//	�o�b�N�o�b�t�@�|�C���^�ޔ�
		iexSystem::GetDevice()->GetRenderTarget( 0, &backBuffer );
	}

	//	�f�X�g���N�^
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
//	�`��
//----------------------------------------------------------------------------------------

	//	�`��
	void	Stage::Render( void )
	{
		RenderTexture();

		for ( int i = 0; i < PARTS_MAX; i++ )
		{
			stage[i]->Render();
		}
	}

	//	�e�N�X�`���`��
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

		//	�t���[���o�b�t�@�֐؂�ւ�
		iexSystem::GetDevice()->SetRenderTarget( 0, backBuffer );

		initState = true;
	}
	
//----------------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------------

	//	�e�N�X�`���擾
	Image*&	Stage::GetTexture( void )
	{
		return	viewTex;
	}





