
#include	"iextreme.h"
#include	<vector>
#include	<memory>
#include	"FrameWork.h"
#include	"GameParam.h"
#include	"sceneMain.h"
#include	"sceneMatching.h"
#include	"CSVReader.h"
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
#define	CENTER_DIST		340.0f

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
		initPlayerParam[0].Set( Vector3( 0.0f, 0.0f, CENTER_DIST ), D3DX_PI, 0.0f, 1.0f, initMotion, 0 );
		initPlayerParam[1].Set( Vector3( CENTER_DIST, 0.0f, 0.0f ), D3DX_PI * 1.5f, 0.0f, 1.0f, initMotion, 0 );
		initPlayerParam[2].Set( Vector3( 0.0f, 0.0f, -CENTER_DIST ), 0.0f, 0.0f, 1.0f, initMotion, 0);
		initPlayerParam[3].Set( Vector3( -CENTER_DIST, 0.0f, 0.0f ), D3DX_PI * 0.5f, 0.0f, 1.0f, initMotion, 0 );

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			matchingInfo[i].isComplete = false;
		}
		playerData.clear();

		//	csv読み込み
		LoadData();
	}

	//	デストラクタ
	GameManager::~GameManager( void )
	{
		if ( timer != nullptr )
		{
			delete timer;
			timer = nullptr;
		}

		playerData.clear();
	}

	//	マッチング情報初期化
	void	GameManager::MatchingInfoInitialize( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			matchingInfo[p].isComplete = false;
		}
	}

	//	CSV読み込み
	void	GameManager::LoadData( void )
	{
		//	CSVファイル
		fstream playerStream( "DATA/player_data.csv" );

		//	CSVリーダー初期化
		std::unique_ptr<CSVReader>	reader =
			std::make_unique<CSVReader>( playerStream );

		//	ファイルから読み込み、vector配列に保存する
		int index = 0;
		while ( 1 )
		{
			playerData.resize( index + 1 );
			reader->Read( playerData[index] );
			if ( playerData[index].size() == 0 )	break;
			index++;
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

	//	プレイヤーステータス初期化
	void	GameManager::InitializeStatus( PlayerStatus& playerStatus )
	{
		int power = GetInitStatus( UPGRADE_DATA::ATTACK );
		int defense = GetInitStatus( UPGRADE_DATA::DEFENSE );
		int magicAttack = GetInitStatus( UPGRADE_DATA::MAGIC_ATTACK );
		int magicDefense = GetInitStatus( UPGRADE_DATA::MAGIC_DIFENSE );
		int life = GetInitStatus( UPGRADE_DATA::HP );
		float speed = GetInitSpeed();

		playerStatus.Initialize( power, defense, magicAttack, magicDefense, life, speed );
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
			else
			{
				ret = matchingInfo[p].isComplete;
				if ( !ret ) 	break;
			}
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

	//	マッチング情報設定
	void	GameManager::SetMatchingInfo( int id, bool state )
	{
		matchingInfo[id].isComplete = state;
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

	//	アップグレードデータ取得
	int	GameManager::GetUpGrade( char levelType, char upGradeData, char level )
	{
		return	std::stoi( playerData[2 + ( levelType * 7 ) + level][upGradeData] );
	}

	//	アップグレード初期値取得
	int	GameManager::GetInitStatus( char upGradeData )
	{
		return	std::stoi( playerData[1][upGradeData] );
	}

	//	スピード初期値取得
	float	GameManager::GetInitSpeed( void )
	{
		return	std::stof( playerData[1][UPGRADE_DATA::SPEED] );
	}

	//	スピードアップグレードデータ取得
	float	GameManager::GetUpGradeSpeed( char levelType, char level )
	{
		return	std::stof( playerData[2 + ( levelType * 7 ) + level][UPGRADE_DATA::SPEED] );
	}


