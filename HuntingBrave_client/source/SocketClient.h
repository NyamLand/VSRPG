
#pragma once

//***************************************************************
//
//	SocketClientクラス
//
//***************************************************************

//	include
#include	<winsock.h>

//	class
class SocketClient
{
protected:
	SOCKET	sock;
	struct sockaddr_in server;
	
public:
	//	初期化・解放
	SocketClient( void );
	~SocketClient( void );
	
	//	ソケット初期化
	bool InitializeTCP( WORD port, char* addr );
	bool InitializeUDP( WORD port, char* addr );

	//	データ送受信
	void	send( char *data, int size );
	int		receive( char *data, int size );
};
