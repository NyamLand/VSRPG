
#include	"iextreme.h"
#include	"system/System.h"
#include	"GlobalFunction.h"
#include	"Interpolation.h"
#include	"GameParam.h"
#include	"InputManager.h"
#include	"GameWait.h"

//***************************************************************
//
//	GameWait�N���X
//
//***************************************************************

//----------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------

#define	VS_SIZE	100

//----------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------

	//	�R���X�g���N�^
	GameWait::GameWait( void ) : back( nullptr ), nameUI( nullptr ), view( nullptr ),
		index( -1 )
	{
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			obj[i] = nullptr;
			targetTex[i] = nullptr;
		}
	}

	//	�f�X�g���N�^
	GameWait::~GameWait( void )
	{
		SafeDelete( back );
		SafeDelete( nameUI );
		SafeDelete( view );

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			SafeDelete( targetTex[i] );
			SafeDelete( obj[i] );
		}
	}

	//	������
	void	GameWait::Initialize( int index, int* name )
	{
		this->index = index;

		//	�w�i�摜�ǂݍ���
		back = new iex2DObj( "DATA/UI/BackGround/matching_gamen_parts.png" );

		//	�o�b�N�o�b�t�@�|�C���^�ޔ�
		iexSystem::GetDevice()->GetRenderTarget( 0, &backBuffer );

		//	nameUI�ݒ�
		nameUI = new NameUI();
		nameUI->Initialize( 
			iexSystem::ScreenWidth / 4, ( int )( iexSystem::ScreenHeight * 0.89f ), 
			50, 50, name );

		//	���Ԑݒ�
		order[0] = index;
		int	 orderNum = 1;

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			if ( i != index )	
			{
				order[orderNum] = i;
				orderNum++;
			}

			//	�I�u�W�F�N�g������
			ObjInitialize( i );

			//	�J����������
			ViewInitialize( i );

			//	�e�N�X�`��������
			TextureInitialize( i );
		}
	}
	
	//	�I�u�W�F�N�g������
	void	GameWait::ObjInitialize( int index )
	{
		//	�e�N�X�`��������
		obj[index] = nullptr;
		obj[index] = new iex3DObj( "DATA/CHR/suppin/suppin.IEM" );

		//	�e�N�X�`�����ւ�
		char	fileName[256] = "DATA/CHR/suppin/s_body_";
		char playerNum[8] = "";
		sprintf_s( playerNum, "%d.png", index );
		strcat_s( fileName, playerNum );
		obj[index]->SetTexture( 0, fileName );

		//	�X�V
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

	//	�J����������
	void	GameWait::ViewInitialize( int index )
	{
			//	�J����������
			view = nullptr;
			view = new iexView();
			view->Set( Vector3( 0.0f, 2.0f, 5.0f ), Vector3( 0.0f, 1.5f, 0.0f ) );
	}

	//	�e�N�X�`��������
	void	GameWait::TextureInitialize( int index )
	{
		targetTex[index] = nullptr;
		targetTex[index] = new iex2DObj( iexSystem::ScreenWidth, iexSystem::ScreenHeight, IEX2D_RENDERTARGET );
	}

//----------------------------------------------------------------------------------
//	�X�V
//----------------------------------------------------------------------------------

	//	�X�V
	void	GameWait::Update( void )
	{
		//	���O�ʒu�X�V
		nameUI->Update();

		//	���f�����X�V
		UpdateInfo();
	}

	//	���X�V
	void	GameWait::UpdateInfo( void )
	{
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			obj[i]->Update();
			obj[i]->Animation();
		}
	}

//----------------------------------------------------------------------------------
//	�X�V
//----------------------------------------------------------------------------------

	//	�`��
	void	GameWait::Render( void )
	{
		//	���L�����`��
		MyCharacterRender();

		//	���v���C���[�`��
		for ( int i = 1; i < PLAYER_MAX; i++ )
		{
			OtherPlayerRender( i );
		}

		//	���O�`��
		nameUI->Render();

		VSRender();
	}

	//	���L�����`��
	void	GameWait::MyCharacterRender( void )
	{
		//	�����_�[�^�[�Q�b�g�ݒ�
		targetTex[index]->RenderTarget( 0 );

		//	��ʃN���A
		view->Activate();
		view->Clear();

		//	�w�i�`��
		iexSystem::GetDevice()->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
		back->Render( 320, 0, 640, iexSystem::ScreenHeight, 0, 0, 650, 720, RS_COPY, GetColor( 0.7f, 0.7f, 0.9f, 1.0f ) );
		iexSystem::GetDevice()->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

		//	�L�����N�^�[�`��
		obj[index]->Render();

		//	�t���[���o�b�t�@�֐؂�ւ�
		iexSystem::GetDevice()->SetRenderTarget( 0, backBuffer );

		//	�e�N�X�`���`��
		targetTex[index]->Render( 
			0, 0, iexSystem::ScreenWidth / 2, iexSystem::ScreenHeight,
			iexSystem::ScreenWidth / 4, 0,
			iexSystem::ScreenWidth / 2, iexSystem::ScreenHeight );
	}

	//	���L�����`��
	void	GameWait::OtherPlayerRender( int index )
	{
		//	�����_�[�^�[�Q�b�g�ݒ�
		targetTex[order[index]]->RenderTarget( 0 );

		//	��ʃN���A
		view->Activate();
		view->Clear();

		//	�w�i�`��
		iexSystem::GetDevice()->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
		back->Render( iexSystem::ScreenWidth / 4, iexSystem::ScreenHeight / 4, 
			iexSystem::ScreenWidth / 2, iexSystem::ScreenHeight / 3, 650, 0, 630, 240, RS_COPY, GetColor( 0.7f, 0.7f, 1.0f, 1.0f ) );
			iexSystem::GetDevice()->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );

		//	�L�����N�^�[�`��
		bool active = gameParam->GetPlayerActive( order[index] );
		if( active )obj[order[index]]->Render();
		//obj[order[index]]->Render();
		//	�t���[���o�b�t�@�֐؂�ւ�
		iexSystem::GetDevice()->SetRenderTarget( 0, backBuffer );
		
		//	�e�N�X�`���`��
		targetTex[order[index]]->Render( 
			iexSystem::ScreenWidth / 2, ( iexSystem::ScreenHeight / 3 ) * ( index - 1 ), 
			iexSystem::ScreenWidth / 2, iexSystem::ScreenHeight / 3,
			iexSystem::ScreenWidth / 4, iexSystem::ScreenHeight / 4,
			iexSystem::ScreenWidth / 2, iexSystem::ScreenHeight / 3 );
	}

	//	VS�`��
	void	GameWait::VSRender( void )
	{
		back->Render( 
			iexSystem::ScreenWidth / 2 - ( VS_SIZE / 2 ), 
			iexSystem::ScreenHeight / 2 - ( VS_SIZE / 2 ),
			VS_SIZE, VS_SIZE,
			650, 480, 325, 240 );
	}


