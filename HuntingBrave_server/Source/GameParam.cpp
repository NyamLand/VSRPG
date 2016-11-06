
#include	"iextreme.h"
#include	"GameManager.h"
#include	"PlayerManager.h"
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
	int		GameParam::Send( int client )
	{
		if( client == -1 ) return -1;
	
		//	全データ送信
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if( playerInfo[p].active == false ) continue;

			//	ゲーム情報送信
			SendGameInfo( p );

			//	移動情報送信
			SendCharaInfo( p );

			//	点数情報送信
			SendPointInfo( p );
		}

		//	終端通知
		char end = -1;
		send( client, &end, 1 );
		return client;
	}

	//	受信
	int		GameParam::Receive( void )
	{
		char	data[256];
		int		size = sizeof( data );
		int		client = receive( data, &size );
		if( client == -1 ) return -1;
		
		switch( data[COMMAND] )
		{
		case COMMANDS::CHARA_INFO:		//	移動情報
			ReceiveChara( client, data );
			break;

		case COMMANDS::CHARA_RECEIVEDATA:	//必要情報全部
			ReceiveCharaDATA( client, data );
			break;

		case COMMANDS::CONTROLLE_AXIS:	//コントローラー軸情報
			ReceiveControllerAxis( client, data );
			break;

		case COMMANDS::CHAR_MOVE:		//	移動情報
			ReceiveCharaMove( client, data );
			break;

		case COMMANDS::POINT_INFO:		//	点数情報
			ReceivePoint( client, data );
			break;

		case COMMANDS::SIGN_UP:	//	新規参入
			ReceiveSignUp( client, data );
			break;

		case COMMANDS::SIGN_OUT:	//	脱退
			ReceiveSignOut( client, data );
			break;
		}
		return client;
	}

//----------------------------------------------------------------------------------------------
//	送信処理
//----------------------------------------------------------------------------------------------

	//	キャラ情報送信
	void	GameParam::SendCharaInfo( int client )
	{
		//	情報設定
		NET_CHARA netChara( client, 
			playerParam[client].pos, 
			playerParam[client].angle,
			playerParam[client].motion );

		//	送信
		send( client, ( LPSTR )&netChara, sizeof( NET_CHARA ) );
	}

	//	ゲーム情報送信
	void	GameParam::SendGameInfo( int client )
	{
		//	情報設定
		NET_GAME	 netGame( gameManager->GetTimer()->GetLimitTime() ); 

		//	送信
		send( client, ( LPSTR )&netGame, sizeof( NET_GAME ) );
	}

	//	点数情報送信
	void	GameParam::SendPointInfo( int client )
	{
		//	加算分が０だとスキップ
		if ( pointInfo[client].addPoint == 0 )	return;

		//	情報設定
		NET_POINT	netPoint;
		netPoint.id = client;
		netPoint.point = pointInfo[client].point;
		pointInfo[client].addPoint = 0;

		//	送信
		send( client, ( LPSTR )&netPoint, sizeof( NET_POINT ) );
	}

//----------------------------------------------------------------------------------------------
//	受信処理
//----------------------------------------------------------------------------------------------

	//	キャラ情報受信
	void	GameParam::ReceiveChara( int client, const LPSTR& data )
	{
		NET_MOVE* netMove = ( NET_MOVE* )data;
		playerParam[client].moveX = netMove->axisX;
		playerParam[client].moveZ = netMove->axisY;
	}

	//	点数情報受信
	void	GameParam::ReceivePoint( int client, const LPSTR& data )
	{
		NET_POINT*	netPoint = ( NET_POINT* )data;
		pointInfo[client].addPoint = netPoint->point;
	}



	//*****************************************
	//		後でちゃんとする

	//受け取り情報全部
	void	GameParam::ReceiveCharaDATA( int client, const LPSTR& data )
	{
		NET_CHAR_RECEIVEDATA* d = (NET_CHAR_RECEIVEDATA*)data;
		//playerParam[client].axis = d->axis;
		float	length = sqrtf(d->axisX * d->axisX + d->axisY * d->axisY) * 0.001f;

		////	入力があれば移動処理
		if (length >= 0.3f)
		{
			Vector3 m = Vector3(sinf(d->angle), 0.0f, cosf(d->angle)) * 0.3f;

			playerParam[client].pos += m;
		}
	}


	//*****************************************

	//	コントローラー情報受信
	void	GameParam::ReceiveControllerAxis(int client, const LPSTR& data)
	{
		NET_CONTROLLE_AXIS* d = (NET_CONTROLLE_AXIS*)data;
		//playerParam[client].axis = d->axis;
		float	length = sqrtf( d->axisX * d->axisX + d->axisY * d->axisY ) * 0.001f;

		//	入力があれば移動処理
		if ( length >= 0.3f )	
		{
			Vector3 m = Vector3(sinf(0), 0.0f, cosf(0)) * 0.3f;
			playerParam[client].pos += m;
		}
	}



	//	キャラ移動量情報受信
	void	GameParam::ReceiveCharaMove(int client, const LPSTR& data)
	{
		NET_MOVE* netMove = ( NET_MOVE* )data;
		playerParam[client].moveX = netMove->axisX;
		playerParam[client].moveZ = netMove->axisY;
	}

	//	サインアップ情報受信
	void	GameParam::ReceiveSignUp( int client, const LPSTR& data )
	{
		//	名前保存
		NET_IN* netIn = ( NET_IN* )data;
		SetPlayer( client, netIn->name );

		//	IDを返信
		netIn->id = client;
		send( client, ( char* )netIn, sizeof( NET_IN ) );

		//	初期座標を送信
		PlayerParam	initParam = gameManager->GetInitInfo( client );
		NET_CHARA	netChara( client, initParam.pos, initParam.angle, initParam.motion );
		send( client, ( LPSTR )&netChara, sizeof( netChara ) );

		//	全員にデータ送信
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( playerInfo[p].active == false ) continue;
			send( p, ( char* )netIn, sizeof( NET_IN ) );
		}

		//	全データ送信
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( playerInfo[p].active == false ) continue;
			netIn->id = p;
			strcpy( netIn->name, playerInfo[p].name );
			send( client, ( char* )netIn, sizeof( NET_IN ) );
		}
		printf("%dP %sさんが参加しました。\n", client + 1, netIn->name);
	}

	//	サインアウト情報受信
	void	GameParam::ReceiveSignOut( int client, const LPSTR& data )
	{
		//	プレイヤー解放
		ReleasePlayer( client );

		//	ソケットを閉じる
		CloseClient( client );

		NET_OUT	netOut( client );

		//	全員にデータ送信
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( playerInfo[p].active == false ) continue;
			send( p, ( char* )&netOut, sizeof( NET_OUT ) );
		}
		printf( "%dP %sさんが脱退しました。\n", client + 1, playerInfo[client].name );
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

