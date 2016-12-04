
#include	"iextreme.h"
#include	"FrameWork.h"
#include	"GameParam.h"
#include	"sceneMain.h"
#include	"sceneMatching.h"
#include	"GameManager.h"

//*****************************************************************************************************************************
//
//		ゲームデータ管理
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

#define	TIME_MAX	( 1.0f * MINUTE )
#define	INIT_LIFE		7

//	実体
GameManager*	gameManager = nullptr;

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	GameManager::GameManager( void ) : timer( nullptr ),
		timeUp( false ), gameState( true )
	{
		//	初期座標設定
		int initMotion = 0;
		initPlayerParam[0].Set( Vector3( 0.0f, 0.0f, 15.0f ), D3DX_PI, initMotion, 0 );
		initPlayerParam[1].Set( Vector3( 15.0f, 0.0f, 0.0f ), D3DX_PI * 1.5f, initMotion, 0 );
		initPlayerParam[2].Set( Vector3( 0.0f, 0.0f, -15.0f ), 0.0f, initMotion, 0 );
		initPlayerParam[3].Set( Vector3( -15.0f, 0.0f, 0.0f ), D3DX_PI * 0.5f, initMotion, 0 );

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			matchingInfo[i].isComplete = false;
		}

		//	タイマー初期化
		timer = new Timer();
		timer->Start( TIME_MAX );
	}

	//	デストラクタ
	GameManager::~GameManager( void )
	{
		if ( timer != nullptr )
		{
			delete timer;
			timer = nullptr;
		}
	}

	//	マッチング情報初期化
	void	GameManager::MatchingInfoInitialize( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			matchingInfo[p].isComplete = false;
		}
	}

//----------------------------------------------------------------------------------------------
//	更新
//----------------------------------------------------------------------------------------------

	//	更新
	void	GameManager::Update( void )
	{
		//	タイマー更新
		if ( gameState )
			timeUp = timer->Update();
	}

//----------------------------------------------------------------------------------------------
//	動作関数
//----------------------------------------------------------------------------------------------

	//	プレイヤーチェック
	bool	GameManager::PlayerCheck( void )
	{
		bool	ret = false;
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( !gameParam->GetPlayerActive( p ) )	continue;
			ret = matchingInfo[p].isComplete;
		}

		return	ret;
	}

	//	シーン切り替え
	void	GameManager::ChangeScene( char& out, char nextScene )
	{
		//	シーン設定
		out = nextScene;
		Response	response( RESPONSE_COMMAND::CHANGE_SCENE );
		
		//	送信
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			gameParam->send( p, ( LPSTR )&response, sizeof( response ) );
		}
	}

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------------------

	//	初期座標取得
	PlayerParam	GameManager::GetInitInfo( int id )const
	{
		return	initPlayerParam[id];
	}

	//	タイマー取得
	Timer*&	GameManager::GetTimer( void )
	{
		return	timer;
	}

	//	マッチング情報取得
	MatchingInfo&	GameManager::GetMatchingInfo( int id )
	{
		return	matchingInfo[id];
	}

	//	タイムアップ取得
	bool	GameManager::GetTimeUp( void )
	{
		return	timeUp;
	}

	//	ゲーム状態取得
	bool	GameManager::GetGameState( void )
	{
		return	gameState;

	}


