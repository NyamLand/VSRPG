
#include	"iextreme.h"
#include	"system/system.h"
#include	<fstream>
#include	<iostream>
#include	<vector>
#include	<thread>
#include	<map>
#include	"GlobalFunction.h"
#include	"Image.h"
#include	"DrawShape.h"
#include	"GameData.h"
#include	"GameParam.h"
#include	"GameManager.h"
#include	"UIManager.h"
#include	"Camera.h"
#include	"PlayerManager.h"
#include	"EnemyManager.h"
#include	"MagicManager.h"
#include	"LevelManager.h"
#include	"NameManager.h"
#include	"ItemManager.h"
#include	"Collision.h"
#include	"Sound.h"

#include	"sceneMain.h"

//*****************************************************************************************************************************
//
//	グローバル変数
//
//*****************************************************************************************************************************

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

	//	stage初期化
	stage = new Stage();

	//	player初期化
	playerManager->Initialize();

	//	enemy初期化
	enemyManager->Initialize();

	//	magic初期化
	magicManager->Initialize();

	//	uiの設定
	uiManager->Initialize();

	//	戦闘BGM
	sound->PlayBGM( BGM::MAIN );

	//	送信
	gameParam->SendResponseInfo( RESPONSE_COMMAND::GAME_START );

	return true;
}

sceneMain::~sceneMain( void )
{
	SafeDelete( mainView );
	SafeDelete( stage );
	enemyManager->Release();
	uiManager->Release();
	magicManager->Release();
	playerManager->Release();
	sound->StopBGM();
}

//*****************************************************************************************************************************
//
//		更新
//
//*****************************************************************************************************************************
void	sceneMain::Update( void )
{
	//	経過時間取得
	float elapseTime = GetElapseTime();

	//	送受信
	std::thread		ThreadFunc( ThreadFunction );
	ThreadFunc.join();

	//	GameManager更新
	gameManager->Update();

	//	player更新
	playerManager->Update();

	//	enemy更新
	enemyManager->Update();

	//	magic更新
	magicManager->Update();

	//	item更新
	itemManager->Update();

	//	ui更新
	uiManager->Update();

	//	camera更新
	int index = gameParam->GetMyIndex();
	mainView->Update( playerManager->GetPlayer( index )->GetPos() );

	//	collision
	collision->AllCollision();

	//	シーン切り替え
	gameManager->ChangeScene( SCENE::RESULT );
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

	//	stage描画
	stage->Render();

	//	player描画
	playerManager->Render();

	//	enemy描画
	enemyManager->Render();

	//	magic描画
	magicManager->Render();

	//	ui描画
	uiManager->Render();

	//	各プレイヤー座標表示
	DebugRender();

	MyInfoRender();
}

//	debug用描画
void	sceneMain::DebugRender( void )
{
	PlayerStatus	playerStatus = gameParam->GetPlayerStatus();

	int atk = playerStatus.power;
	int def = playerStatus.defense;
	int mgcAtk = playerStatus.magicPower;
	int mgcDef = playerStatus.magicDefense;

	char str[256];
	sprintf( str, "power = %d\ndefense = %d\nmagicAttack = %d\nmagicDefense = %d\n", atk, def, mgcAtk, mgcDef );
	IEX_DrawText( str, 20, 300, 500, 500, 0xFFFFFF00 );
}

//	自分の情報表示
void	sceneMain::MyInfoRender( void )
{
	//	自分のID( Player番号 )
	int	 id = gameParam->GetMyIndex();
	
	//	自分の名前
	LPSTR name = gameParam->GetPlayerName( id );
	nameManager->SetNameIndex( id, name );

	//	自分の座標
	Vector3	pos = playerManager->GetPlayer( id )->GetPos();

	//	経験値
	int	exp = levelManager->GetExp();

	//	表示
	char	str[256];
	sprintf_s( str, "id : %d\n\nname : %s\n\npos : Vector3( %.2f, %.2f, %.2f )\n\nexp : %d", id + 1, name, pos.x, pos.y, pos.z, exp );
	IEX_DrawText( str, 20, 50, 500, 500, 0xFFFFFF00 );
}

//	受信送信
void	sceneMain::ThreadFunction( void )
{
	//	サーバーから情報受信
	gameParam->Update();
}









