
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
#include	"Screen.h"
#include	"Font.h"
#include	"sceneTitle.h"

//***************************************************************
//
//	sceneTitle�N���X
//
//***************************************************************

//-----------------------------------------------------------------------------------
//	�O���[�o��
//-----------------------------------------------------------------------------------

namespace
{
	namespace TITLE_STEP
	{
		enum
		{
			FADE_IN,
			WAIT,
			FADE_OUT,
		};
	}
}

Font*	font = nullptr;
Font*	font2 = nullptr;

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
		bg = new iex2DObj( "DATA/UI/BackGround/lovelive.png" );
		//bg = new iex2DObj( "DATA/UI/BackGround/title.png" );
		lovelive = new iex2DObj( "DATA/UI/BackGround/title.png" );
		//lovelive = new iex2DObj( "DATA/UI/BackGround/lovelive.png" );

		//	�������Đ�
		sound->PlayBGM( BGM::TITLE );

		//	screen�ݒ�
		screen->SetScreenMode( SCREEN_MODE::WHITE_IN, 0.01f );

		pushState = false;
		percentage = 0.0f;
		alpha = 1.0f;
		step = TITLE_STEP::FADE_IN;

		font = new Font( "���C���I" );
		font2 = new Font( "HG�s����" );

		return	true;
	}

	//	���
	sceneTitle::~sceneTitle( void )
	{
		SafeDelete( mainView );
		SafeDelete( bg );
		SafeDelete( lovelive );
		SafeDelete( font );
		SafeDelete( font2 );
		sound->StopBGM();
	}

//-----------------------------------------------------------------------------------
//	�X�V�E�`��
//-----------------------------------------------------------------------------------

	//	�X�V
	void	sceneTitle::Update( void )
	{
		switch ( step )
		{
		case TITLE_STEP::FADE_IN:
			if ( !screen->Update() )	break;
			if ( KEY( KEY_B ) == 3 || 
				KEY( KEY_SPACE ) == 3 || 
				KEY( KEY_ENTER ) == 3 || 
				KEY( KEY_A ) == 3 )
			{
				step++;
			}
			break;

		case TITLE_STEP::WAIT:
			{
				Interpolation::PercentageUpdate( percentage, 0.01f );
				bool	state = Interpolation::LinearInterpolation( alpha, 1.0f, 0.0f, percentage );
				if ( state )
				{
					screen->SetScreenMode( SCREEN_MODE::WHITE_OUT, 0.01f );
					step++;
				}
			}
			break;

		case TITLE_STEP::FADE_OUT:
			if ( !screen->Update() )	break;
			MainFrame->ChangeScene( new sceneMatching() );
			return;
			break;
		}
	}

	//	�`��
	void	sceneTitle::Render( void )
	{
		//	camera
		mainView->Activate();
		mainView->Clear();

		//	bg�`��
		//lovelive->Render( 0, 0, iexSystem::ScreenWidth, iexSystem::ScreenHeight, 0, 0, 2048, 1024 );
		//lovelive->Render(0, 0, iexSystem::ScreenWidth, iexSystem::ScreenHeight, 0, 0, 1280, 720 );
		//bg->Render( 0, 0, iexSystem::ScreenWidth, iexSystem::ScreenHeight, 0, 0, 2048, 1024, RS_COPY, GetColor( 1.0f, 1.0f, 1.0f, alpha ) );
		//bg->Render( 0, 0, iexSystem::ScreenWidth, iexSystem::ScreenHeight, 0, 0, 1280, 720, RS_COPY, GetColor( 1.0f, 1.0f, 1.0f, alpha ) );

		//	�X�N���[������
		screen->Render();

		LPSTR str = "��㉤��";
		LPSTR str2 = "���傤��";
		font->DrawFont( str2, 640, 100, 500, 500, 0xFFFFFFFF );
		font2->DrawFont( str, 640, 360, 500, 500, 0xFFFFFFFF );
	}

//-----------------------------------------------------------------------------------
//	����֐�
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//	���ݒ�
//-----------------------------------------------------------------------------------