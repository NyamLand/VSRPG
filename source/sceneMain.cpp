
#include	"iextreme.h"
#include	"system/system.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"Camera.h"
#include	"PlayerManager.h"

#include	"sceneMain.h"

//*****************************************************************************************************************************
//
//	グローバル変数
//
//*****************************************************************************************************************************

iexMesh*	stage = nullptr;	//	仮(絶対消す)



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
	mainView = new Camera();
	mainView->Initialize(
		Camera::VIEW_MODE::TRACKING_VIEW,
		Vector3( 0.0f, 15.0f, -15.0f ),
		Vector3( 0.0f, 3.0f, 0.0f ) );

	//	player設定
	playerManager->Initialize();

	stage = new iexMesh( "DATA/BG/2_1/FIELD2_1.IMO" );

	return true;
}

sceneMain::~sceneMain( void )
{
	SafeDelete( mainView );
	SafeDelete( stage );
	playerManager->Release();



}

//*****************************************************************************************************************************
//
//		更新
//
//*****************************************************************************************************************************
void	sceneMain::Update( void )
{
	//	gameManager更新
	gameManager->Update();

	//	player更新
	playerManager->Update();

	//	camera更新
	mainView->Update( playerManager->GetPlayer()->GetPos() );
}

//*****************************************************************************************************************************
//
//		描画関連
//
//*****************************************************************************************************************************
void	sceneMain::Render( void )
{
	//	画面クリア
	mainView->Activate();
	mainView->Clear();

	stage->Render();

	//	player描画
	playerManager->Render();

}



