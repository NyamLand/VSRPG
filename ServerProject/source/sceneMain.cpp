
#include	"iextreme.h"
#include	<thread>
#include	"system/system.h"
#include	"GameParam.h"
#include	"GlobalFunction.h"
#include	"PlayerManager.h"

#include	"sceneMain.h"

//*****************************************************************************************************************************
//
//	グローバル変数
//
//*****************************************************************************************************************************

GameParam*	sceneMain::gameParam;

//*****************************************************************************************************************************
//
//	初期化
//
//*****************************************************************************************************************************

bool	sceneMain::Initialize( void )
{
	//	環境設定
	iexLight::SetAmbient( 0x404040 );
	iexLight::SetFog( 800, 1000, 0 );

	Vector3 dir( 1.0f, -1.0f, -0.5f );
	dir.Normalize();
	iexLight::DirLight( shader, 0, &dir, 0.8f, 0.8f, 0.8f );

	//	カメラ設定
	view = new iexView();
	view->Set( Vector3( 0, 3, -5 ), Vector3( 0, 0, 0 ) );

	//	ゲームパラメータ初期化
	gameParam = new GameParam();

	//	プレイヤー初期化
	playerManager->Initialize( gameParam );

	//	サーバー初期化
	gameParam->InitializeServer();

	return true;
}

sceneMain::~sceneMain( void )
{
	playerManager->Release();
	SafeDelete( view );
	SafeDelete( gameParam );

}

//*****************************************************************************************************************************
//
//		更新
//
//*****************************************************************************************************************************
void	sceneMain::Update( void )
{
	int client = gameParam->Receive();

	if ( client != -1 )
	{
		playerManager->Update( client );
		gameParam->Send( client );
	}
}

//*****************************************************************************************************************************
//
//		描画関連
//
//*****************************************************************************************************************************
void	sceneMain::Render( void )
{
	//	画面クリア
	view->Activate();
	view->Clear();

	gameParam->Render();






}




