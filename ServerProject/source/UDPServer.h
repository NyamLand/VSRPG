
#pragma once

//********************************************************************
//
//	UDPServerクラス
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
	//	初期化・解放
	UDPServer( void );
	virtual ~UDPServer( void );
	bool	Initialize( WORD port );

	//	送受信
	void	Send( int client, LPSTR data, int size );
	int		Receive( LPSTR data, int* size );

	//	クライアント終了
	void	CloseClient( int client );
};
