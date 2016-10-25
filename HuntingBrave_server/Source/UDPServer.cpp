#include	"UDPServer.h"
#pragma comment( lib, "wsock32.lib" )

bool UDPServer::Initialize( WORD port )
{
	struct	sockaddr_in server;
	//	�T�[�o�[���ݒ� 
	server.sin_family=AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(port);

	//	�\�P�b�g�쐬���ڑ��҂� 
	sock = socket(AF_INET,SOCK_DGRAM,0);
	bind(sock, (sockaddr*)&server,sizeof(server));

	for( int i=0 ; i<NUM_CLIENT ; i++ ){
		client_addr[i].sin_addr.S_un.S_addr = 0;
	}

	// fd_set�̏��������܂�
	FD_ZERO(&fds);
	FD_SET( sock, &fds );

	return true;
}

//		�f�[�^���M		
void UDPServer::send( int client, char *data, int size )
{	
	sendto( sock, data, size, 0, (struct sockaddr *)&client_addr[client], sizeof(client_addr[client]) );
}

//		�f�[�^��M		
int	UDPServer::receive( char *data, int *size )
{
	struct timeval tv;
	tv.tv_sec  = 0;
	tv.tv_usec = 0;

	fd_set	fd_work;
	memcpy(&fd_work, &fds, sizeof(fd_set));
	// fds�ɐݒ肳�ꂽ�\�P�b�g���ǂݍ��݉\�ɂȂ�܂ő҂��܂�
	int n = select(0, &fd_work, NULL, NULL, &tv);
	// �^�C���A�E�g�̏ꍇ��select��0��Ԃ��܂�
	if (n <= 0) return -1;

	int		i, recvsize;
	int		addr_len;
	struct	sockaddr_in addr;

	//	�f�[�^��M 
	addr_len = sizeof(struct sockaddr_in);
	recvsize = recvfrom(sock, data, *size, 0, (struct sockaddr *)&addr, &addr_len );

	*size = recvsize;
	if( recvsize <= 0 ) return -1;

	//	�N���C�A���g����
	for( i=0 ; i<NUM_CLIENT ; i++ ){
		if( client_addr[i].sin_addr.S_un.S_addr == 0 ) continue;
		if( addr.sin_addr.S_un.S_addr == client_addr[i].sin_addr.S_un.S_addr ) return i;
	}

	//	�V�K�����
	for( i=0 ; i<NUM_CLIENT ; i++ ){
		if( client_addr[i].sin_addr.S_un.S_addr != 0 ) continue;
		client_addr[i] = addr;
		return i;
	}
	return -1;
}
