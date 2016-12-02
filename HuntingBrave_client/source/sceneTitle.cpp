
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
#include	"Sound.h"
#include	"sceneTitle.h"

//***************************************************************
//
//	sceneTitle�N���X
//
//***************************************************************

//-----------------------------------------------------------------------------------
//	�O���[�o��
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//	�������E���
//-----------------------------------------------------------------------------------

	//	������
	bool	sceneTitle::Initialize( void )
	{
		//	���ݒ�
		iexLight::SetAmbient( 0x404040 );
		iexLight::SetFog( 800, 1000, 0 );

		Vector3 dir( 1.0f, -1.0f, -0.5f );
		dir.Normalize();
		iexLight::DirLight( shader, 0, &dir, 0.8f, 0.8f, 0.8f );

		//	�J����������
		mainView = new Camera();

		//	�摜������
		bg = new iex2DObj( "DATA/UI/BackGround/title.png" );
		lovelive = new iex2DObj( "DATA/UI/BackGround/lovelive.png" );

		//	�������Đ�
		sound->PlayBGM( BGM::TITLE );

		pushState = false;
		percentage = 0.0f;
		alpha = 1.0f;
		return	true;
	}

	//	���
	sceneTitle::~sceneTitle( void )
	{
		SafeDelete( mainView );
		SafeDelete( bg );
		sound->StopBGM();
	}

//-----------------------------------------------------------------------------------
//	�X�V�E�`��
//-----------------------------------------------------------------------------------

	//	�X�V
	void	sceneTitle::Update( void )
	{
		if ( !pushState )
		{
			if ( KEY( KEY_B ) == 3 || 
				KEY( KEY_SPACE ) == 3 || 
				KEY( KEY_ENTER ) == 3 || 
				KEY( KEY_A ) == 3 )	pushState = true; 
		}
		else
		{
			//Interpolation::PercentageUpdate( percentage, 0.01f );
			//
			//bool	state = Interpolation::LinearInterpolation( alpha, 1.0f, 0.5f, percentage );

			//if ( state )
			//{
				MainFrame->ChangeScene( new sceneMatching() );
				return;
			//}
		}
	}

	//	�`��
	void	sceneTitle::Render( void )
	{
		//	camera
		mainView->Activate();
		mainView->Clear();

		//	bg�`��
		lovelive->Render( 0, 0, iexSystem::ScreenWidth, iexSystem::ScreenHeight, 0, 0, 2048, 1024 );
		bg->Render( 0, 0, iexSystem::ScreenWidth, iexSystem::ScreenHeight, 0, 0, 1280, 720, RS_COPY, GetColor( 1.0f, 1.0f, 1.0f, alpha ) );
	}

//-----------------------------------------------------------------------------------
//	����֐�
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//	���ݒ�
//-----------------------------------------------------------------------------------