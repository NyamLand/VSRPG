
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
//	sceneTitleクラス
//
//***************************************************************

//-----------------------------------------------------------------------------------
//	グローバル
//-----------------------------------------------------------------------------------

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
		bg = new iex2DObj( "DATA/UI/BackGround/title.png" );
		lovelive = new iex2DObj( "DATA/UI/BackGround/lovelive.png" );

		//	ｂｇｍ再生
		sound->PlayBGM( BGM::TITLE );

		pushState = false;
		percentage = 0.0f;
		alpha = 1.0f;
		return	true;
	}

	//	解放
	sceneTitle::~sceneTitle( void )
	{
		SafeDelete( mainView );
		SafeDelete( bg );
		sound->StopBGM();
	}

//-----------------------------------------------------------------------------------
//	更新・描画
//-----------------------------------------------------------------------------------

	//	更新
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

	//	描画
	void	sceneTitle::Render( void )
	{
		//	camera
		mainView->Activate();
		mainView->Clear();

		//	bg描画
		lovelive->Render( 0, 0, iexSystem::ScreenWidth, iexSystem::ScreenHeight, 0, 0, 2048, 1024 );
		bg->Render( 0, 0, iexSystem::ScreenWidth, iexSystem::ScreenHeight, 0, 0, 1280, 720, RS_COPY, GetColor( 1.0f, 1.0f, 1.0f, alpha ) );
	}

//-----------------------------------------------------------------------------------
//	動作関数
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//	情報設定
//-----------------------------------------------------------------------------------