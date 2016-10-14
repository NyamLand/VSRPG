
#include"SocketClient.h"
#pragma comment( lib, "ws2_32.lib" )
#pragma comment( lib, "winmm.lib" )

//********************************************************************
//
//	SocketClient�N���X
//
//********************************************************************

#define	TIME_OUT	1000

//-------------------------------------------------------------------------------
//	�������E���
//-------------------------------------------------------------------------------

	//	�R���X�g���N�^
	SocketClient::SocketClient( void ) : sock( INVALID_SOCKET )
	{
		
	}
	
	//	�f�X�g���N�^
	SocketClient::~SocketClient( void )
	{
		if ( sock != INVALID_SOCKET )	closesocket( sock );
	}

	//	TCP�N���C�A���g������
	bool	SocketClient::InitializeTCP( WORD port, const LPSTR addr )
	{
		//	�|�[�g���A�h���X�w��
		ZeroMemory( &server, sizeof( server ) );
		server.sin_family = AF_INET;
		server.sin_port = htons( port );

		struct	hostent*	host = gethostbyname( addr );
		server.sin_addr.S_un.S_addr = *( ( ULONG* )host->h_addr_list[0] );

		//	TCP�\�P�b�g�쐬
		sock = socket( AF_INET, SOCK_STREAM, 0 );
		if ( sock == INVALID_SOCKET )	return	false;

		//	�^�C���A�E�g�ݒ�( 1000ms )
		int	timeout = TIME_OUT;
		if ( setsockopt( sock, SOL_SOCKET, SO_RCVTIMEO, ( LPSTR )&timeout, sizeof( timeout ) ) == SOCKET_ERROR )
			return	false;

		//	�T�[�o�[�ڑ�
		if( connect( sock, ( sockaddr* )&server, sizeof( server ) ) == SOCKET_ERROR )	return	false;
		return	true;

	}

	//	UDP�N���C�A���g������
	bool	SocketClient::InitializeUDP( WORD port, const LPSTR addr )
	{
		//	�|�[�g���A�h���X�w��
		ZeroMemory( &server, sizeof( server ) );
		server.sin_family = AF_INET;
		server.sin_port = htons( port );

		struct	 hostent*	host = gethostbyname( addr );
		server.sin_addr.S_un.S_addr = *( ( ULONG* )host->h_addr_list[0] );

		//	UDP�\�P�b�g�쐬
		sock = socket( AF_INET, SOCK_DGRAM, 0 );
		if ( sock == INVALID_SOCKET )	return	false;

		//	�^�C���A�E�g�ݒ�( 1000ms )
		int	timeout = TIME_OUT;
		if ( setsockopt( sock, SOL_SOCKET, SO_RCVTIMEO, ( LPSTR )&timeout, sizeof( timeout ) ) == SOCKET_ERROR )
			return	false;

		return	true;
	}

//-------------------------------------------------------------------------------
//	����M
//-------------------------------------------------------------------------------
	
	//	�f�[�^���M
	void	SocketClient::Send( const LPSTR data, int size )
	{
		sendto( sock, data, size, 0, ( struct sockaddr* )&server, sizeof( server ) );
	}

	//	�f�[�^��M
	int	SocketClient::Receive( const LPSTR data, int size )
	{
		int	recvSize;
		recvSize = recv( sock, data, size, 0 );

		//	�G���[(�^�C���A�E�g)����
		if ( recvSize == SOCKET_ERROR )	return	0;

		return	recvSize;
	}