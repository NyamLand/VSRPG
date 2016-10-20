
#include	"iextreme.h"
#include	"GameParam.h"

//*****************************************************************************************************************************
//
//		�Q�[���f�[�^�Ǘ�
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	GameParam::GameParam( void )
	{
		for( int id = 0 ; id < PLAYER_MAX ; id++ )
		{
			playerInfo[id].active = false;

			playerParam[id].pos = Vector3( 0.0f, 0.0f, 0.0f );
			playerParam[id].angle = 0.0f;
		}
	}

	//	�T�[�o�[������
	bool GameParam::InitializeServer( void )
	{
		//	WinSock������
		WSADATA	wsaData;
		WSAStartup( MAKEWORD( 1, 1 ), &wsaData );
		bool successInit = Initialize( 7000 );

		if ( successInit )
		{
			printf( "�T�[�o�[����������\n" );
		}
		return successInit;
	}

//----------------------------------------------------------------------------------------------
//	�f�[�^����M
//----------------------------------------------------------------------------------------------

	//	���M
	int		GameParam::Send( int client )
	{
		if( client == -1 ) return -1;
	
		//	�S�f�[�^���M
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if( playerInfo[p].active == false ) continue;

			NET_CHARA netChara;
			netChara.id = p;
			netChara.com = 0;
			netChara.pos = playerParam[p].pos;
			send( client, ( LPSTR )&netChara, sizeof( NET_CHARA ) );
		}

		//	�I�[�ʒm
		char end = -1;
		send( client, &end, 1 );
		return client;
	}

	//	��M
	int		GameParam::Receive( void )
	{
		char	data[256];
		int		size = sizeof( data );
		int		client = receive( data, &size );
		if( client == -1 ) return -1;
		
		switch( data[COMMAND] )
		{
		case COMMANDS::CHARA_INFO:		//	�ړ����
			{
				NET_CHARA* d = ( NET_CHARA* )&data;
				playerParam[client].pos = d->pos;
			}
			break;

		case COMMANDS::SIGN_UP:	//	�V�K�Q��
			{
				NET_IN* netIn = ( NET_IN* )&data;
				SetPlayer( client, netIn->name );

				netIn->id = client;
				send( client, ( char* )netIn, sizeof( NET_IN ) );

				//	�S���Ƀf�[�^���M
				for( int p = 0 ; p < PLAYER_MAX ; p++ )
				{
					if( playerInfo[p].active == false ) continue;
					send( p, ( char* )netIn, sizeof( NET_IN ) );
				}

				//	�S�f�[�^���M
				for( int p=0 ; p<PLAYER_MAX ; p++ )
				{
					if( playerInfo[p].active == false ) continue;
					netIn->id = p;
					strcpy( netIn->name, playerInfo[p].name );
					send( client, ( char* )netIn, sizeof( NET_IN ) );
				}
				printf( "%dP %s���񂪎Q�����܂����B\n", client + 1, netIn->name );
			}
			break;

		case COMMANDS::SIGN_OUT:
			{
				playerInfo[client].active = false;
				CloseClient( client );

				NET_OUT	d;
				d.com = COMMANDS::SIGN_OUT;
				d.id  = client;

				//	�S���Ƀf�[�^���M
				for( int p = 0 ; p < PLAYER_MAX ; p++ )
				{
					if( playerInfo[p].active == false ) continue;
					send( p, ( char* )&d, sizeof( NET_OUT ) );
				}
				printf( "%dP %s���񂪒E�ނ��܂����B\n", client + 1, playerInfo[client].name );
			}		
			break;
		}
		return client;
	}

//----------------------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------------------

	//	�v���C���[���ݒ�
	void	GameParam::SetPlayer( int id, char* name )
	{
		//	�v���C���[���ݒ�
		playerInfo[id].active = true;
		strcpy( playerInfo[id].name, name );

		//	�p�����[�^������
		playerParam[id].pos = Vector3( 0.0f, 0.0f, 0.0f );
		playerParam[id].angle  = 0.0f;
	}

	//	�v���C���[�p�����[�^�ݒ�
	void	GameParam::SetPlayerParam( int id, Vector3& pos, float angle )
	{
		playerParam[id].pos    = pos;
		playerParam[id].angle  = angle;
	}

	//	�v���C���[�p�����[�^�ݒ�
	void	GameParam::SetPlayerParam( int id, PlayerParam& param )
	{
		playerParam[id].pos    = param.pos;
		playerParam[id].angle  = param.angle;
	}

