
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
	bool	InitializeTCP( WORD port, const LPSTR addr );
	bool	InitializeUDP( WORD port, const LPSTR addr );

	//	����M
	void	Send( const LPSTR data, int size );
	int		Receive( const LPSTR data, int size );

	//	����֐�

};
