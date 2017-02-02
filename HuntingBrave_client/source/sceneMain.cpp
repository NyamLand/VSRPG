
#include	"iextreme.h"
#include	"system/system.h"
#include	<fstream>
#include	<iostream>
#include	<vector>
#include	<thread>
#include	<map>
#include	<process.h>
#include	"Screen.h"
#include	"GlobalFunction.h"
#include	"Interpolation.h"
#include	"Image.h"
#include	"DrawShape.h"
#include	"GameData.h"
#include	"GameParam.h"
#include	"GameManager.h"
#include	"UIManager.h"
#include	"TimeUpUI.h"
#include	"Camera.h"
#include	"PlayerManager.h"
#include	"EnemyManager.h"
#include	"MagicManager.h"
#include	"EffectManager.h"
#include	"LevelManager.h"
#include	"NameManager.h"
#include	"ItemManager.h"
#include	"PointManager.h"
#include	"NetEnemyManager.h"
#include	"Collision.h"
#include	"Sound.h"

#include	"sceneMain.h"

//*****************************************************************************************************************************
//
//	グローバル変数
//
//*****************************************************************************************************************************

#define	BLACK_WHITE_SPEED		0.01f
#define	MAP_SIZE		250
#define	MAP_POS_X		1150
#define	MAP_POS_Y		130
#define	MAP_SRC_SIZE	720

bool	sceneMain::threadState;

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

	//	カメラ初期化
	mainView->AngleInit( gameParam->GetMyIndex() );

	//	stage初期化
	stage = new Stage();

	//	player初期化
	playerManager->Initialize();

	//	enemy初期化
	enemyManager->Initialize();

	//	netEnemy初期化
	netEnemyManager->Initialize();

	//	magic初期化
	magicManager->Initialize();

	//	uiの設定
	uiManager->Initialize();

	//	level初期化
	levelManager->Initialize();

	//	Effect初期化
	effectManager->Initialize();

	//	point初期化
	pointManager->Initialize();

	//	collision初期化
	collision->Initialize(gameParam->GetMyIndex(), "DATA/BG/stage_atari.IMO" );

	//	particle初期化
	particle->Initialize();

	//	送信
	gameParam->SendResponseInfo( RESPONSE_COMMAND::GAME_START );

	//	戦闘BGM
	sound->PlayBGM( BGM::MAIN );

	//	バックバッファポインタ退避
	iexSystem::GetDevice()->GetRenderTarget( 0, &backBuffer );
	mainScreen = new iex2DObj( iexSystem::ScreenWidth, iexSystem::ScreenHeight, IEX2D_RENDERTARGET );

	screen->SetScreenMode( SCREEN_MODE::FADE_IN, 0.01f );

	blackWhitePercentage = 0.0f;

	_beginthread( ThreadFunction, 0, nullptr );
	threadState = false;

	//	タイムアップ用
	timeUp = new TimeUpUI();
	return true;
}

sceneMain::~sceneMain( void )
{
	SafeDelete( mainView );
	SafeDelete( stage );
	SafeDelete( mainScreen );
	SafeDelete( timeUp );
	backBuffer->Release();
	enemyManager->Release();
	netEnemyManager->Release();
	uiManager->Release();
	magicManager->Release();
	//playerManager->Release();
	effectManager->Release();
	particle->Release();
	collision->Release();
	sound->StopBGM();
}

//*****************************************************************************************************************************
//
//		更新
//
//*****************************************************************************************************************************
void	sceneMain::Update( void )
{
	//	送信
	//if (!threadState){
		gameParam->Send();
	//}

	//	経過時間取得
	float elapseTime = GetElapseTime();

	//	GameManager更新
	gameManager->Update();

	//	player更新
	playerManager->Update();

	//	enemy更新
	enemyManager->Update();

	//	netEnemy更新
	netEnemyManager->Update();

	//	magic更新
	magicManager->Update();

	//	item更新
	itemManager->Update();

	//	ui更新
	uiManager->Update();

	//	Effect更新
	effectManager->Update();

	//	camera更新
	int index = gameParam->GetMyIndex();
	mainView->Update( playerManager->GetPlayer( index )->GetPos() );

	//	collision
	collision->AllCollision();

	//	particle
	particle->Update();

	//	スクリーン制御
	screen->Update();
	DeadScreen();

	//	シーン切り替え
	if ( threadState ){
	//	sound->PlaySE(SE::TIME_END);
	//	if (timeUp->Update() == true && sound->GetSEState(SE::TIME_END) == true)	
		gameManager->ChangeScene(SCENE::RESULT);
	}
}

//*****************************************************************************************************************************
//
//		描画関連
//
//*****************************************************************************************************************************
void	sceneMain::Render( void )
{
	//	レンダーターゲット設定
	mainScreen->RenderTarget( 0 );

	//	画面クリア
	mainView->Activate();
	mainView->Clear();

	//	stage描画
	stage->Render();

	//	player描画
	playerManager->Render();

	//	enemy描画
	enemyManager->Render();
	
	//	netEnemy描画
	netEnemyManager->Render();

	//	magic描画
	magicManager->Render();

	//	effect描画
	effectManager->Render();

	//	particle描画
	particle->Render();

	stage->GetTexture()->Render(IMAGE_MODE::NORMAL, MAP_POS_X, MAP_POS_Y, MAP_SIZE, MAP_SIZE,
		280, 0, MAP_SRC_SIZE, MAP_SRC_SIZE);

	//	ui描画
	uiManager->Render();
	
	screen->Render();

	//	各プレイヤー座標表示
	//DebugRender();

	//MyInfoRender();

	timeUp->Render();

	//	フレームバッファへ切り替え
	iexSystem::GetDevice()->SetRenderTarget( 0, backBuffer );

	shader2D->SetValue( "percentage", blackWhitePercentage );
	mainScreen->Render( 0, 0, 1280, 720, 0, 0, 1280, 720, shader2D, "blackWhiteOutSet" );
}

//	debug用描画
void	sceneMain::DebugRender( void )
{
	PlayerStatus	playerStatus = gameParam->GetPlayerStatus();

	int life = gameParam->GetPlayerParam( gameParam->GetMyIndex() ).life;
	int atk = playerStatus.power;
	int def = playerStatus.defense;
	int mgcAtk = playerStatus.magicPower;
	int mgcDef = playerStatus.magicDefense;

	char str[256];
	sprintf( str, "life = %d\npower = %d\ndefense = %d\nmagicAttack = %d\nmagicDefense = %d\n", life, atk, def, mgcAtk, mgcDef );
	IEX_DrawText( str, 20, 300, 500, 500, 0xFFFFFF00 );
}

//	自分の情報表示
void	sceneMain::MyInfoRender( void )
{
	//	自分のID( Player番号 )
	int	 id = gameParam->GetMyIndex();
	
	//	自分の名前
	LPSTR name = gameParam->GetPlayerName()->GetName( id );
	nameManager->SetNameIndex( id, name );

	//	自分の座標
	Vector3	pos = playerManager->GetPlayer( id )->GetPos();

	//	中心からの距離
	float			length = Vector3( Vector3( 0.0f, 0.0f, 0.0f ) - pos ).Length();
	//	経験値
	int	exp = levelManager->GetExp();

	//	表示
	char	str[256];
	sprintf_s( str, "id : %d\n\nname : %s\n\npos : Vector3( %.2f, %.2f, %.2f )\n\nexp : %d\n\nlength : %.2f", id + 1, name, pos.x, pos.y, pos.z, exp, length );
	IEX_DrawText( str, 20, 50, 500, 500, 0xFFFFFF00 );
}

//	生存チェック
void	sceneMain::DeadScreen( void )
{
	int index = gameParam->GetMyIndex();
	
	//	生存していたらスキップ
	if ( gameParam->GetPlayerParam( index ).motion != MOTION_NUM::DEAD )
	{
		blackWhitePercentage = 0.0f;
		return;
	}

	//	補間処理
	bool state = Interpolation::PercentageUpdate( blackWhitePercentage, BLACK_WHITE_SPEED );
}

//	受信送信
void	sceneMain::ThreadFunction( void* ptr )
{
	//	サーバーから情報受信
	for (;;)
	{
		gameParam->Receive();

		if ( gameManager->GetChangeSceneFrag() )	break;
	}

	threadState = true;
	_endthread();
}









