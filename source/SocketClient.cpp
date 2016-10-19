#include	"SocketClient.h"
#pragma comment( lib, "wsock32.lib" )

bool SocketClient::InitializeTCP( WORD port, char* addr )
{
	//	ポート＆アドレス指定
	ZeroMemory( &server, sizeof(server) );
	server.sin_family = AF_INET;
	server.sin_port   = htons(port);

	struct hostent *host = gethostbyname(addr);
	server.sin_addr.S_un.S_addr = *((ULONG*)host->h_addr_list[0]);
	
	//	TCPソケット作成
	sock = socket( AF_INET, SOCK_STREAM, 0 );
	if( sock == INVALID_SOCKET ) return false;

	//	タイムアウト設定(1000ms)	
	int timeout = 1000;
	if( setsockopt( sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout) ) == SOCKET_ERROR ) return false;

	//	サーバー接続
	if( connect( sock, (sockaddr*)&server, sizeof(server) ) == SOCKET_ERROR ) return false;

	return true;
}

bool SocketClient::InitializeUDP( WORD port, char* addr )
{
	//	サーバー情報設定 	
	ZeroMemory( &server, sizeof(server) );
	server.sin_family=AF_INET;
	server.sin_port = htons(port);

	struct	hostent *host = gethostbyname(addr);
	server.sin_addr.S_un.S_addr = *((ULONG*)host->h_addr_list[0]);

	//	UDPソケットの作成	
	sock = socket( AF_INET, SOCK_DGRAM, 0);
	if( sock == INVALID_SOCKET ) return false;

	//	タイムアウト設定(1000ms)	
	int timeout = 1000;
	if( setsockopt( sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout) ) == SOCKET_ERROR ) return false;

	return true;
}

//		データ送信		
void SocketClient::send( char *data, int size )
{	
	sendto( sock, data, size, 0, (struct sockaddr *)&server, sizeof(server) );
}

//		データ受信		
int	SocketClient::receive( char *data, int size )
{
	int recvsize = recv( sock, data, size, 0 );
	//	エラー(タイムアウト)判定		
	if( recvsize == SOCKET_ERROR ) return -1;

	return recvsize;
}
