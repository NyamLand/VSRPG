
#include	"iextreme.h"
#include	"GameManager.h"
#include	"PlayerManager.h"
#include	"InputManager.h"
#include	<thread>
#include	"GameParam.h"

//*****************************************************************************************************************************
//
//		ゲームデータ管理
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	GameParam::GameParam( void )
	{
		for( int id = 0 ; id < PLAYER_MAX ; id++ )
		{
			ZeroMemory( &playerInfo[id], sizeof( PlayerInfo ) );
			ZeroMemory( &playerParam[id], sizeof( PlayerParam ) );
			ZeroMemory( &pointInfo[id], sizeof( PointInfo ) );
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
			//	
			if( playerInfo[clientNum].active == false ) continue;

			//	アクティブでないプレイヤーはとばす
			if ( playerInfo[clientNum].active == false ) continue;

			//	移動情報送信
			SendCharaInfo( client, clientNum );

			//	点数情報送信
			SendPointInfo( client, clientNum );	
		}
		
		//	ゲーム情報送信
		SendGameInfo( client );

		//	終端通知
		char end = -1;
		send( client, &end, 1 );
		return client;
	}

	//	受信
	int	GameParam::Receive( void )
	{
		char	data[256];
		int		size = sizeof( data );
		int		client = receive( data, &size );
		if( client == -1 ) return -1;
		
		switch( data[COMMAND] )
		{
		case RECEIVE_COMMAND::PLAYER_INFO:		//	パラメータ情報
			client = ReceiveChara( client, data );
			break;

		case RECEIVE_COMMAND::POINT_INFO:		//	点数情報
			client = ReceivePoint( client, data );
			break;

		case RECEIVE_COMMAND::ATTACK_INFO:		//	攻撃情報
			client = ReceiveAttackParam( client , data );
			break;

		case COMMANDS::SIGN_UP:	//	新規参入
			client = ReceiveSignUp( client, data );
			break;

		case COMMANDS::SIGN_OUT:	//	脱退
			client = ReceiveSignOut( client, data );
			break;
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
			playerParam[player].pos, 
			playerParam[player].angle,
			playerParam[player].motion,
			playerParam[player].life );

		//	送信
		send( client, ( LPSTR )&sendCharaData, sizeof( sendCharaData ) );
	}

	//	ゲーム情報送信
	void	GameParam::SendGameInfo( int client )
	{
		//	情報設定
		SendGameData	 sendGameData( gameManager->GetTimer()->GetLimitTime() ); 

		//	送信
		send( client, ( LPSTR )&sendGameData, sizeof( sendGameData ) );
	}

	//	点数情報送信
	void	GameParam::SendPointInfo( int client, int player )
	{
		//	情報設定
		SendPointData	sendPointData( player, pointInfo[player].point );
		
		//	送信
		send( client, ( char* )&sendPointData, sizeof( sendPointData ) );
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

		//	ボタンの入力情報設定
		inputManager->SetInput( client, receivePlayerData->button, receivePlayerData->inputType );
		
		//	フレーム情報設定
		playerParam[client].frame = receivePlayerData->frame;

		return	client;
	}

	//	点数情報受信
	int	GameParam::ReceivePoint( int client, const LPSTR& data )
	{
		ReceivePointData*	receivePointData = ( ReceivePointData* )data;
		pointInfo[client].point += receivePointData->addPoint;
		
		//	全プレイヤーに送信
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			SendPointInfo( client, p );
		}

		return	-1;
	}

	//	攻撃情報受信
	int	GameParam::ReceiveAttackParam( int client, const LPSTR& data )
	{
		ReceiveAttackData*	receiveAttackData = ( ReceiveAttackData* )data;
		
		attackInfo[client].attackParam = ( AttackInfo::ATTACK_PARAM )receiveAttackData->attackParam;
		attackInfo[client].collisionShape.SetCapsule( 
			Capsule( 	receiveAttackData->attackPos1, 
							receiveAttackData->attackPos2,
							receiveAttackData->radius ) );
		attackInfo[client].collisionShape.shapeType = SHAPE_TYPE::CAPSULE;
		attackInfo[client].power = 1;
		return	-1;
	}

	//	サインアップ情報受信
	int	GameParam::ReceiveSignUp( int client, const LPSTR& data )
	{
		//	名前保存
		SignUp* signUp = ( SignUp* )data;
		SetPlayer( client, signUp->name );

		//	IDを返信
		signUp->id = client;
		send( client, ( char* )signUp, sizeof( SignUp ) );

		//	初期座標を送信
		PlayerParam	initParam = gameManager->GetInitInfo( client );
		SendCharaData	sendCharaData( client, 
			initParam.pos, initParam.angle, initParam.motion, 
			initParam.life );
		send( client, ( LPSTR )&sendCharaData, sizeof( sendCharaData ) );

		//	全員にデータ送信
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( playerInfo[p].active == false ) continue;
			send( p, ( char* )signUp, sizeof( SignUp ) );
		}

		//	全データ送信
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( playerInfo[p].active == false ) continue;
			signUp->id = p;
			strcpy( signUp->name, playerInfo[p].name );
			send( client, ( char* )signUp, sizeof( SignUp ) );
		}
		printf( "%dP %sさんが参加しました。\n", client + 1, signUp->name );

		return	client;
	}

	//	サインアウト情報受信
	int	GameParam::ReceiveSignOut( int client, const LPSTR& data )
	{
		//	プレイヤー解放
		ReleasePlayer( client );

		SignOut	signOut( client );

		//	ソケットを閉じる
		CloseClient( client );

		//	全員にデータ送信
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( playerInfo[p].active == false ) continue;
			send( p, ( char* )&signOut, sizeof( SignOut ) );
		}
		printf( "%dP %sさんが脱退しました。\n", client + 1, playerInfo[client].name );

		return	client;
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
		playerManager->SetPlayer( id );
	}

	//	プレイヤー解放
	void	GameParam::ReleasePlayer( int id )
	{
		ZeroMemory( &playerInfo[id], sizeof( PlayerInfo ) );
		//playerManager->ReleasePlayer( id );
	}

	//	プレイヤーパラメータ設定
	void	GameParam::SetPlayerParam( int id, const Vector3& pos, float angle, int motion )
	{
		playerParam[id].pos    = pos;
		playerParam[id].angle  = angle;
		playerParam[id].motion = motion;
	}

	//	プレイヤーパラメータ設定
	void	GameParam::SetPlayerParam( int id, const PlayerParam& param )
	{
		playerParam[id].pos    = param.pos;
		playerParam[id].angle  = param.angle;
	}

	//	点数情報設定
	void	GameParam::SetPointInfo( int id, const PointInfo& pointInfo )
	{
		this->pointInfo[id] = pointInfo;
	}

