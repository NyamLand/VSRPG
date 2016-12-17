
#include	"iextreme.h"
#include	<thread>
#include	<map>
#include	"GameManager.h"
#include	"PlayerManager.h"
#include	"InputManager.h"
#include	"LevelManager.h"
#include	"PointManager.h"
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
#define	TIME_MAX	( 1.0f * MINUTE )
GameParam*	gameParam = nullptr;

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	GameParam::GameParam( void )
	{
		InitializeGame();
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
		lifeInfo[id].Initialize( INIT_LIFE );
		playerParam[id] = gameManager->GetInitInfo( id );
	}

	//	ゲーム初期化
	void	GameParam::InitializeGame( void )
	{
		for ( int id = 0; id < PLAYER_MAX; id++ )
		{
			ZeroMemory( &playerInfo[id], sizeof( PlayerInfo ) );
			ZeroMemory( &playerParam[id], sizeof( PlayerParam ) );
			ZeroMemory( &lifeInfo[id], sizeof( LifeInfo ) );
			lifeInfo[id].Initialize( INIT_LIFE );
		}
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

		case RECEIVE_COMMAND::HUNT_INFO:
			client = ReceiveHuntInfo( client, data );
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
		SendCharaData sendCharaData( player, 
			attackInfo[player].attackParam,
			playerParam[player].pos, 
			playerParam[player].angle,
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
		Matching	matching( player, gameManager->GetMatchingInfo( player ).isComplete );

		//	送信
		send( client, ( char* )&matching, sizeof( matching ) );
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
		attackInfo[client].power = 1;
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
	int	GameParam::ReceiveHuntInfo( int client, const LPSTR& data )
	{
		ReceiveHuntData*	receiveHuntData = ( ReceiveHuntData* )data;

		//	大型の時点数を加算
		if ( receiveHuntData->enemyType == ENEMY_EXP::BIG_ENEMY )
		{
			pointManager->CalcPoint( client, 1000 );
			pointManager->SendPoint( client );
		}

		//	経験値計算
		levelManager->CalcExp( client, receiveHuntData->enemyType );
		levelManager->SendExp( client );
		return	-1;
	}

	//	レベル情報取得
	int	GameParam::ReceiveLevelInfo( int client, const LPSTR& data )
	{
		ReceiveLevelData*	receiveLevelData = ( ReceiveLevelData* )data;
		levelManager->AddLevel( client, receiveLevelData->levelType );
		levelManager->SendLevel( client, receiveLevelData->levelType );

		return	-1;
	}

//----------------------------------------------------------------------------------------------
//	ログイン関連受信処理
//----------------------------------------------------------------------------------------------

	//	サインアップ情報受信
	int	GameParam::ReceiveSignUp( int client, const LPSTR& data )
	{
		if ( gameManager->GetGameState() )	return	-1;

		//	名前保存
		SignUp* signUp = ( SignUp* )data;
		strcpy( playerInfo[client].name, signUp->name );

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
		gameManager->GetMatchingInfo( client ).isComplete = matching->isComplete;

		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	アクティブでないプレイヤーはとばす
			if ( playerInfo[p].active == false ) continue;
			SendMatchingInfo( client, p );
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
		PlayerParam	initParam = gameManager->GetInitInfo( client );
		SendCharaData	sendCharaData( client,
			AttackInfo::NO_ATTACK,
			initParam.pos, initParam.angle, initParam.motion,
			lifeInfo[client].life );
		send( client, ( LPSTR )&sendCharaData, sizeof( sendCharaData ) );

		//	サインアップ情報を設定
		SignUp		signUp( client, playerInfo[client].name );

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
			strcpy( signUp.name, playerInfo[p].name );
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
			gameManager->GetTimer()->Start( TIME_MAX );
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
	void	GameParam::SetPlayerParam( int id, const Vector3& pos, float angle, int motion )
	{
		playerParam[id].pos    = pos;
		playerParam[id].angle  = angle;
		playerParam[id].motion = motion;
	}
