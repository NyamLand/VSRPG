
#pragma once

//********************************************************************
//
//	UDPServer�N���X
//
//********************************************************************

//	include&define
#include	"GameData.h"
#include	<winsock.h>

//	class
class UDPServer
{
private:
protected:
	SOCKET	sock;
	struct	sockaddr_in	client_addr[PLAYER_MAX];
	fd_set		fds;

public:
	//	�������E���
	UDPServer( void );
	virtual ~UDPServer( void );
	bool	Initialize( WORD port );

	//	����M
	void	Send( int client, LPSTR data, int size );
	int		Receive( LPSTR data, int* size );

	//	�N���C�A���g�I��
	void	CloseClient( int client );
};
