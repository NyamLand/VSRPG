
#include"SocketClient.h"
#pragma comment( lib, "ws2_32.lib" )
#pragma comment( lib, "winmm.lib" )

//********************************************************************
//
//	SocketClientクラス
//
//********************************************************************

#define	TIME_OUT	1000

//-------------------------------------------------------------------------------
//	初期化・解放
//-------------------------------------------------------------------------------

	//	コンストラクタ
	SocketClient::SocketClient( void ) : sock( INVALID_SOCKET )
	{
		
	}
	
	//	デストラクタ
	SocketClient::~SocketClient( void )
	{
		if ( sock != INVALID_SOCKET )	closesocket( sock );
	}

	//	TCPクライアント初期化
	bool	SocketClient::InitializeTCP( WORD port, const LPSTR addr )
	{
		//	ポート＆アドレス指定
		ZeroMemory( &server, sizeof( server ) );
		server.sin_family = AF_INET;
		server.sin_port = htons( port );

		struct	hostent*	host = gethostbyname( addr );
		server.sin_addr.S_un.S_addr = *( ( ULONG* )host->h_addr_list[0] );

		//	TCPソケット作成
		sock = socket( AF_INET, SOCK_STREAM, 0 );
		if ( sock == INVALID_SOCKET )	return	false;

		//	タイムアウト設定( 1000ms )
		int	timeout = TIME_OUT;
		if ( setsockopt( sock, SOL_SOCKET, SO_RCVTIMEO, ( LPSTR )&timeout, sizeof( timeout ) ) == SOCKET_ERROR )
			return	false;

		//	サーバー接続
		if( connect( sock, ( sockaddr* )&server, sizeof( server ) ) == SOCKET_ERROR )	return	false;
		return	true;

	}

	//	UDPクライアント初期化
	bool	SocketClient::InitializeUDP( WORD port, const LPSTR addr )
	{
		//	ポート＆アドレス指定
		ZeroMemory( &server, sizeof( server ) );
		server.sin_family = AF_INET;
		server.sin_port = htons( port );

		struct	 hostent*	host = gethostbyname( addr );
		server.sin_addr.S_un.S_addr = *( ( ULONG* )host->h_addr_list[0] );

		//	UDPソケット作成
		sock = socket( AF_INET, SOCK_DGRAM, 0 );
		if ( sock == INVALID_SOCKET )	return	false;

		//	タイムアウト設定( 1000ms )
		int	timeout = TIME_OUT;
		if ( setsockopt( sock, SOL_SOCKET, SO_RCVTIMEO, ( LPSTR )&timeout, sizeof( timeout ) ) == SOCKET_ERROR )
			return	false;

		return	true;
	}

//-------------------------------------------------------------------------------
//	送受信
//-------------------------------------------------------------------------------
	
	//	データ送信
	void	SocketClient::Send( const LPSTR data, int size )
	{
		sendto( sock, data, size, 0, ( struct sockaddr* )&server, sizeof( server ) );
	}

	//	データ受信
	int	SocketClient::Receive( const LPSTR data, int size )
	{
		int	recvSize;
		recvSize = recv( sock, data, size, 0 );

		//	エラー(タイムアウト)判定
		if ( recvSize == SOCKET_ERROR )	return	0;

		return	recvSize;
	}