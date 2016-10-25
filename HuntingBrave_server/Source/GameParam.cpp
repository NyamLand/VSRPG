
#include	"iextreme.h"
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
			playerInfo[id].active = false;

			playerParam[id].pos = Vector3( 0.0f, 0.0f, 0.0f );
			playerParam[id].angle = 0.0f;
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

			//	移動情報送信
			SendCharaInfo( p );
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
		NET_CHARA netChara( client, playerParam[client].pos );
		send( client, ( LPSTR )&netChara, sizeof( NET_CHARA ) );
	}

//----------------------------------------------------------------------------------------------
//	受信処理
//----------------------------------------------------------------------------------------------

	//	キャラ情報受信
	void	GameParam::ReceiveChara( int client, const LPSTR& data )
	{
		NET_CHARA* d = ( NET_CHARA* )data;
		playerParam[client].pos = d->pos;
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
		playerInfo[client].active = false;
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
		playerParam[id].pos = Vector3( 0.0f, 0.0f, 0.0f );
		playerParam[id].angle  = 0.0f;
	}

	//	プレイヤーパラメータ設定
	void	GameParam::SetPlayerParam( int id, Vector3& pos, float angle )
	{
		playerParam[id].pos    = pos;
		playerParam[id].angle  = angle;
	}

	//	プレイヤーパラメータ設定
	void	GameParam::SetPlayerParam( int id, PlayerParam& param )
	{
		playerParam[id].pos    = param.pos;
		playerParam[id].angle  = param.angle;
	}

