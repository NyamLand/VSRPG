
#include	"iextreme.h"
#include	"system/Scene.h"
#include	"system/Framework.h"
#include	"GlobalFunction.h"
#include	"Interpolation.h"
#include	"GameData.h"
#include	"GameManager.h"
#include	"GameParam.h"
#include	"Camera.h"
#include	"InputManager.h"
#include	"sceneMatching.h"
#include	"PointManager.h"
#include	"Sound.h"
#include	"sceneTitle.h"
#include	"sceneResult.h"

//***************************************************************
//
//	sceneResult�N���X
//
//***************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

	//	������
	bool	sceneResult::Initialize( void )
	{
		//	���ݒ�
		iexLight::SetAmbient( 0x404040 );
		iexLight::SetFog( 800, 1000, 0 );

		//	���s���ݒ�
		Vector3 dir( 1.0f, -1.0f, -0.5f );
		dir.Normalize();
		iexLight::DirLight( shader, 0, &dir, 0.8f, 0.8f, 0.8f );
		
		//	�J����������
		mainView = new Camera();

		//	�摜�ǂݍ���
		back = new iex2DObj( "DATA/UI/BackGround/result_UI.png" );
		lovelive = new iex2DObj( "DATA/UI/BackGround/lovelive.png" );

		//	�T�C���A�E�g
		gameParam->CloseClient();

		//	�ϐ�������
		alpha = 0.0f;
		percentage = 0.0f;
		pushState = false;

		//	BGM�Đ�
		sound->PlayBGM( BGM::RESULT );

		//	���U���g������
		result = new Result();
		result->Initialize(gameParam->GetMyIndex());

		pointManager->Sort();

		return	true;
	}

	//	���
	sceneResult::~sceneResult( void )
	{
		SafeDelete( mainView );
		SafeDelete( back );
		SafeDelete( lovelive );
		SafeDelete( gameParam );
		//gameManager->Release();
		SafeDelete( result );
		sound->StopBGM();
	}

//----------------------------------------------------------------------------------------------
//	�X�V�E�`��
//----------------------------------------------------------------------------------------------

	//	�X�V
	void	sceneResult::Update( void )
	{
		//result->Update();
		if ( !pushState )
		{
			if ( KEY( KEY_SPACE ) == 3 ||
				KEY( KEY_ENTER ) == 3 ||
				KEY( KEY_A ) == 3 )	pushState = true;
		}

		if ( pushState )
		{
			MainFrame->ChangeScene( new sceneTitle() );
			return;
		}
	}

	//	�`��
	void	sceneResult::Render( void )
	{
		mainView->Activate();
		mainView->Clear();

		char str[256];

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			int player = pointManager->GetPlayer( i );
			sprintf(str, "%d��	    %dP	   score : %d", i + 1, player + 1, pointManager->GetPoint( player ) );
			IEX_DrawText( str, 600, 300 + i * 50, 200, 200, 0xFFFFFFFF );
		}

		//back->Render( 0, 0, iexSystem::ScreenWidth, iexSystem::ScreenHeight, 0, 0, 1280, 720 );
		//lovelive->Render( 0, 0, iexSystem::ScreenWidth, iexSystem::ScreenHeight, 0, 0, 2048, 1024, RS_COPY, GetColor( 1.0f, 1.0f, 1.0f, alpha ) );
		//result->Render();
	}
