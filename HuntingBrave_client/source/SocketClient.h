
#pragma once

#include	<winsock.h>

class SocketClient
{
private:
protected:
	SOCKET	sock;
	struct sockaddr_in server;

public:
	SocketClient() : sock(INVALID_SOCKET) {}
	~SocketClient()
	{
		if( sock != INVALID_SOCKET ) closesocket(sock);
	}

	bool InitializeTCP( WORD port, char* addr );
	bool InitializeUDP( WORD port, char* addr );

	void send( char *data, int size );
	int	receive( char *data, int size );
};
