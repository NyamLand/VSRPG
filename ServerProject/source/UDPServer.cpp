
#include	"UDPServer.h"
#include	"GameParam.h"
#pragma comment( lib, "wsock32.lib" )

//********************************************************************
//
//	UDPServer�N���X
//
//********************************************************************

//-------------------------------------------------------------------------------
//	�������E���
//-------------------------------------------------------------------------------

	//	�R���X�g���N�^
	UDPServer::UDPServer( void ) : sock( INVALID_SOCKET )
	{
		//	�S�N���C�A���g�A�h���X������
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			client_addr[i].sin_addr.S_un.S_addr = 0;
		}
	}

	//	�f�X�g���N�^
	UDPServer::~UDPServer( void )
	{
		if ( sock != INVALID_SOCKET )	closesocket( sock );
	}

	//	������
	bool	UDPServer::Initialize( WORD port )
	{
		struct	sockaddr_in	server;

		//	�T�[�o�[���ݒ�
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons( port );

		//	UDP�\�P�b�g�쐬
		sock = socket( AF_INET, SOCK_DGRAM, 0 );

		//	�T�[�o�[����
		bind( sock, ( struct sockaddr* )&server, sizeof( server ) );

		//	�\�P�b�g���X�g�ɓo�^
		FD_ZERO( &fds );
		FD_SET( sock, &fds );

		//	��TCP�Ƃ̈Ⴂ�̓\�P�b�g�̎�ނ�listen����������
		return	true;
	}

//-------------------------------------------------------------------------------
//	����M
//-------------------------------------------------------------------------------
	
	//	���M
	void	UDPServer::Send( int client, const LPSTR data, int size )
	{
		sendto( sock, data, size, 0, ( struct sockaddr* )&client_addr[client], sizeof( client_addr[client] ) );
	}

	//	��M
	int		UDPServer::Receive( const LPSTR data, int* size )
	{
		//	�^�C���A�E�g�ݒ�
		struct	timeval	tv = { 0, 1000 };

		//	�\�P�b�g���X�g������
		fd_set	fd_work;
		memcpy( &fd_work, &fds, sizeof( fd_set ) );

		//	��M��ԃ\�P�b�g�̌���
		int n = select( 0, &fd_work, NULL, NULL, &tv );

		//	�^�C���A�E�g�̏ꍇ��select��0��������
		if ( n <= 0 )	return	-1;

		//	�f�[�^��M�p�ϐ�����
		int		recvsize;
		int		addr_len;
		struct	sockaddr_in	addr;

		//	�f�[�^��M
		addr_len = sizeof( struct sockaddr_in );
		recvsize = recvfrom( sock, data, *size, 0, ( struct sockaddr* )&addr, &addr_len );
		*size = recvsize;
		if ( recvsize <= 0 )	return	-1;	//	�G���[

		int	command = ( int )data[COMMAND];

		if ( command == COMMANDS::SIGN_UP )
		{
			//	�V�K�����
			for ( int i = 0; i<PLAYER_MAX; i++ )
			{
				if ( client_addr[i].sin_addr.S_un.S_addr != 0 ) continue;
				client_addr[i] = addr;
				return i;
			}
		}

		//	�N���C�A���g����
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			if ( client_addr[i].sin_addr.S_un.S_addr == 0 ) continue;

			if ( addr.sin_addr.S_un.S_addr == client_addr[i].sin_addr.S_un.S_addr )
			{
				int id = atoi( &data[ID] );
				if ( i == id )	return	i;
				else continue;
			}
		}
	
		return	-1;
	}

//-------------------------------------------------------------------------------
//	�N���C�A���g�I��
//-------------------------------------------------------------------------------

	//	�N���C�A���g�I��
	void	UDPServer::CloseClient( int client )
	{
		client_addr[client].sin_addr.S_un.S_addr = 0;
	}