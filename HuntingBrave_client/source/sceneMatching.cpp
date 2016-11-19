
#include	"iextreme.h"
#include	"system/Framework.h"
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
#include	"sceneMatching.h"

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

bool	sceneMatching::Initialize(void)
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

	//	モデル初期化
	for ( int i = 0; i < PLAYER_MAX; i++ )
	{
		obj[i] = make_unique<iex3DObj>( LPSTR( "DATA/CHR/suppin/Suppin.IEM" ) );
	}

	return true;
}

sceneMatching::~sceneMatching( void )
{
	SafeDelete( mainView );
}

//*****************************************************************************************************************************
//
//		更新
//
//*****************************************************************************************************************************
void	sceneMatching::Update( void )
{
	//	サーバーから情報受信
	gameParam->Update();

	//	GameManager更新
	gameManager->Update();

	//	モデル更新
	ObjUpdate();

	CheckComplete();

	if ( KEY_Get( KEY_ENTER ) == 3 )
	{
		gameManager->isComplete = true;
	}
}

void	sceneMatching::ObjUpdate()
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

void	sceneMatching::CheckComplete()
{
	bool check = true;
	for ( int i = 0; i < PLAYER_MAX; i++ )
	{
		if ( gameParam->GetPlayerActive( i ) )
		{
			if ( gameParam->GetMatchingInfo( i ).isComplete == false ) check = false;
		}
	}

	if ( check )
	{
		gameManager->isComplete = false;
		MainFrame->ChangeScene( new sceneMain() );
		return;
	}
}

//*****************************************************************************************************************************
//
//		描画関連
//
//*****************************************************************************************************************************
void	sceneMatching::Render(void)
{
	//	画面クリア
	mainView->Activate();
	mainView->Clear();

	for (int i = 0; i < PLAYER_MAX; i++)
	{
		int active = gameParam->GetPlayerActive(i);

		if (active)
		{
			obj[i]->Render();
		}
	}

	//	各プレイヤー座標表示
	DebugRender();

	//MyInfoRender();
}

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







