
#include	"iextreme.h"
#include	"system/Framework.h"
#include	"system/system.h"
#include	<fstream>
#include	<iostream>
#include	<thread>
#include	"Random.h"
#include	"GlobalFunction.h"
#include	"Image.h"
#include	"GameData.h"
#include	"GameParam.h"
#include	"GameManager.h"
#include	"UIManager.h"
#include	"Camera.h"
#include	"PlayerManager.h"
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
			WAIT
		};
	}
}

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

		Vector3 dir( 1.0f, -1.0f, -0.5f );
		dir.Normalize();
		iexLight::DirLight( shader, 0, &dir, 0.8f, 0.8f, 0.8f );

		//	カメラ設定
		mainView = new Camera();
		mainView->Initialize(
			Camera::VIEW_MODE::TRACKING_VIEW,
			Vector3( 0.0f, 5.0f, -20.0f ),
			Vector3( 0.0f, 3.0f, 0.0f ) );

		//	NameInput画面初期化
		nameInput = new NameInput();

		//	ItemSelect初期化
		itemSelect = new ItemSelect();

		//	モデル初期化
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			obj[i] = nullptr;
			obj[i] = new iex3DObj( "DATA/CHR/suppin/suppin.IEM" );		
			char	fileName[256] = "DATA/CHR/suppin/s_body_";
			char playerNum[8] = "";
			sprintf_s( playerNum, "%d.png", i );
			strcat_s( fileName, playerNum );
			obj[i]->SetTexture( 0, fileName );
		}

		//	GameParam初期化
		gameParam = new GameParam();
	
		//	テキスト読み込み
		std::ifstream	ifs( "onlineInfo.txt" );
		ifs >> addr;
		ifs >> name;

		//	画像読み込み
		back = new iex2DObj( "DATA/UI/BackGround/matching_gamen.png" );

		//	BGM再生( ランダムで言い訳のテーマ )
		if ( random->PercentageRandom( 0.2f ) )	sound->PlayBGM( BGM::IIWAKE );
		else	sound->PlayBGM( BGM::MENU );

		step = MATCHING_MODE::NAME_INPUT;
		nextScene = SCENE::MAIN;

		screen->SetScreenMode( SCREEN_MODE::WHITE_IN, 0.01f );
		return true;
	}

	//	解放
	sceneMatching::~sceneMatching( void )
	{
		SafeDelete( mainView );
		SafeDelete( back );
		SafeDelete( nameInput );
		SafeDelete( itemSelect );
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			SafeDelete( obj[ p ] );
		}
		sound->StopBGM();

		playerManager->Release();
	}

//*****************************************************************************************************************************
//
//		更新
//
//*****************************************************************************************************************************
	
	//	全体更新
	void	sceneMatching::Update( void )
	{
		//	テスト
		switch ( step )
		{
		case MATCHING_MODE::NAME_INPUT:
			//	スクリーン処理完了まで待機
			if ( !screen->GetScreenState() )	break;
			
			//	名前入力
			if( nameInput->Update() )	step = MATCHING_MODE::SIGN_UP;
			if ( nameInput->GetCancelState() )
			{
				screen->SetScreenMode( SCREEN_MODE::WHITE_OUT, 0.01f );
				nextScene = SCENE::TITLE;
			}
			break;

		case MATCHING_MODE::SIGN_UP:
			//	クライアント初期化( serverと接続 )
			if ( gameParam->InitializeClient( addr, 7000, name ) )
			{
				itemSelect->Initialize( gameParam->GetMyIndex() );
				step = MATCHING_MODE::WAIT;
			}
			break;

		case MATCHING_MODE::WAIT:
			//	サーバーから情報受信
			gameParam->Update();

			//	GameManager更新
			gameManager->Update();

			//	アイテム選択更新
			itemSelect->Update();
	
			//	モデル更新
			ObjUpdate();

			if ( KEY_Get( KEY_ENTER ) == 3 )
			{
				gameParam->SendMatching();
			}
			break;
		}

		//	シーン切り替え
		if ( screen->Update() )		gameManager->ChangeScene( nextScene );
	}

	//	オブジェクト更新
	void	sceneMatching::ObjUpdate( void )
	{
		//接続してるかどうかだけの確認のため、座標決定や描画はクライアントでもいい・・・よくない？
		Vector3 temppos;
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			temppos = Vector3( -10.0f + i * 5.0f, 0, 0 );
			int active = gameParam->GetPlayerActive( i );

			if ( active )
			{
				obj[i]->SetPos( temppos );
				obj[i]->SetAngle( 180 * PI / 180 );
				obj[i]->SetScale( 0.2f );
				obj[i]->Animation();
				obj[i]->Update();
			}
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

		//	back
		iexSystem::GetDevice()->SetRenderState( D3DRS_ZENABLE, D3DZB_FALSE );
		back->Render( 0, 0, iexSystem::ScreenWidth, iexSystem::ScreenHeight, 0, 0, 1280, 720 );
		iexSystem::GetDevice()->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );

		//	プレイヤーモデル描画
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			int active = gameParam->GetPlayerActive( i );

			if ( active )	obj[i]->Render();
		}

		switch ( step )
		{
		case MATCHING_MODE::NAME_INPUT:
			nameInput->Render();
			break;

		case MATCHING_MODE::SIGN_UP:
			break;

		case MATCHING_MODE::WAIT:
			itemSelect->Render();
			break;
		}

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
	LPSTR name = gameParam->GetPlayerName(id);

	//	表示
	char	str[256];
	//sprintf_s(str, "id : %d\n\nname : %s\n\npos : Vector3( %.2f, %.2f, %.2f )", id + 1, name, pos.x, pos.y, pos.z);
	IEX_DrawText(str, 20, 50, 500, 500, 0xFFFFFF00);
}







