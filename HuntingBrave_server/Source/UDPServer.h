#include	<winsock.h>

#define	NUM_CLIENT	100

class UDPServer
{
private:
protected:
	SOCKET	sock;
	struct sockaddr_in client_addr[NUM_CLIENT];

	fd_set fds;

public:
	UDPServer() : sock(INVALID_SOCKET) {}
	~UDPServer()
	{
		if( sock != INVALID_SOCKET ) closesocket(sock);
	}

	bool Initialize( WORD port );

	void send( int client, char *data, int size );
	int	receive( char *data, int *size );

	void CloseClient( int client ){ client_addr[client].sin_addr.S_un.S_addr = 0; }
};
