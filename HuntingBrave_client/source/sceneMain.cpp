
#include	"iextreme.h"
#include	"system/system.h"
#include	<fstream>
#include	<iostream>
#include	<thread>
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
#include	"Collision.h"

//
#include	"BaseEquipment.h"
//

#include	"sceneMain.h"

//*****************************************************************************************************************************
//
//	グローバル変数
//
//*****************************************************************************************************************************

iexMesh*	stage = nullptr;	//	仮(絶対消す)
BaseEquipment* baseEquipment;	//	仮(絶対消す)

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

	//	GameParam初期化
	gameParam = new GameParam();
	
	//	カメラ設定
	mainView = new Camera();
	mainView->Initialize(
		Camera::VIEW_MODE::TRACKING_VIEW,
		Vector3( 0.0f, 15.0f, -15.0f ),
		Vector3( 0.0f, 3.0f, 0.0f ) );

	//	player設定
	playerManager->Initialize();

	//	enemy設定
	enemyManager->Initialize();
	
	//	stage設定
	stage = new iexMesh( "DATA/BG/2_1/FIELD2_1.IMO" );

	baseEquipment = new BaseEquipment("DATA\\player_data.csv");

	//	uiの設定
	uiManager->Initialize();

	//	GameManagerの初期化
	gameManager->Initialize();

	//	テキスト読み込み
	char addr[64], name[17];
	std::ifstream	ifs( "onlineInfo.txt" );
	ifs >> addr;
	ifs >> name;

	//	クライアント初期化( serverと接続 )
	if ( !gameParam->InitializeClient( addr, 7000, name ) )
	{
		MessageBox(iexSystem::Window, "クライアント初期化失敗!", "ERROR!", MB_OK );
		exit( 0 );
		return	false;
	}
	return true;
}

sceneMain::~sceneMain( void )
{
	SafeDelete( mainView );
	SafeDelete( stage );
	SafeDelete( gameParam );
	playerManager->Release();
	enemyManager->Release();
	uiManager->Release();
	

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
	printf( "経過時間 : %f\n", elapseTime );

	//	送受信
	std::thread		ThreadFunc( ThreadFunction );
	ThreadFunc.join();

	//	GameManager更新
	gameManager->Update();

	//	player更新
	playerManager->Update();

	//	enemy更新
	enemyManager->Update();

	//	ui更新
	uiManager->Update();

	//	camera更新
	int index = gameParam->GetMyIndex();
	mainView->Update( playerManager->GetPlayer( index )->GetPos() );

	//	collision
	collision->AllCollision();
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

	//	ui描画
	uiManager->Render();

	//	各プレイヤー座標表示
	DebugRender();

	MyInfoRender();
}

//	debug用描画
void	sceneMain::DebugRender( void )
{
	for ( int p = 0; p < PLAYER_MAX; p++ )
	{
		//	各プレイヤー座標描画
		PlayerParam	playerParam = gameParam->GetPlayerParam( p );
		int	point = gameParam->GetPointInfo( p ).point;
		Vector3	p_pos = playerParam.pos;
		char	str[256];
		sprintf_s( str, "%dP pos = Vector3( %.2f, %.2f, %.2f ), score = %d",  p + 1, p_pos.x, p_pos.y, p_pos.z, point );
		IEX_DrawText( str, 20 , 300 + p * 50, 500, 200, 0xFFFFFF00 );
	}
}

//	自分の情報表示
void	sceneMain::MyInfoRender( void )
{
	//	自分のID( Player番号 )
	int	 id = gameParam->GetMyIndex();
	
	//	自分の名前
	LPSTR name = gameParam->GetPlayerName( id );
	
	//	自分の座標
	Vector3	pos = playerManager->GetPlayer( id )->GetPos();

	//	表示
	char	str[256];
	sprintf_s( str, "id : %d\n\nname : %s\n\npos : Vector3( %.2f, %.2f, %.2f )", id + 1, name, pos.x, pos.y, pos.z );
	IEX_DrawText( str, 20, 50, 500, 500, 0xFFFFFF00 );
}

//	受信送信
void	sceneMain::ThreadFunction( void )
{
	//	サーバーから情報受信
	gameParam->Update();
}









