
#include	"iextreme.h"
#include	<vector>
#include	"system/Scene.h"
#include	"system/Framework.h"
#include	"GlobalFunction.h"
#include	"Interpolation.h"
#include	"GameData.h"
#include	"GameManager.h"
#include	"GameParam.h"
#include	"Random.h"
#include	"Camera.h"
#include	"InputManager.h"
#include	"sceneMatching.h"
#include	"Sound.h"
#include	"Screen.h"
#include	"Font.h"
#include	"CSVReader.h"
#include	"sceneTitle.h"

//***************************************************************
//
//	sceneTitle�N���X
//
//***************************************************************

CSVReader*	reader = nullptr;

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
			FADE_OUT,
		};
	}
}

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

		//	�������Đ�
		sound->PlayBGM( BGM::TITLE );

		//	screen�ݒ�
		screen->SetScreenMode( SCREEN_MODE::WHITE_IN, 0.01f );

		step = TITLE_STEP::FADE_IN;

		fstream		fstr( "DATA/player_data.csv" );
		reader = new CSVReader( fstr, DEFAULT_SEPARATOR, DEFAULT_QUOTE_CHARACTER );


		return	true;
	}

	//	���
	sceneTitle::~sceneTitle( void )
	{
		SafeDelete( mainView );
		SafeDelete( bg );
		SafeDelete( reader );
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
				screen->SetScreenMode( SCREEN_MODE::WHITE_OUT, 0.01f );
				step++;
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
		static	const LPSTR	technique[] =
		{
			"copy",
			"blackWhite",
			"negaPosi"
		};

		static int tec = random->GetInt( 0, 2 );
		bg->Render( 0, 0, 
			iexSystem::ScreenWidth, iexSystem::ScreenHeight, 
			0, 0, 1280, 720, shader2D, technique[tec] );

		//	�X�N���[������
		screen->Render();
	}

//-----------------------------------------------------------------------------------
//	����֐�
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//	���ݒ�
//-----------------------------------------------------------------------------------