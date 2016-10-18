
#include	"UDPServer.h"
#include	"GameParam.h"
#pragma comment( lib, "wsock32.lib" )

//********************************************************************
//
//	UDPServerクラス
//
//********************************************************************

//-------------------------------------------------------------------------------
//	初期化・解放
//-------------------------------------------------------------------------------

	//	コンストラクタ
	UDPServer::UDPServer( void ) : sock( INVALID_SOCKET )
	{
		//	全クライアントアドレス初期化
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			client_addr[i].sin_addr.S_un.S_addr = 0;
		}
	}

	//	デストラクタ
	UDPServer::~UDPServer( void )
	{
		if ( sock != INVALID_SOCKET )	closesocket( sock );
	}

	//	初期化
	bool	UDPServer::Initialize( WORD port )
	{
		struct	sockaddr_in	server;

		//	サーバー情報設定
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons( port );

		//	UDPソケット作成
		sock = socket( AF_INET, SOCK_DGRAM, 0 );

		//	サーバー準備
		bind( sock, ( struct sockaddr* )&server, sizeof( server ) );

		//	ソケットリストに登録
		FD_ZERO( &fds );
		FD_SET( sock, &fds );

		//	※TCPとの違いはソケットの種類とlistenが無いだけ
		return	true;
	}

//-------------------------------------------------------------------------------
//	送受信
//-------------------------------------------------------------------------------
	
	//	送信
	void	UDPServer::Send( int client, const LPSTR data, int size )
	{
		sendto( sock, data, size, 0, ( struct sockaddr* )&client_addr[client], sizeof( client_addr[client] ) );
	}

	//	受信
	int		UDPServer::Receive( const LPSTR data, int* size )
	{
		//	タイムアウト設定
		struct	timeval	tv = { 0, 1000 };

		//	ソケットリスト初期化
		fd_set	fd_work;
		memcpy( &fd_work, &fds, sizeof( fd_set ) );

		//	受信状態ソケットの検索
		int n = select( 0, &fd_work, NULL, NULL, &tv );

		//	タイムアウトの場合にselectは0をかえす
		if ( n <= 0 )	return	-1;

		//	データ受信用変数準備
		int		recvsize;
		int		addr_len;
		struct	sockaddr_in	addr;

		//	データ受信
		addr_len = sizeof( struct sockaddr_in );
		recvsize = recvfrom( sock, data, *size, 0, ( struct sockaddr* )&addr, &addr_len );
		*size = recvsize;
		if ( recvsize <= 0 )	return	-1;	//	エラー

		int	command = ( int )data[COMMAND];

		if ( command == COMMANDS::SIGN_UP )
		{
			//	新規受入れ
			for ( int i = 0; i<PLAYER_MAX; i++ )
			{
				if ( client_addr[i].sin_addr.S_un.S_addr != 0 ) continue;
				client_addr[i] = addr;
				return i;
			}
		}

		//	クライアント検索
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			if ( client_addr[i].sin_addr.S_un.S_addr == 0 ) continue;

			if ( addr.sin_addr.S_un.S_addr == client_addr[i].sin_addr.S_un.S_addr )
			{
				int id = atoi( &data[ID] );
				if ( i == id )	return	i;
				else continue;
			}
		}
	
		return	-1;
	}

//-------------------------------------------------------------------------------
//	クライアント終了
//-------------------------------------------------------------------------------

	//	クライアント終了
	void	UDPServer::CloseClient( int client )
	{
		client_addr[client].sin_addr.S_un.S_addr = 0;
	}