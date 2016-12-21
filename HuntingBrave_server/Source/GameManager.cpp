
#include	"iextreme.h"
#include	<vector>
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

#define	TIME_MAX	( 5 )
#define	INIT_LIFE		5

//	実体
GameManager*	gameManager = nullptr;

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	GameManager::GameManager( void ) : timer( nullptr ),
		timeUp( false ), gameState( false )
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

	//	初期化
	bool	GameManager::Initialize( void )
	{
		//	解放
		Release();

		//	マッチング情報初期化
		MatchingInfoInitialize();
		if ( timer == nullptr )	
			timer = new Timer();

		return	true;
	}

	//	解放
	void	GameManager::Release( void )
	{
		if ( timer != nullptr )
		{
			delete	timer;
			timer = nullptr;
		}

		gameState = false;
		timeUp = false;
	}

//----------------------------------------------------------------------------------------------
//	更新
//----------------------------------------------------------------------------------------------

	//	更新
	void	GameManager::Update( void )
	{
		//	タイマー更新
		if ( gameState )
		{
			if ( timer != nullptr )		timeUp = timer->Update();
		}
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

	//	ゲーム状態設定
	void	GameManager::SetGameState( bool state )
	{
		gameState = state;
	}

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


