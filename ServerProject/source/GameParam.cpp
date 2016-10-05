
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameParam.h"

//***************************************************************
//
//	GameParam�N���X
//
//***************************************************************

//-------------------------------------------------------------------------------------
//	�O���[�o��
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//	�������E���
//-------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	GameParam::GameParam( void )
	{
		for ( int id = 0; id < PLAYER_MAX; id++ )
		{
			playerInfo[id].active = false;

			playerParam[id].pos = Vector3( -10.0f + 5.0f * id, 0.0f, 0.0f );
			playerParam[id].angle = 0.0f;
			playerParam[id].motion = 0;
		}
	}

	//	�f�X�g���N�^
	GameParam::~GameParam( void )
	{

	}
	
	//	�T�[�o�[������
	bool	GameParam::InitializeServer( void )
	{
		WSADATA	wsaData;
		
		//	�v������WinSock�̃o�[�W����
		WSAStartup( MAKEWORD( 1, 1 ), &wsaData );

		//	�|�[�g�ԍ�
		Initialize( PORT_NUM );

		return	true;
	}

//-------------------------------------------------------------------------------------
//	��M�E���M
//-------------------------------------------------------------------------------------

	//	���M
	int		GameParam::Send( int client )
	{
		//	�S�N���C�A���g�Ɋe�v���C���[�̏��𑗐M����
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	�v���C���[���A�N�e�B�u��ԂłȂ���΃X�L�b�v
			if ( playerInfo[p].active == false )		continue;

			char	data[256];
			data[0] = 0;

			//	��ԖڂɃv���C���[�ԍ��ۑ�
			*( int* )&data[1] = p;
			
			//	�ܔԖڈȍ~�Ƀp�����[�^���ۑ�
			CopyMemory( &data[5], &playerParam[p], sizeof( PlayerParam ) );
			UDPServer::Send( client, data, sizeof( PlayerParam )+5 );
		}

		char	end = -1;
		UDPServer::Send( client, &end, 1 );

		return	client;
	}

	//	��M( ( �� ) �v�֐��� )
	int		GameParam::Receive( void )
	{
		int		client = -1;
		char	data[256];

		int	size = sizeof( data );
		client = UDPServer::Receive( data, &size );
		
		if ( client == -1 )		return	-1;

		//	data�̂O�Ԗڂɂ���ď�����ς���
		switch ( data[0] )
		{
			//	�ړ�����M
			case RECEIVE_MODE::MOVE:
				{
					NET_MOVE* d = ( NET_MOVE* )data;
					playerParam[client].move = Vector3( d->vx, 0.0f, d->vz );
				}
				break;

			//	�`���b�g
			case RECEIVE_MODE::CHAT:
				{

					//	id�ɃN���C�A���gID���Z�b�g
					NET_CHAT*	chat = ( NET_CHAT* )data;
					chat->id = client;

					//	�S���Ƀ��b�Z�[�W�𑗐M
					for ( int p = 0; p < PLAYER_MAX; p++ )
					{
						//	���Ȃ���΃X�L�b�v
						if ( playerInfo[p].active == false )continue;

						UDPServer::Send( p, ( LPSTR )chat, sizeof( NET_CHAT ) );
					}

					//	�`���b�g�̏ꍇ�N���C�A���g�ł͂Ȃ�-�P��Ԃ�
					return	-1;
				}
				break;

			case RECEIVE_MODE::SIGN_UP:
				{
					//	�v���C���[��o�^����
					NET_INFO*	d = ( NET_INFO* )data;
					SetPlayer( client, d->name, d->type );

					//	�\���̂�id�����o��ݒ肵���M�҂֑��M����
					d->id = client;
					UDPServer::Send( d->id, ( LPSTR )d, sizeof( NET_INFO ) );

					//	�S���ɏ�񑗐M
					for ( int p = 0; p < PLAYER_MAX; p++ )
					{
						if ( playerInfo[p].active == false )continue;
						UDPServer::Send( p, ( LPSTR )d, sizeof( NET_INFO ) );

						//	�S���̏���V�K�v���C���[�ɑ��M
						for ( int p = 0; p < PLAYER_MAX; p++ )
						{
							//	�v���C���[�����Ȃ���΃X�L�b�v
							if ( playerInfo[p].active == false )continue;

							//	�\���̂ɃR�s�[
							d->id = p;
							d->type = playerInfo[p].type;
							strcpy( d->name, playerInfo[p].name );
						
							//	���M
							UDPServer::Send( client, ( LPSTR )d, sizeof( NET_INFO ) );
						}
					}
				}
				break;

			case RECEIVE_MODE::SIGN_OUT:
				{
					//	�N���C�A���g�E��
					playerInfo[client].active = false;
					CloseClient( client );
				
					//	�E�ޏ���S�N���C�A���g�֑��M
					NET_OUT	d;
					d.com = SIGN_OUT;
					d.id = client;

					//	�S���Ƀf�[�^���M
					for ( int p = 0; p < PLAYER_MAX; p++ )
					{
						if ( playerInfo[p].active == false )	continue;
						UDPServer::Send( p, ( LPSTR )&d, sizeof( NET_OUT ) );
					}
				}
				break;
		}

		return	client;
	}

//-------------------------------------------------------------------------------------
//	���ݒ�
//-------------------------------------------------------------------------------------

	//	�v���C���[���̐ݒ�
	void	GameParam::SetPlayer( int id, LPSTR name, int type )
	{
		//	id�Ԗڂ̃v���C���[���A�N�e�B�u�ɂ��A�����󂯎��
		playerInfo[id].active = true;
		playerInfo[id].type = type;
		strcpy( playerInfo[id].name, name );
		
		//	�����ʒu�ݒ�
		Vector3	pos = Vector3( -10.0f + 5.0f * id, 0.0f, 0.0f );
		playerParam[id].pos = pos;
		playerParam[id].angle = 0.0f;
		playerParam[id].motion = 1;
		playerParam[id].move = Vector3( 0.0f, 0.0f, 0.0f );
	}

	//	�v���C���[�p�����[�^�̐ݒ�
	void	GameParam::SetPlayerParam( int id, Vector3& pos, float angle, int motion )
	{
		playerParam[id].pos = pos;
		playerParam[id].angle = angle;
		playerParam[id].motion = motion;
	}

	//	�v���C���[�p�����[�^�̐ݒ�
	void	GameParam::SetPlayerParam( int id, PlayerParam& param )
	{
		playerParam[id].pos = param.pos;
		playerParam[id].angle = param.angle;
		playerParam[id].motion = param.motion;
	}

//-------------------------------------------------------------------------------------
//	���擾
//-------------------------------------------------------------------------------------

	//	�v���C���[�p�����[�^�擾
	PlayerParam& GameParam::GetPlayerParam( int id )
	{
		return	playerParam[id];
	}

//-------------------------------------------------------------------------------------
//	�X�V�E�`��
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//	�X�V�E�`��
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//	�X�V�E�`��
//-------------------------------------------------------------------------------------


