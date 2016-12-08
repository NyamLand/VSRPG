
#include	"iextreme.h"
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

//----------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------

	//	�R���X�g���N�^
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

	//	�f�X�g���N�^
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
			iexSystem::ScreenWidth / 4, ( int )( iexSystem::ScreenHeight * 0.8f ), 
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
			obj[index]->SetAngle( D3DX_PI * 0.25f );
			obj[index]->SetPos( -0.8f, 0.0f, 0.0f );
		}
		obj[index]->SetScale( 0.1f );
		obj[index]->Update();
	}

	//	�J����������
	void	GameWait::ViewInitialize( int index )
	{
			//	�J����������
			view[index] = nullptr;
			view[index] = new iexView();
			view[index]->Set( Vector3( 0.0f, 2.0f, 5.0f ), Vector3( 0.0f, 1.5f, 0.0f ) );
	}

	//	�e�N�X�`��������
	void	GameWait::TextureInitialize( int index )
	{
		targetTex[index] = nullptr;
		targetTex[index] = new iex2DObj( iexSystem::ScreenWidth, iexSystem::ScreenHeight, IEX2D_RENDERTARGET );
	}

//----------------------------------------------------------------------------------
//	�X�V�E�`��
//----------------------------------------------------------------------------------

	//	�X�V
	void	GameWait::Update( void )
	{
		nameUI->Update();
		UpdateInfo();
	}

	//	�`��
	void	GameWait::Render( void )
	{
		//	��ʃN���A
		MyCharacterRender();
		for ( int i = 1; i < PLAYER_MAX; i++ )
		{
			OtherPlayerRender( i );
		}

		nameUI->Render();
	}

	//	���L�����`��
	void	GameWait::MyCharacterRender( void )
	{
		//	�����_�[�^�[�Q�b�g�ݒ�
		targetTex[index]->RenderTarget( 0 );

		//	��ʃN���A
		view[index]->Activate();
		view[index]->Clear();

		//	�w�i�`��
		iexSystem::GetDevice()->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
		back->Render( iexSystem::ScreenWidth / 5, 0, iexSystem::ScreenWidth / 5 * 3, iexSystem::ScreenHeight, 0, 0, 650, 720 );
		iexSystem::GetDevice()->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

		//	�L�����N�^�[�`��
		obj[index]->Render();

		//	�t���[���o�b�t�@�֐؂�ւ�
		iexSystem::GetDevice()->SetRenderTarget( 0, backBuffer );

		//	�e�N�X�`���`��
		targetTex[index]->Render( 
			0, 0, iexSystem::ScreenWidth / 2, iexSystem::ScreenHeight,
			iexSystem::ScreenWidth / 5, 0,
			iexSystem::ScreenWidth / 5 * 3, iexSystem::ScreenHeight );
	}

	//	���L�����`��
	void	GameWait::OtherPlayerRender( int index )
	{
		//	�����_�[�^�[�Q�b�g�ݒ�
		targetTex[order[index]]->RenderTarget( 0 );

		//	��ʃN���A
		view[order[index]]->Activate();
		view[order[index]]->Clear();

		//	�w�i�`��
		iexSystem::GetDevice()->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
		back->Render( 0, iexSystem::ScreenHeight / 4, 
			iexSystem::ScreenWidth / 5 * 4, iexSystem::ScreenHeight / 3, 650, 0, 650, 240 );
		iexSystem::GetDevice()->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE );

		//	�L�����N�^�[�`��
		bool active = gameParam->GetPlayerActive( order[index] );
		if( active )obj[order[index]]->Render();

		//	�t���[���o�b�t�@�֐؂�ւ�
		iexSystem::GetDevice()->SetRenderTarget( 0, backBuffer );
		
		//	�e�N�X�`���`��
		targetTex[order[index]]->Render( 
			iexSystem::ScreenWidth / 2, ( iexSystem::ScreenHeight / 3 ) * ( index - 1 ), 
			iexSystem::ScreenWidth / 2, iexSystem::ScreenHeight / 3,
			0, iexSystem::ScreenHeight / 4,
			iexSystem::ScreenWidth / 5 * 4, iexSystem::ScreenHeight / 3 );
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
//	�O���[�o��
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------
//----------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------


