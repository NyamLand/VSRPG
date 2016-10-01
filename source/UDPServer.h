
#pragma once

//********************************************************************
//
//	UDPServer�N���X
//
//********************************************************************

//	include&define
#include	<winsock.h>
//#include	"define.h"

//	class
class UDPServer
{
private:
protected:
	SOCKET	sock;
	struct	sockaddr_in	client_addr[4];
	fd_set		fds;

public:
	//	�������E���
	UDPServer( void );
	~UDPServer( void );
	bool	Initialize( WORD port );

	//	����M
	void	Send( int client, LPSTR data, int size );
	int	Receive( LPSTR data, int* size );

	//	�N���C�A���g�I��
	void	CloseClient( int client );
};
