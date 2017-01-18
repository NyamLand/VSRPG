
#include	"iextreme.h"
#include	"system/Framework.h"
#include	"system/Scene.h"
#include	"system/System.h"
#include	<process.h>
#include	"GlobalFunction.h"
#include	"Camera.h"
#include	"sceneMain.h"
#include	"sceneMatching.h"
#include	"sceneResult.h"
#include	"sceneTitle.h"
#include	"sceneLoad.h"

//***************************************************************
//
//	sceneLoadクラス
//
//***************************************************************

//----------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------

bool	sceneLoad::threadState;

//----------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------

	//	初期化
	sceneLoad::sceneLoad( Scene* nextScene ) : newScene( nextScene )
	{
		threadState = false;
	}

	//	初期化
	bool	sceneLoad::Initialize( void )
	{
		//	環境設定
		iexLight::SetAmbient( 0x404040 );
		iexLight::SetFog( 800, 1000, 0 );

		//	ライト設定
		Vector3 dir( 1.0f, -1.0f, -0.5f );
		dir.Normalize();
		iexLight::DirLight( shader, 0, &dir, 0.8f, 0.8f, 0.8f );

		//	カメラ初期化
		view = new iexView();

		//	waitLoad初期化
		waitLoad = new WaitLoad();

		//	別thread作成
		_beginthread( Thread, 0, ( void* )newScene );

		return	true;
	}

	//	解放
	sceneLoad::~sceneLoad( void )
	{
		SafeDelete( view );
		SafeDelete( waitLoad );
	}

//----------------------------------------------------------------------------------
//	更新・描画
//----------------------------------------------------------------------------------

	//	更新
	void	sceneLoad::Update( void )
	{
		//	ロード演出
		waitLoad->Update();

		if ( threadState )
		{
			MainFrame->ChangeScene( newScene, false );
			return;
		}
	}

	//	描画
	void	sceneLoad::Render( void )
	{
		view->Activate();
		view->Clear();

		//	ロード演出
		waitLoad->Render();
	}

//----------------------------------------------------------------------------------
//	動作関数
//----------------------------------------------------------------------------------

	//	スレッド動作
	void	sceneLoad::Thread( void* arg )
	{
		//	並列させる処理
		Scene*	scene = ( Scene* )arg;
		scene->Initialize();

		//	スレッド終了
		threadState = true;
		_endthread();
	}

//----------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------

