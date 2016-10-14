
#pragma	once

//********************************************************************
//
//	SocketClientクラス
//
//********************************************************************

//	include&define
#include	<winsock.h>


//	class
class SocketClient
{
//private:
protected:
	SOCKET	sock;
	struct	sockaddr_in		server;

public:
	//	初期化・解放
	SocketClient( void );
	~SocketClient( void );
	bool	InitializeTCP( WORD port, const LPSTR addr );
	bool	InitializeUDP( WORD port, const LPSTR addr );

	//	送受信
	void	Send( const LPSTR data, int size );
	int		Receive( const LPSTR data, int size );

	//	動作関数

};
