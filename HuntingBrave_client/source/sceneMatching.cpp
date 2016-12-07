
#include	"iextreme.h"
#include	"system/Framework.h"
#include	"system/system.h"
#include	<fstream>
#include	<iostream>
#include	<thread>
#include	"Random.h"
#include	"GlobalFunction.h"
#include	"Image.h"
#include	"GameData.h"
#include	"GameParam.h"
#include	"GameManager.h"
#include	"UIManager.h"
#include	"Camera.h"
#include	"PlayerManager.h"
#include	"Sound.h"
#include	"Screen.h"

//
#include	"BaseEquipment.h"
//

#include	"sceneMain.h"
#include	"sceneMatching.h"

//*****************************************************************************************************************************
//
//	�O���[�o���ϐ�
//
//*****************************************************************************************************************************

namespace
{
	namespace MATCHING_MODE
	{
		enum
		{
			NAME_INPUT,
			SIGN_UP,
			WAIT
		};
	}
}

//*****************************************************************************************************************************
//
//	������
//
//*****************************************************************************************************************************

	//	������
	bool	sceneMatching::Initialize( void )
	{
		//	���ݒ�
		iexLight::SetAmbient( 0x404040 );
		iexLight::SetFog( 800, 1000, 0 );

		Vector3 dir( 1.0f, -1.0f, -0.5f );
		dir.Normalize();
		iexLight::DirLight( shader, 0, &dir, 0.8f, 0.8f, 0.8f );

		//	�J�����ݒ�
		mainView = new Camera();
		mainView->Initialize(
			Camera::VIEW_MODE::TRACKING_VIEW,
			Vector3( 0.0f, 5.0f, -20.0f ),
			Vector3( 0.0f, 3.0f, 0.0f ) );

		//	NameInput��ʏ�����
		nameInput = new NameInput();

		//	ItemSelect������
		itemSelect = new ItemSelect();

		//	���f��������
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			obj[i] = nullptr;
			obj[i] = new iex3DObj( "DATA/CHR/suppin/suppin.IEM" );		
			char	fileName[256] = "DATA/CHR/suppin/s_body_";
			char playerNum[8] = "";
			sprintf_s( playerNum, "%d.png", i );
			strcat_s( fileName, playerNum );
			obj[i]->SetTexture( 0, fileName );
		}

		//	GameParam������
		gameParam = new GameParam();
	
		//	�e�L�X�g�ǂݍ���
		std::ifstream	ifs( "onlineInfo.txt" );
		ifs >> addr;
		ifs >> name;

		//	�摜�ǂݍ���
		back = new iex2DObj( "DATA/UI/BackGround/matching_gamen.png" );

		//	BGM�Đ�( �����_���Ō�����̃e�[�} )
		if ( random->PercentageRandom( 0.2f ) )	sound->PlayBGM( BGM::IIWAKE );
		else	sound->PlayBGM( BGM::MENU );

		step = MATCHING_MODE::NAME_INPUT;
		nextScene = SCENE::MAIN;

		screen->SetScreenMode( SCREEN_MODE::WHITE_IN, 0.01f );
		return true;
	}

	//	���
	sceneMatching::~sceneMatching( void )
	{
		SafeDelete( mainView );
		SafeDelete( back );
		SafeDelete( nameInput );
		SafeDelete( itemSelect );
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			SafeDelete( obj[ p ] );
		}
		sound->StopBGM();

		playerManager->Release();
	}

//*****************************************************************************************************************************
//
//		�X�V
//
//*****************************************************************************************************************************
	
	//	�S�̍X�V
	void	sceneMatching::Update( void )
	{
		//	�e�X�g
		switch ( step )
		{
		case MATCHING_MODE::NAME_INPUT:
			//	�X�N���[�����������܂őҋ@
			if ( !screen->GetScreenState() )	break;
			
			//	���O����
			if( nameInput->Update() )	step = MATCHING_MODE::SIGN_UP;
			if ( nameInput->GetCancelState() )
			{
				screen->SetScreenMode( SCREEN_MODE::WHITE_OUT, 0.01f );
				nextScene = SCENE::TITLE;
			}
			break;

		case MATCHING_MODE::SIGN_UP:
			//	�N���C�A���g������( server�Ɛڑ� )
			if ( gameParam->InitializeClient( addr, 7000, name ) )
			{
				itemSelect->Initialize( gameParam->GetMyIndex() );
				step = MATCHING_MODE::WAIT;
			}
			break;

		case MATCHING_MODE::WAIT:
			//	�T�[�o�[�������M
			gameParam->Update();

			//	GameManager�X�V
			gameManager->Update();

			//	�A�C�e���I���X�V
			itemSelect->Update();
	
			//	���f���X�V
			ObjUpdate();

			if ( KEY_Get( KEY_ENTER ) == 3 )
			{
				gameParam->SendMatching();
			}
			break;
		}

		//	�V�[���؂�ւ�
		if ( screen->Update() )		gameManager->ChangeScene( nextScene );
	}

	//	�I�u�W�F�N�g�X�V
	void	sceneMatching::ObjUpdate( void )
	{
		//�ڑ����Ă邩�ǂ��������̊m�F�̂��߁A���W�����`��̓N���C�A���g�ł������E�E�E�悭�Ȃ��H
		Vector3 temppos;
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			temppos = Vector3( -10.0f + i * 5.0f, 0, 0 );
			int active = gameParam->GetPlayerActive( i );

			if ( active )
			{
				obj[i]->SetPos( temppos );
				obj[i]->SetAngle( 180 * PI / 180 );
				obj[i]->SetScale( 0.2f );
				obj[i]->Animation();
				obj[i]->Update();
			}
		}
	}

//*****************************************************************************************************************************
//
//		�`��֘A
//
//*****************************************************************************************************************************
	
	//	�`��
	void	sceneMatching::Render( void )
	{
		//	��ʃN���A
		mainView->Activate();
		mainView->Clear();

		//	back
		iexSystem::GetDevice()->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
		back->Render( 0, 0, iexSystem::ScreenWidth, iexSystem::ScreenHeight, 0, 0, 1280, 720 );
		iexSystem::GetDevice()->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );

		//	�v���C���[���f���`��
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			int active = gameParam->GetPlayerActive( i );

			if ( active )	obj[i]->Render();
		}

		switch ( step )
		{
		case MATCHING_MODE::NAME_INPUT:
			nameInput->Render();
			break;

		case MATCHING_MODE::SIGN_UP:
			break;

		case MATCHING_MODE::WAIT:
			itemSelect->Render();
			break;
		}

		screen->Render();

		//	debug�`��
		DebugRender();
	}

//*****************************************************************************************************************************
//
//		�`��֘A
//
//*****************************************************************************************************************************

//	debug�p�`��
void	sceneMatching::DebugRender( void )
{
	for ( int p = 0; p < PLAYER_MAX; p++ )
	{
		//	�e�v���C���[���O�C�����Ă��邩�ǂ���
		PlayerParam	playerParam = gameParam->GetPlayerParam( p );
		int active = gameParam->GetPlayerActive( p );

		char	str[256];
		char	str2[256];

		if ( gameParam->GetMatchingInfo( p ).isComplete == false )sprintf_s( str2, "Enter�L�[�������Ă�������" );
		else sprintf_s( str2, "��������" );

		if ( active )
		{
			sprintf_s( str, "%dP pos = �ڑ��� : %s", p + 1, str2 );
		}
		else
		{
			sprintf_s( str, "%dP pos = �ҋ@�� : %s", p + 1, str2 );
		}
		IEX_DrawText( str, 20, 300 + p * 50, 500, 200, 0xFFFFFF00 );
	}
}

//	�����̏��\��
void	sceneMatching::MyInfoRender( void )
{
	//	������ID( Player�ԍ� )
	int	 id = gameParam->GetMyIndex();

	//	�����̖��O
	LPSTR name = gameParam->GetPlayerName(id);

	//	�\��
	char	str[256];
	//sprintf_s(str, "id : %d\n\nname : %s\n\npos : Vector3( %.2f, %.2f, %.2f )", id + 1, name, pos.x, pos.y, pos.z);
	IEX_DrawText(str, 20, 50, 500, 500, 0xFFFFFF00);
}







