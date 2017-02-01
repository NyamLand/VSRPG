
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
//	sceneResultクラス
//
//***************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	初期化
	bool	sceneResult::Initialize( void )
	{
		//	環境設定
		iexLight::SetAmbient( 0x404040 );
		iexLight::SetFog( 800, 1000, 0 );

		//	平行光設定
		Vector3 dir( 1.0f, -1.0f, -0.5f );
		dir.Normalize();
		iexLight::DirLight( shader, 0, &dir, 0.8f, 0.8f, 0.8f );
		
		//	カメラ初期化
		mainView = new Camera();
		mainView->Initialize( Camera::VIEW_MODE::FIX_VIEW,
			Vector3( 0.0f, 50.0f, 200.0f ),
			Vector3( 0.0f, 3.0f, 300.0f ) );

		//	画像読み込み
		back = new iex2DObj( "DATA/UI/BackGround/result_UI.png" );

		testResult = new TestResult();

		//	サインアウト
		gameParam->CloseClient();

		//	BGM再生
		sound->PlayBGM( BGM::RESULT );

		pointManager->Sort();

		int index = 0;
		viewPos = Vector3( 0.0f, 50.0f, 200.0f );

		return	true;
	}

	//	解放
	sceneResult::~sceneResult( void )
	{
		SafeDelete( mainView );
		SafeDelete( back );
		SafeDelete( gameParam );
		SafeDelete( testResult );
		sound->StopBGM();
	}

//----------------------------------------------------------------------------------------------
//	更新・描画
//----------------------------------------------------------------------------------------------

	//	更新
	void	sceneResult::Update( void )
	{
		if ( KEY( KEY_TYPE::A ) == 3 )
		{
			MainFrame->ChangeScene( new sceneTitle() );
			return;
		}
	}

	//	描画
	void	sceneResult::Render( void )
	{
		mainView->Activate();
		mainView->Clear();

		//	リザルト描画
		testResult->Render();

		char str[256];

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			int player = pointManager->GetPlayer( i );
			sprintf(str, "%d位	    %dP	   score : %d", i + 1, player + 1, pointManager->GetPoint( player ) );
			IEX_DrawText( str, 600, 300 + i * 50, 200, 200, 0xFFFFFFFF );
		}
	}
