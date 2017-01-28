
#include	"iextreme.h"
#include	"system/Framework.h"
#include	"system/system.h"
#include	<fstream>
#include	<iostream>
#include	<thread>
#include	<process.h>
#include	<vector>
#include	"PlayerManager.h"
#include	"Random.h"
#include	"GlobalFunction.h"
#include	"Image.h"
#include	"GameData.h"
#include	"GameParam.h"
#include	"GameManager.h"
#include	"UIManager.h"
#include	"Camera.h"
#include	"Sound.h"
#include	"Screen.h"

//
#include	"BaseEquipment.h"
//

#include	"sceneMain.h"
#include	"sceneMatching.h"

//*****************************************************************************************************************************
//
//	グローバル変数
//
//*****************************************************************************************************************************

namespace
{
	namespace MATCHING_MODE
	{
		enum
		{
			NAME_INPUT,
			SIGN_UP,
			ITEM_SELECT,
			WAIT
		};
	}
}

bool	sceneMatching::threadState;

//*****************************************************************************************************************************
//
//	初期化
//
//*****************************************************************************************************************************

	//	初期化
	bool	sceneMatching::Initialize( void )
	{
		//	環境設定
		iexLight::SetAmbient( 0x404040 );
		iexLight::SetFog( 800, 1000, 0 );

		//	ライト設定
		Vector3 dir( 1.0f, -1.0f, -0.5f );
		dir.Normalize();
		iexLight::DirLight( shader, 0, &dir, 0.8f, 0.8f, 0.8f );

		//	カメラ設定
		mainView = new Camera();
		mainView->Initialize( Camera::VIEW_MODE::TRACKING_VIEW,
			Vector3( 0.0f, 5.0f, -20.0f ), Vector3( 0.0f, 3.0f, 0.0f ) );

		//	NameInput画面初期化
		nameInput = new NameInput();

		//	ItemSelect初期化
		itemSelect = new ItemSelect();

		//	GameWait初期化
		gameWait = new GameWait();

		//	GameParam初期化
		gameParam = new GameParam();

		//	WaitLoad初期化
		waitLoad = new WaitLoad();

		//	PlayerManager初期化
		playerManager->Initialize();
	
		//	テキスト読み込み
		std::ifstream	ifs( "onlineInfo.txt" );
		ifs >> addr;
		ifs >> name;

		//	BGM再生( ランダムで言い訳のテーマ )
		if ( random->PercentageRandom( 0.2f ) )	sound->PlayBGM( BGM::IIWAKE );
		else	sound->PlayBGM( BGM::MENU );

		//	変数初期化
		step = MATCHING_MODE::NAME_INPUT;
		nextScene = SCENE::MAIN;

		//	画面演出初期化
		screen->SetScreenMode( SCREEN_MODE::WHITE_IN, 0.01f );

		threadState = false;
		return true;
	}

	//	解放
	sceneMatching::~sceneMatching( void )
	{
		SafeDelete( mainView );
		SafeDelete( nameInput );
		SafeDelete( itemSelect );
		SafeDelete( gameWait );
		SafeDelete( waitLoad );
		sound->StopBGM();
	}

//*****************************************************************************************************************************
//
//		更新
//
//*****************************************************************************************************************************
	
	//	全体更新
	void	sceneMatching::Update( void )
	{
		waitLoad->Update();

		//	テスト
		switch ( step )
		{
		case MATCHING_MODE::NAME_INPUT:
			//	スクリーン処理完了まで待機
			if ( !screen->GetScreenState() )	break;
			
			//	名前入力
			if ( nameInput->Update() )
			{
				step = MATCHING_MODE::SIGN_UP;
			}
			if ( nameInput->GetCancelState() )
			{
				screen->SetScreenMode( SCREEN_MODE::WHITE_OUT, 0.01f );
				nextScene = SCENE::TITLE;
			}
			break;

		case MATCHING_MODE::SIGN_UP:
			//	クライアント初期化( serverと接続 )
			if ( gameParam->InitializeClient( addr, 7000, nameInput->GetName() ) )
			{
				int id = gameParam->GetMyIndex();
				itemSelect->Initialize( id );
				gameWait->Initialize( id );
				step = MATCHING_MODE::ITEM_SELECT;
				_beginthread( ThreadFunc, 0, NULL );
			}
			break;

		case MATCHING_MODE::ITEM_SELECT:
			{
				//	アイテム選択更新
				bool selectOK = itemSelect->Update();
				if ( selectOK )
				{
					gameParam->SendMatching();
					step = MATCHING_MODE::WAIT;
				}
			}

		case MATCHING_MODE::WAIT:
			//	プレイヤー情報送信
			gameParam->SendPlayerInfo();

			//	待機画面更新
			gameWait->Update();
			break;
		}

		screen->Update();

		//	シーン切り替え
		if ( threadState )
		{
			gameManager->ChangeScene( nextScene );
		}
	}

//*****************************************************************************************************************************
//
//		描画関連
//
//*****************************************************************************************************************************
	
	//	描画
	void	sceneMatching::Render( void )
	{
		//	画面クリア
		mainView->Activate();
		mainView->Clear();

		waitLoad->Render();

		switch ( step )
		{
		case MATCHING_MODE::NAME_INPUT:
			nameInput->Render();
			break;

		case MATCHING_MODE::SIGN_UP:
			break;

		case MATCHING_MODE::ITEM_SELECT:
		case MATCHING_MODE::WAIT:
			gameWait->Render();
			itemSelect->Render();
			break;
		}

		//	画面制御
		screen->Render();

		//	debug描画
		DebugRender();
	}

//*****************************************************************************************************************************
//
//		描画関連
//
//*****************************************************************************************************************************

//	debug用描画
void	sceneMatching::DebugRender( void )
{
	for ( int p = 0; p < PLAYER_MAX; p++ )
	{
		//	各プレイヤーログインしているかどうか
		PlayerParam	playerParam = gameParam->GetPlayerParam( p );
		int active = gameParam->GetPlayerActive( p );

		char	str[256];
		char	str2[256];

		if ( gameParam->GetMatchingInfo( p ).isComplete == false )sprintf_s( str2, "Enterキーを押してください" );
		else sprintf_s( str2, "準備完了" );

		if ( active )
		{
			sprintf_s( str, "%dP pos = 接続中 : %s", p + 1, str2 );
		}
		else
		{
			sprintf_s( str, "%dP pos = 待機中 : %s", p + 1, str2 );
		}
		IEX_DrawText( str, 20, 300 + p * 50, 500, 200, 0xFFFFFF00 );
	}
}

//	自分の情報表示
void	sceneMatching::MyInfoRender( void )
{
	//	自分のID( Player番号 )
	int	 id = gameParam->GetMyIndex();

	//	自分の名前
	LPSTR name = gameParam->GetPlayerName()->GetName( id );

	//	表示
	char	str[256];
	//sprintf_s(str, "id : %d\n\nname : %s\n\npos : Vector3( %.2f, %.2f, %.2f )", id + 1, name, pos.x, pos.y, pos.z);
	IEX_DrawText( str, 20, 50, 500, 500, 0xFFFFFF00 );
}


void	sceneMatching::ThreadFunc( void* ptr )
{
	for (;;)
	{
		//	サーバーから情報受信
		gameParam->Receive();

		//	thread終了
		if ( gameManager->GetChangeSceneFrag() )	break;
	}

	threadState = true;
	_endthread();
}



