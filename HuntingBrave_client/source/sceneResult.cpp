
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
#include	"PlayerManager.h"
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
#define	PLAYER_NUM_DIST	120
#define	PLAYER_NUM_SIZE	70
#define	SCORE_DIST		100
#define	SCORE_SIZE		100

const LPSTR fileName[] =
{
	"DATA/CHR/suppin/Suppin.IEM",
	"DATA/CHR/Fighter/Fighter.IEM",
	"DATA/CHR/Magician/Magician.IEM",
	"DATA/CHR/Knight/Knight.IEM",
	"DATA/CHR/Prist/prist.IEM",
	"DATA/CHR/Assasin/assasin.IEM"
};

const LPSTR bodyTexFileName[] =
{
	"DATA/CHR/suppin/body_",
	"DATA/CHR/Fighter/body_",
	"DATA/CHR/Magician/body_",
	"DATA/CHR/Knight/body_",
	"DATA/CHR/Prist/body_",
	"DATA/CHR/Assasin/body_"
};

float	scale[] =
{
	0.2f,
	0.2f,
	0.2f,
	0.08f,
	0.2f,
	0.08f
};

float	angle[] = 
{
	PI * 0.95f,
	PI * 0.95f,
	0.0f,
	-PI * 0.3f
};

int	motion[] =
{
	18,
	18,
	20,
	20
};

Vector3	pos[] =
{
	Vector3(0.0f, 0.0f, 220.0f),
	Vector3(6.0f, 0.0f, 225.0f),
	Vector3(-5.0f, 0.0f, 230.0f),
	Vector3(-10.0f, 0.0f, 235.0f),
};

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
			Vector3( 6.0f, 10.0f, 205.0f ),
			Vector3( 6.0f, 3.0f, 220.0f ) );

		//	画像読み込み
		back = new iex2DObj( "DATA/UI/BackGround/result_UI.png" );

		testResult = new TestResult();

		//	BGM再生
		sound->PlayBGM( BGM::RESULT );

		pointManager->Sort();

		index = 0;
		viewPos = Vector3( 0.0f, 20.0f, 200.0f );

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			obj[i] = nullptr;
			rankUI[i] = nullptr;
			scoreUI[i] = nullptr;
			playerNumUI[i] = nullptr;
			if ( gameParam->GetPlayerActive( i ) == false )	continue;

			//	クラス取得
			char classType = playerManager->GetPlayer( i )->GetCurClass();

			//	モデル初期化
			obj[i] = new iex3DObj( fileName[classType] );
			obj[i]->SetScale( scale[classType] );
			playerManager->GetPlayer( i )->ChangeTexture( obj[i], classType, i );

			//	ランク初期化
			rankUI[i] = new RankUI( RESULT_POS_X, RESULT_POS_Y + ( RESULT_DIST_HEIGHT * i ), RANK_SIZE_X, RANK_SIZE_Y );
			playerNumUI[i] = new PlayerNumUI( pointManager->GetPlayer(i), RESULT_POS_X + PLAYER_NUM_DIST, RESULT_POS_Y + (RESULT_DIST_HEIGHT * i ), PLAYER_NUM_SIZE, PLAYER_NUM_SIZE );
			scoreUI[i] = new ScoreUI( RESULT_POS_X + PLAYER_NUM_DIST + SCORE_DIST, RESULT_POS_Y + ( RESULT_DIST_HEIGHT * i ), SCORE_SIZE, RANK_SIZE_Y ) ;
		}

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			int num = pointManager->GetPlayer(i);
			if ( gameParam->GetPlayerActive( num ) == false )	continue;
			obj[num]->SetAngle(angle[i]);
			obj[num]->SetMotion(motion[i]);
			obj[num]->SetPos(pos[i]);
			obj[num]->Update();
		}
		//	サインアウト
		gameParam->CloseClient();

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
			SafeDelete( playerNumUI[i] );
		}
		playerManager->Release();
		sound->StopBGM();
	}

//----------------------------------------------------------------------------------------------
//	更新・描画
//----------------------------------------------------------------------------------------------

	//	更新
	void	sceneResult::Update( void )
	{
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			if ( obj[i] == nullptr )	continue;
			obj[i]->Animation();
			obj[i]->Update();
			if( rankUI[i] != nullptr )rankUI[i]->Update( pointManager->GetPlayer( i ) );
			if( scoreUI[i] != nullptr )scoreUI[i]->SetScore( pointManager->GetPoint( i ) );
			if( scoreUI[i] != nullptr )scoreUI[i]->Update();
		}

		if ( KEY( KEY_TYPE::START ) == 3 || KEY( KEY_TYPE::A ) == 3 )
		{
			MainFrame->ChangeScene( new sceneTitle() );
			return;
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
			if ( obj[i] != nullptr )	obj[i]->Render();

			if( rankUI[i] != nullptr )rankUI[i]->Render();
			if( playerNumUI[i] != nullptr )playerNumUI[i]->Render();
			if( scoreUI[i] != nullptr )scoreUI[i]->Render();
		}
	}
