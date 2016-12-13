
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
//	sceneTitleクラス
//
//***************************************************************

//-----------------------------------------------------------------------------------
//	グローバル
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
//	初期化・解放
//-----------------------------------------------------------------------------------

	//	初期化
	bool	sceneTitle::Initialize( void )
	{
		//	環境設定
		iexLight::SetAmbient( 0x404040 );
		iexLight::SetFog( 800, 1000, 0 );

		Vector3 dir( 1.0f, -1.0f, -0.5f );
		dir.Normalize();
		iexLight::DirLight( shader, 0, &dir, 0.8f, 0.8f, 0.8f );

		//	カメラ初期化
		mainView = new Camera();

		//	画像初期化
		bg = new iex2DObj( "DATA/UI/BackGround/lovelive.png" );
		//bg = new iex2DObj( "DATA/UI/BackGround/title.png" );
		lovelive = new iex2DObj( "DATA/UI/BackGround/title.png" );
		//lovelive = new iex2DObj( "DATA/UI/BackGround/lovelive.png" );

		//	ｂｇｍ再生
		sound->PlayBGM( BGM::TITLE );

		//	screen設定
		screen->SetScreenMode( SCREEN_MODE::WHITE_IN, 0.01f );

		pushState = false;
		percentage = 0.0f;
		alpha = 1.0f;
		step = TITLE_STEP::FADE_IN;

		font = new Font( "メイリオ" );
		font2 = new Font( "HG行書体" );

		return	true;
	}

	//	解放
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
//	更新・描画
//-----------------------------------------------------------------------------------

	//	更新
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

	//	描画
	void	sceneTitle::Render( void )
	{
		//	camera
		mainView->Activate();
		mainView->Clear();

		//	bg描画
		//lovelive->Render( 0, 0, iexSystem::ScreenWidth, iexSystem::ScreenHeight, 0, 0, 2048, 1024 );
		//lovelive->Render(0, 0, iexSystem::ScreenWidth, iexSystem::ScreenHeight, 0, 0, 1280, 720 );
		//bg->Render( 0, 0, iexSystem::ScreenWidth, iexSystem::ScreenHeight, 0, 0, 2048, 1024, RS_COPY, GetColor( 1.0f, 1.0f, 1.0f, alpha ) );
		//bg->Render( 0, 0, iexSystem::ScreenWidth, iexSystem::ScreenHeight, 0, 0, 1280, 720, RS_COPY, GetColor( 1.0f, 1.0f, 1.0f, alpha ) );

		//	スクリーン制御
		screen->Render();

		LPSTR str = "大阪王将";
		LPSTR str2 = "ぎょうざ";
		font->DrawFont( str2, 640, 100, 500, 500, 0xFFFFFFFF );
		font2->DrawFont( str, 640, 360, 500, 500, 0xFFFFFFFF );
	}

//-----------------------------------------------------------------------------------
//	動作関数
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//	情報設定
//-----------------------------------------------------------------------------------