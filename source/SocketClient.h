
#pragma	once

//********************************************************************
//
//	SocketClient�N���X
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
	//	�������E���
	SocketClient( void );
	~SocketClient( void );
	bool	InitializeTCP( WORD port, LPSTR addr );
	bool	InitializeUDP( WORD port, LPSTR addr );

	//	����M
	void	Send( LPSTR data, int size );
	int	Receive( LPSTR data, int size );

	//	����֐�

};
