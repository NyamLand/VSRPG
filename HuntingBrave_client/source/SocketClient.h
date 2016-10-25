
#pragma once

//***************************************************************
//
//	SocketClient�N���X
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
	//	�������E���
	SocketClient( void );
	~SocketClient( void );
	
	//	�\�P�b�g������
	bool InitializeTCP( WORD port, char* addr );
	bool InitializeUDP( WORD port, char* addr );

	//	�f�[�^����M
	void	send( char *data, int size );
	int		receive( char *data, int size );
};
