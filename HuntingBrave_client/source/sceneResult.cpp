
#include	"iextreme.h"
#include	"system/Scene.h"
#include	"system/Framework.h"
#include	"GlobalFunction.h"
#include	"Interpolation.h"
#include	"GameData.h"
#include	"GameManager.h"
#include	"GameParam.h"
#include	"Camera.h"
#include	"InputManager.h"
#include	"sceneMatching.h"
#include	"PointManager.h"
#include	"Sound.h"
#include	"sceneTitle.h"
#include	"sceneResult.h"

//***************************************************************
//
//	sceneResultクラス
//
//***************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

#define	RESULT_POS_X	800
#define	RESULT_POS_Y	200
#define	RESULT_DIST_HEIGHT	100
#define	RANK_SIZE_X		100
#define	RANK_SIZE_Y		80
#define	PLAYER_NUM_DIST	100
#define	SCORE_DIST		100
#define	SCORE_SIZE		100


//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	初期化
	bool	sceneResult::Initialize( void )
	{
		//	環境設定
		iexLight::SetAmbient( 0x404040 );
		iexLight::SetFog( 800, 1000, 0 );

		//	平行光設定
		Vector3 dir( 1.0f, -1.0f, -0.5f );
		dir.Normalize();
		iexLight::DirLight( shader, 0, &dir, 0.8f, 0.8f, 0.8f );
		
		//	カメラ初期化
		mainView = new Camera();
		mainView->Initialize( Camera::VIEW_MODE::FIX_VIEW,
			Vector3( 0.0f, 50.0f, 200.0f ),
			Vector3( 0.0f, 3.0f, 300.0f ) );

		//	画像読み込み
		back = new iex2DObj( "DATA/UI/BackGround/result_UI.png" );

		testResult = new TestResult();

		//	サインアウト
		gameParam->CloseClient();

		//	BGM再生
		sound->PlayBGM( BGM::RESULT );

		pointManager->Sort();

		index = 0;
		viewPos = Vector3( 0.0f, 50.0f, 200.0f );

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			playerPos[i] = Vector3( 0.0f, 0.0f, 250.0f );
			obj[i] = new iex3DObj( "DATA/CHR/Suppin/suppin.IEM" );
			obj[i]->SetScale( 0.2f );
			obj[i]->SetPos( 0.0f, 0.0f, 250.0f );
			obj[i]->Update();

			rankUI[i] = new RankUI( RESULT_POS_X, RESULT_POS_Y + ( RESULT_DIST_HEIGHT * i ), RANK_SIZE_X, RANK_SIZE_Y );
			scoreUI[i] = new ScoreUI( RESULT_POS_X + SCORE_DIST, RESULT_POS_Y + ( RESULT_DIST_HEIGHT * i ), SCORE_SIZE, RANK_SIZE_Y ) ;
		}

		return	true;
	}

	//	解放
	sceneResult::~sceneResult( void )
	{
		SafeDelete( mainView );
		SafeDelete( back );
		SafeDelete( gameParam );
		SafeDelete( testResult );

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			SafeDelete( rankUI[i] );
			SafeDelete( scoreUI[i] );
		}
		sound->StopBGM();
	}

//----------------------------------------------------------------------------------------------
//	更新・描画
//----------------------------------------------------------------------------------------------

	//	更新
	void	sceneResult::Update( void )
	{
		//if ( KEY( KEY_RIGHT ) == 1 )	viewPos.x += 10.0f;
		//if ( KEY( KEY_LEFT ) == 1 )		viewPos.x -= 10.0f;
		if ( KEY( KEY_UP ) == 1 )		viewPos.z += 10.0f;
		if ( KEY( KEY_DOWN ) == 1 )	viewPos.z -= 10.0f;

		if ( KEY( KEY_AXISX ) < 0 )		playerPos[index].x -= 1.0f;
		if ( KEY( KEY_AXISX ) > 0 )		playerPos[index].x += 1.0f;
		if ( KEY( KEY_AXISY ) < 0 )		playerPos[index].z += 1.0f;
		if ( KEY( KEY_AXISY ) > 0 )		playerPos[index].z -= 1.0f;

		obj[index]->SetPos( playerPos[index] );
		obj[index]->Update();
		
		mainView->Set( viewPos, Vector3( 0.0f, 3.0f, 300.0f ) );

		if ( KEY( KEY_ENTER ) == 3 )
		{
			index++;
			if ( index >= PLAYER_MAX )	index = 0;	
		}

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			rankUI[i]->Update( pointManager->GetPlayer( i ) );
		}
	}

	//	描画
	void	sceneResult::Render( void )
	{
		mainView->Activate();
		mainView->Clear();

		//	リザルト描画
		testResult->Render();

		char str[256];

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			int player = pointManager->GetPlayer( i );
			sprintf(str, "%d位	    %dP	   score : %d", i + 1, player + 1, pointManager->GetPoint( player ) );
			IEX_DrawText( str, 600, 300 + i * 50, 200, 200, 0xFFFFFFFF );

			obj[i]->Render();

			rankUI[i]->Render();
			scoreUI[i]->Render();
		}

		//	座標表示
		sprintf( str, "pos.x = %2f\npos.y = %2f\npos.z = %2f", playerPos[index].x, playerPos[index].y, playerPos[index].z );
		IEX_DrawText( str, 20, 600, 200, 200, 0xFFFFFF00 );

		sprintf( str, "viewPos.x = %2f\nviewPos.y = %2f\nviewPos.z = %2f", viewPos.x, viewPos.y, viewPos.z );
		IEX_DrawText( str, 20, 200, 200, 200, 0xFFFFFF00 );
	}
