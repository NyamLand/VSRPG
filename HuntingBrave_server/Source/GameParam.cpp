
#include	"iextreme.h"
#include	<thread>
#include	<map>
#include	<vector>
#include	"GameManager.h"
#include	"PlayerManager.h"
#include	"InputManager.h"
#include	"LevelManager.h"
#include	"ItemManager.h"
#include	"PointManager.h"
#include	"EnemyManager.h"
#include	"Collision.h"
#include	"GameParam.h"

//*****************************************************************************************************************************
//
//		ゲームデータ管理
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

#define	INIT_LIFE		5
#define	TIME_MAX	1.0f//( 9.0f * MINUTE + 30.0f )
GameParam*	gameParam = nullptr;

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	GameParam::GameParam( void ) : playerName( nullptr )
	{
		playerName = new PlayerName();
		InitializeGame();
	}

	//	デストラクタ
	GameParam::~GameParam( void )
	{
		if ( playerName != nullptr )
		{
			delete	playerName;
			playerName = nullptr;
		}
	}

	//	サーバー初期化
	bool GameParam::InitializeServer( void )
	{
		//	WinSock初期化
		WSADATA	wsaData;
		WSAStartup( MAKEWORD( 1, 1 ), &wsaData );
		bool successInit = Initialize( 7000 );

		if ( successInit )	printf( "サーバー初期化成功\n" );
		return successInit;
	}

	//	プレイヤー初期化
	void	GameParam::InitializePlayer( int id )
	{
		lifeInfo[id].life = lifeInfo[id].maxLife;
		playerParam[id].pos = gameManager->GetInitInfo( id ).pos;
		//playerParam[id] = gameManager->GetInitInfo( id );
	}

	//	ゲーム初期化
	void	GameParam::InitializeGame( void )
	{
		for ( int id = 0; id < PLAYER_MAX; id++ )
		{
			ZeroMemory( &playerInfo[id], sizeof( PlayerInfo ) );
			ZeroMemory( &playerParam[id], sizeof( PlayerParam ) );
			ZeroMemory( &playerStatus[id], sizeof( PlayerStatus ) );
			ZeroMemory( &lifeInfo[id], sizeof( LifeInfo ) );
			int initLife = gameManager->GetInitStatus( UPGRADE_DATA::HP );
			lifeInfo[id].Initialize( initLife );
			gameManager->InitializeStatus( playerStatus[id] );
		}

		itemManager->Initialize();
	}

	//	ゲームリセット
	void	GameParam::ReleaseGame( void )
	{
		playerName->Initialize();
		itemManager->Release();
		playerManager->Release();
		gameManager->Release();
	}

//----------------------------------------------------------------------------------------------
//	データ送受信
//----------------------------------------------------------------------------------------------

	//	送信
	int	GameParam::Send( int client )
	{
		if( client == -1 ) return -1;

		//	全データ送信
		for ( int clientNum = 0; clientNum < PLAYER_MAX; clientNum++ )
		{
			//	アクティブでないプレイヤーはとばす
			if ( playerInfo[clientNum].active == false ) continue;

			//	移動情報送信
			SendCharaInfo( client, clientNum );
		}
		
		//	ゲーム情報送信
		SendGameInfo( client );

		//	終端通知
		char end = -1;
		send( client, &end, 1 );

		//	キー情報リセット
		inputManager->ResetInput( client );

		return client;
	}

	//	受信
	int	GameParam::Receive( char scene )
	{
		//	データ受信
		char	data[256];
		int	size = sizeof( data );
		int	client = receive( data, &size );
		if( client == -1 ) return -1;

		//	ネット関連
		switch ( data[COMMAND] )
		{
		case RECEIVE_COMMAND::PLAYER_INFO:
			client = ReceiveChara( client, data );
			break;

		case RECEIVE_COMMAND::ATTACK_INFO:
			client = ReceiveAttackInfo( client, data );
			break;

		case RECEIVE_COMMAND::INPUT_INFO:
			client = ReceiveInput( client, data );
			break;

		case RECEIVE_COMMAND::LEVEL_INFO:
			client = ReceiveLevelInfo( client, data );
			break;

		case RECEIVE_COMMAND::ENEMY_INFO:
			client = ReceiveEnemyInfo( client, data );
			break;

		case RECEIVE_COMMAND::ITEM_INFO:
			client = ReceiveItemInfo( client, data );
			break;

		case COMMANDS::MATCHING:
			client = ReceiveMatching( client, data );
			break;

		case COMMANDS::SIGN_UP:
			client = ReceiveSignUp( client, data );
			break;

		case COMMANDS::SIGN_OUT:	//	脱退
			client = ReceiveSignOut( client, data );
			break;

		case COMMANDS::RESPONSE:	//	サインアップ応答
			client = ReceiveResponse( client, data );
			break;

		case COMMANDS::DEBUG:
		{
				collision->SendHitSE( 0 );
				//	ライフ計算
				int damage = 50;
				if ( damage <= 0 )	damage = 5;
				bool isAlive = gameParam->GetLifeInfo( client ).CulcLife(-damage);
				if ( isAlive ) gameParam->GetPlayerParam( client ).effParam = 0.0f;
				else
				{
					//	プレイヤーを死亡させる
					playerManager->GetPlayer(0)->SetDeath();
				}
		}
			break;

		default:	//	ゲーム情報処理
			client = -1;
		}
		return client;
	}

//----------------------------------------------------------------------------------------------
//	送信処理
//----------------------------------------------------------------------------------------------

	//	キャラ情報送信
	void	GameParam::SendCharaInfo( int client, int player )
	{
		//	情報設定
		SendCharaData sendCharaData(player,
			attackInfo[player].attackParam,
			playerParam[player].pos,
			playerParam[player].angle,
			playerParam[player].effParam,
			playerParam[player].motion,
			lifeInfo[player].life );

		//	送信
		send( client, ( LPSTR )&sendCharaData, sizeof( sendCharaData ) );
	}

	//	ゲーム情報送信
	void	GameParam::SendGameInfo( int client )
	{
		//	情報設定
		SendGameData	 sendGameData( gameManager->GetTimer()->GetRemainingTime() ); 

		//	送信
		send( client, ( LPSTR )&sendGameData, sizeof( sendGameData ) );
	}

	//	マッチング情報送信
	void	GameParam::SendMatchingInfo( int client, int player )
	{
		//	情報設定
		Matching	matching( client, gameManager->GetMatchingInfo( client ).isComplete );

		//	送信
		send( player, ( char* )&matching, sizeof( matching ) );
	}

	//	キル情報送信
	void	GameParam::SendKillInfo( int killer, int dead )
	{
		struct
		{
			char com;
			char responseCom;
			int killer;
			int dead;
		} killInfo;
		killInfo.com = COMMANDS::RESPONSE;
		killInfo.responseCom = RESPONSE_COMMAND::KILL_INFO;
		killInfo.killer = killer;
		killInfo.dead = dead;

		//	送信
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			send( i, ( char* )&killInfo, sizeof( killInfo ) );
		}
	}

//----------------------------------------------------------------------------------------------
//	受信処理
//----------------------------------------------------------------------------------------------

	//	キャラ情報受信
	int	GameParam::ReceiveChara( int client, const LPSTR& data )
	{
		ReceivePlayerData* receivePlayerData = ( ReceivePlayerData* )data;
		
		//	スティックの入力情報設定
		inputManager->SetAxis( client, receivePlayerData->axisX,	receivePlayerData->axisY );

		//	カメラアングル取得
		playerParam[client].cameraAngle = receivePlayerData->cameraAngle;
		
		//	フレーム情報設定
		playerParam[client].frame = receivePlayerData->frame;

		return	client;
	}

	//	攻撃情報受信
	int	GameParam::ReceiveAttackInfo( int client, const LPSTR& data )
	{
		ReceiveAttackData*	receiveAttackData = ( ReceiveAttackData* )data;
		
		//	攻撃情報設定
		attackInfo[client].shapeType = receiveAttackData->shape;
		attackInfo[client].vec1 = receiveAttackData->vec1;
		attackInfo[client].vec2 = receiveAttackData->vec2;
		attackInfo[client].radius = receiveAttackData->radius;
		return	-1;
	}

	//	入力情報取得
	int	GameParam::ReceiveInput( int client, const LPSTR& data )
	{
		ReceiveInputData*	receiveInputData = ( ReceiveInputData* )data;

		//	ボタンの入力情報設定
		inputManager->SetInput( client, receiveInputData->key, receiveInputData->keyState );
		return	-1;
	}

	//	討伐情報取得
	int	GameParam::ReceiveEnemyInfo( int client, const LPSTR& data )
	{
		switch ( data[1] )
		{
		case RECEIVE_ENEMY_COMMAND::BIG_ENEMY_HUNT:
			//	点数計算
			pointManager->ReceiveHuntInfo( client, data );

			//	経験値計算
			levelManager->ReceiveHuntInfo( client, data );
			break;

		case RECEIVE_ENEMY_COMMAND::SMALL_ENEMY_HUNT:
			//	点数計算
			pointManager->ReceiveHuntInfo( client, data );

			//	経験値計算
			levelManager->ReceiveHuntInfo( client, data );
			break;

		case RECEIVE_ENEMY_COMMAND::PLAYER_HIT:
			{
				//	ライフ計算
				int damage = 5;
				bool isAlive = gameParam->GetLifeInfo( client ).CulcLife( -damage );
				if (isAlive) gameParam->GetPlayerParam( client ).effParam = 0.0f;
				else
				{
					//	プレイヤーを死亡させる
					playerManager->GetPlayer( client )->SetDeath();
				}
			}
			break;

		case RECEIVE_ENEMY_COMMAND::CLIENT_OK:
			enemyManager->Receive( client, data );
			break;

		default:
			break;
		}

		return	-1;
	}

	//	レベル情報取得
	int	GameParam::ReceiveLevelInfo( int client, const LPSTR& data )
	{
		ReceiveLevelData*	receiveLevelData = ( ReceiveLevelData* )data;
		levelManager->AddLevel( client, receiveLevelData->levelType );
		levelManager->SendLevel( client, receiveLevelData->levelType );
		levelManager->SendAllStatus( client );

		return	-1;
	}

	//	アイテム情報取得
	int	GameParam::ReceiveItemInfo( int client, const LPSTR& data )
	{
		itemManager->ReceiveData( client, data );
		return	-1;
	}

//----------------------------------------------------------------------------------------------
//	ログイン関連受信処理
//----------------------------------------------------------------------------------------------

	//	サインアップ情報受信
	int	GameParam::ReceiveSignUp( int client, const LPSTR& data )
	{
		if ( gameManager->GetGameState() )
		{
			return	-1;
		}

		//	名前保存
		SignUp* signUp = ( SignUp* )data;
		playerName->SetName( client, signUp->name );
		char*	name = playerName->GetName( client );
		strcpy( playerInfo[client].name, name );

		//	称号保存
		playerInfo[client].frontTitle = signUp->frontTitle;
		playerInfo[client].backTitle = signUp->backTitle;

		//	IDを返信
		signUp->id = client;
		send( client, ( char* )signUp, sizeof( SignUp ) );

		return	-1;
	}

	//	サインアウト情報受信
	int	GameParam::ReceiveSignOut( int client, const LPSTR& data )
	{
		//	プレイヤー解放
		ZeroMemory( &playerInfo[client], sizeof( PlayerInfo ) );
		
		//	ソケットを閉じる
		CloseClient( client );

		//	情報設定
		SignOut	signOut( client );

		//	全員にデータ送信
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( playerInfo[p].active == false ) continue;
			send( p, ( char* )&signOut, sizeof( SignOut ) );
		}
		printf( "%dP %sさんが脱退しました。\n", client + 1, playerInfo[client].name );

		return	client;
	}

	//	マッチング情報受信
	int	GameParam::ReceiveMatching( int client, const LPSTR& data )
	{
		Matching*	matching = ( Matching* )data;
		gameManager->SetMatchingInfo( client, matching->isComplete );

		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	アクティブでないプレイヤーはとばす
			if ( playerInfo[p].active == false ) continue;
			SendMatchingInfo( /*受信したプレイヤー情報*/client, /*送信したい他のプレイヤー*/p );
		}

		return	-1;
	}

	//	返答情報受診
	int	GameParam::ReceiveResponse( int client, const LPSTR& data )
	{
		Response*	response = ( Response* )data;

		switch ( response->responseCom )
		{
		case RESPONSE_COMMAND::SIGN_UP:
			client = SignUpResponse( client );
			break;

		case RESPONSE_COMMAND::GAME_START:
			client = GameStartResponse( client );
			break;
		}

		return	client;
	}

//----------------------------------------------------------------------------------------------
//	応答コマンド毎の処理
//----------------------------------------------------------------------------------------------

	//	サインアップ応答情報受信
	int	GameParam::SignUpResponse( int client )
	{
		//	返答が返ってきたのでアクティブにする
		SetPlayer( client, playerInfo[client].name );

		//	初期情報送信
		{
			//	初期情報取得
			PlayerParam		initParam = gameManager->GetInitInfo( client );

			//	初期情報設定
			SendCharaData	sendCharaData( client,
				AttackInfo::NO_ATTACK,
				initParam.pos, initParam.angle, initParam.effParam, initParam.motion,
				lifeInfo[client].life );

			//	初期情報送信
			send( client, ( LPSTR )&sendCharaData, sizeof( sendCharaData ) );
		}

		//	初期パラメータ送信
		levelManager->SendAllStatus( client );

		//	サインアップ情報を設定
		SignUp		signUp( client, 
			playerName->GetNameIndex( client ),
			playerInfo[client].frontTitle, 
			playerInfo[client].backTitle );

		//	全員にデータ送信
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( playerInfo[p].active == false ) continue;
			send( p, ( char* )&signUp, sizeof( signUp ) );
		}

		//	全データ送信
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( playerInfo[p].active == false ) continue;
			signUp.id = p;
			signUp.frontTitle = playerInfo[p].frontTitle;
			signUp.backTitle = playerInfo[p].backTitle;

			//	名前インデックスコピー
			for ( int i = 0; i < 4; i++ )
			{
				signUp.name[i] = playerName->GetNameIndex( p )[i];
			}
			send( client, ( char* )&signUp, sizeof( signUp ) );
		}
		printf( "%dP %sさんが参加しました。\n", client + 1, signUp.name );

		return	client;
	}

	//	ゲーム開始応答情報受信
	int	GameParam::GameStartResponse( int client )
	{
		gameManager->GetMatchingInfo( client ).isComplete = true;

		//	全員準備完了でスタート
		if ( gameManager->PlayerCheck() )
		{
			gameManager->MatchingInfoInitialize();
			gameManager->SetGameState( true );
			gameManager->GetTimer()->Start( TIME_MAX * 3 );
		}

		return	-1;
	}

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

	//	プレイヤー情報設定
	void	GameParam::SetPlayer( int id, char* name )
	{
		//	プレイヤー情報設定
		playerInfo[id].active = true;
		strcpy( playerInfo[id].name, name );

		//	パラメータ初期化
		playerParam[id] = gameManager->GetInitInfo( id );
	}

	//	プレイヤーパラメータ設定
	void	GameParam::SetPlayerParam( int id, const Vector3& pos, float angle, float effParam, int motion )
	{
		playerParam[id].pos    = pos;
		playerParam[id].angle  = angle;
		playerParam[id].motion = motion;
		playerParam[id].effParam = effParam;
	}
