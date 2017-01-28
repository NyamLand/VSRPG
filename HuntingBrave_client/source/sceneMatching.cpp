
#include	"iextreme.h"
#include	"system/Framework.h"
#include	"system/system.h"
#include	<fstream>
#include	<iostream>
#include	<thread>
#include	<process.h>
#include	<vector>
#include	"PlayerManager.h"
#include	"Random.h"
#include	"GlobalFunction.h"
#include	"Image.h"
#include	"GameData.h"
#include	"GameParam.h"
#include	"GameManager.h"
#include	"UIManager.h"
#include	"Camera.h"
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
			ITEM_SELECT,
			WAIT
		};
	}
}

bool	sceneMatching::threadState;

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

		//	���C�g�ݒ�
		Vector3 dir( 1.0f, -1.0f, -0.5f );
		dir.Normalize();
		iexLight::DirLight( shader, 0, &dir, 0.8f, 0.8f, 0.8f );

		//	�J�����ݒ�
		mainView = new Camera();
		mainView->Initialize( Camera::VIEW_MODE::TRACKING_VIEW,
			Vector3( 0.0f, 5.0f, -20.0f ), Vector3( 0.0f, 3.0f, 0.0f ) );

		//	NameInput��ʏ�����
		nameInput = new NameInput();

		//	ItemSelect������
		itemSelect = new ItemSelect();

		//	GameWait������
		gameWait = new GameWait();

		//	GameParam������
		gameParam = new GameParam();

		//	WaitLoad������
		waitLoad = new WaitLoad();

		//	PlayerManager������
		playerManager->Initialize();
	
		//	�e�L�X�g�ǂݍ���
		std::ifstream	ifs( "onlineInfo.txt" );
		ifs >> addr;
		ifs >> name;

		//	BGM�Đ�( �����_���Ō�����̃e�[�} )
		if ( random->PercentageRandom( 0.2f ) )	sound->PlayBGM( BGM::IIWAKE );
		else	sound->PlayBGM( BGM::MENU );

		//	�ϐ�������
		step = MATCHING_MODE::NAME_INPUT;
		nextScene = SCENE::MAIN;

		//	��ʉ��o������
		screen->SetScreenMode( SCREEN_MODE::WHITE_IN, 0.01f );

		threadState = false;
		return true;
	}

	//	���
	sceneMatching::~sceneMatching( void )
	{
		SafeDelete( mainView );
		SafeDelete( nameInput );
		SafeDelete( itemSelect );
		SafeDelete( gameWait );
		SafeDelete( waitLoad );
		sound->StopBGM();
	}

//*****************************************************************************************************************************
//
//		�X�V
//
//*****************************************************************************************************************************
	
	//	�S�̍X�V
	void	sceneMatching::Update( void )
	{
		waitLoad->Update();

		//	�e�X�g
		switch ( step )
		{
		case MATCHING_MODE::NAME_INPUT:
			//	�X�N���[�����������܂őҋ@
			if ( !screen->GetScreenState() )	break;
			
			//	���O����
			if ( nameInput->Update() )
			{
				step = MATCHING_MODE::SIGN_UP;
			}
			if ( nameInput->GetCancelState() )
			{
				screen->SetScreenMode( SCREEN_MODE::WHITE_OUT, 0.01f );
				nextScene = SCENE::TITLE;
			}
			break;

		case MATCHING_MODE::SIGN_UP:
			//	�N���C�A���g������( server�Ɛڑ� )
			if ( gameParam->InitializeClient( addr, 7000, nameInput->GetName() ) )
			{
				int id = gameParam->GetMyIndex();
				itemSelect->Initialize( id );
				gameWait->Initialize( id );
				step = MATCHING_MODE::ITEM_SELECT;
				_beginthread( ThreadFunc, 0, NULL );
			}
			break;

		case MATCHING_MODE::ITEM_SELECT:
			{
				//	�A�C�e���I���X�V
				bool selectOK = itemSelect->Update();
				if ( selectOK )
				{
					gameParam->SendMatching();
					step = MATCHING_MODE::WAIT;
				}
			}

		case MATCHING_MODE::WAIT:
			//	�v���C���[��񑗐M
			gameParam->SendPlayerInfo();

			//	�ҋ@��ʍX�V
			gameWait->Update();
			break;
		}

		screen->Update();

		//	�V�[���؂�ւ�
		if ( threadState )
		{
			gameManager->ChangeScene( nextScene );
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

		waitLoad->Render();

		switch ( step )
		{
		case MATCHING_MODE::NAME_INPUT:
			nameInput->Render();
			break;

		case MATCHING_MODE::SIGN_UP:
			break;

		case MATCHING_MODE::ITEM_SELECT:
		case MATCHING_MODE::WAIT:
			gameWait->Render();
			itemSelect->Render();
			break;
		}

		//	��ʐ���
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
	LPSTR name = gameParam->GetPlayerName()->GetName( id );

	//	�\��
	char	str[256];
	//sprintf_s(str, "id : %d\n\nname : %s\n\npos : Vector3( %.2f, %.2f, %.2f )", id + 1, name, pos.x, pos.y, pos.z);
	IEX_DrawText( str, 20, 50, 500, 500, 0xFFFFFF00 );
}


void	sceneMatching::ThreadFunc( void* ptr )
{
	for (;;)
	{
		//	�T�[�o�[�������M
		gameParam->Receive();

		//	thread�I��
		if ( gameManager->GetChangeSceneFrag() )	break;
	}

	threadState = true;
	_endthread();
}



