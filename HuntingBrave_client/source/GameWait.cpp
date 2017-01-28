
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

#define	TITLE_UI_POS_X			1115
#define	TITLE_INIT_HEIGHT	65
#define	TITLE_POS_SPACE		240

#define	NAME_UI_POS_X			1115
#define	NAME_INIT_HEIGHT	175
#define	NAME_POS_SPACE		240	

//----------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------

	//	�R���X�g���N�^
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

	//	�f�X�g���N�^
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

	//	������
	void	GameWait::Initialize( int index )
	{
		this->index = index;

		//	�w�i�摜�ǂݍ���
		back = new iex2DObj( "DATA/UI/BackGround/matching_gamen_parts.png" );

		//	�o�b�N�o�b�t�@�|�C���^�ޔ�
		iexSystem::GetDevice()->GetRenderTarget( 0, &backBuffer );

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

			//	NameUI������
			NameUIInitialize( i );

			//	playerTitleUI������
			PlayerTitleUIInitialize( i );
		}
	}
	
	//	�I�u�W�F�N�g������
	void	GameWait::ObjInitialize( int index )
	{
		//	�e�N�X�`��������
		obj[index] = nullptr;
		obj[index] = new iex3DObj( "DATA/CHR/suppin/suppin.IEM" );

		//	�e�N�X�`�����ւ�
		char	fileName[256] = "DATA/CHR/suppin/body_";
		char playerNum[8] = "";
		sprintf_s( playerNum, "%d.png", index + 1 );
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

	//	NameUI������
	void	GameWait::NameUIInitialize( int index )
	{
		//	nameUI�ݒ�
		nameUI[index] = new NameUI();

		nameUI[index]->Initialize(
			iexSystem::ScreenWidth / 4, ( int )( iexSystem::ScreenHeight * 0.89f ),
			50, 50 );
	}

	//	PlayerTitleUI������
	void	GameWait::PlayerTitleUIInitialize( int index )
	{
		//	playerTitleUI������
		playerTitleUI[index] = new PlayerTitleUI();
		playerTitleUI[index]->Initialize( 
			0, 0, 
			iexSystem::ScreenWidth / 4, 
			65, 
			150, 100 );
	}

//----------------------------------------------------------------------------------
//	�X�V
//----------------------------------------------------------------------------------

	//	�X�V
	void	GameWait::Update( void )
	{
		//	���O�X�V
		UpdateName();

		//	�̍��X�V
		UpdatePlayerTitle();

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

	//	���OUI�X�V
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

	//	�v���C���[�̍��X�V
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
		NameUIRender();

		//	�̍��`��
		PlayerTitleUIRender();

		//	VS�`��
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

	//	���OUI�`��
	void	GameWait::NameUIRender( void )
	{
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			bool active = gameParam->GetPlayerActive( order[i] );
			if ( active )
				nameUI[order[i]]->Render();
		}
	}

	//	�v���C���[�̍�UI�`��
	void	GameWait::PlayerTitleUIRender( void )
	{
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			bool active = gameParam->GetPlayerActive( order[i] );
			if ( active )
				playerTitleUI[order[i]]->Render();
		}
	}


