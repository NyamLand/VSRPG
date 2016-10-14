
#include	"iextreme.h"
#include	"system/system.h"
#include	<fstream>
#include	<iostream>
#include	<string>
#include	<thread>
#include	"GlobalFunction.h"
#include	"DrawShape.h"
#include	"GameParam.h"
#include	"GameData.h"
#include	"GameManager.h"
#include	"UIManager.h"
#include	"Camera.h"
#include	"PlayerManager.h"



//
#include	"BaseEquipment.h"
//

#pragma comment( lib, "WSOCK32.lib" )

#include	"sceneMain.h"

//*****************************************************************************************************************************
//
//	グローバル変数
//
//*****************************************************************************************************************************

iexMesh*	stage = nullptr;	//	仮(絶対消す)
//BaseEquipment* baseEquipment;	//	仮(絶対消す)
GameParam*	sceneMain::m_GameParam = nullptr;


//*****************************************************************************************************************************
//
//	初期化
//
//*****************************************************************************************************************************

bool	sceneMain::Initialize( void )
{
	//	WinSock初期化
	WSADATA	wsaData;
	WSAStartup( MAKEWORD( 1, 1 ), &wsaData );

	//	環境設定
	iexLight::SetAmbient( 0x404040 );
	iexLight::SetFog( 800, 1000, 0 );

	Vector3 dir( 1.0f, -1.0f, -0.5f );
	dir.Normalize();
	iexLight::DirLight( shader, 0, &dir, 0.8f, 0.8f, 0.8f );
	
	//	GameParam初期化
	m_GameParam = new GameParam();
	gameParam = m_GameParam;

	//	カメラ設定
	mainView = new Camera();
	mainView->Initialize(
		Camera::VIEW_MODE::TRACKING_VIEW,
		Vector3( 0.0f, 15.0f, -15.0f ),
		Vector3( 0.0f, 3.0f, 0.0f ) );

	//	player設定
	playerManager->Initialize();

	//	stage設定
	stage = new iexMesh( "DATA/BG/2_1/FIELD2_1.IMO" );

	//	uiの設定
	uiManager->Initialize();

	//	GameManagerの初期化
	gameManager->Initialize();

	//	テキスト読み込み
	char addr[64], name[64];
	std::ifstream	ifs( "onlineInfo.txt" );
	ifs >> addr;
	ifs >> name;

	//	クライアント初期化( serverと接続 )
	if ( !m_GameParam->InitializeClient( addr, PORT_NUM, name, 0 ) )
	{
		MessageBox( iexSystem::Window, "クライアント初期化失敗", "ERROR", MB_OK );
		PostQuitMessage( 0 );
		return	false;
	}




	//仮
	//baseEquipment = new BaseEquipment();
	
	return true;
}

sceneMain::~sceneMain( void )
{
	SafeDelete( mainView );
	SafeDelete( stage );
	SafeDelete( m_GameParam );
	playerManager->Release();
	uiManager->Release();

	//	WinSock終了
	WSACleanup();
}

//*****************************************************************************************************************************
//
//		更新
//
//*****************************************************************************************************************************
void	sceneMain::Update( void )
{
	//	受信処理は別スレッドで回しておく
	std::thread		threadFunc1( ThreadFunc1 );
	std::thread		threadFunc2( ThreadFunc2 );
	threadFunc1.join();
	threadFunc2.join();
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

	//	ui描画
	uiManager->Render();

	//	各プレイヤー座標表示
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			PlayerParam	playerParam = m_GameParam->GetPlayerParam( p );
			Vector3	p_pos = playerParam.pos;
			char	str[256];
			sprintf_s( str, "%dP pos = Vector3( %.2f, %.2f, %.2f )",  p + 1, p_pos.x, p_pos.y, p_pos.z );
			IEX_DrawText( str, 20 , 300 + p * 50, 500, 200, 0xFFFFFF00 );

			//	自分はスキップ
			if ( m_GameParam->GetMyIndex() == p )	continue;

			//	仮で球体描画
			if ( m_GameParam->GetPlayerInfo(p).active )
			{
				//	球体描画
				drawShape->DrawSphereMesh( playerParam.pos, 1.5f, 0xFFFFFF00 );
			}
		}
	}

	MyInfoRender();
}

//	仮

//	自分の情報表示
void	sceneMain::MyInfoRender( void )
{
	//	自分のID( Player番号 )
	int	 id = m_GameParam->GetMyIndex();
	
	//	自分の名前
	LPSTR name = m_GameParam->GetMyInfo( id ).name;
	
	//	自分の座標
	Vector3	pos = m_GameParam->GetPlayerParam( id ).pos;

	//	表示
	char	str[256];
	sprintf_s( str, "id : %d\n\nname : %s\n\npos : Vector3( %.2f, %.2f, %.2f )", id + 1, name, pos.x, pos.y, pos.z );
	IEX_DrawText( str, 20, 50, 500, 500, 0xFFFFFF00 );
}

void	sceneMain::ThreadFunc1( void )
{
	m_GameParam->Receive();
}

void	sceneMain::ThreadFunc2( void )
{
	//	サーバーへの情報送信
	m_GameParam->Update();

	//	GameManager更新
	gameManager->Update();

	//	player更新
	playerManager->Update();

	//	ui更新
	uiManager->Update();

	//	camera更新
	mainView->Update( playerManager->GetPlayer()->GetPos() );
}








