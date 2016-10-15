
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
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
		//	������
		for ( int id = 0; id < PLAYER_MAX; id++ )
		{
			ZeroMemory( &playerInfo[id], sizeof( PlayerInfo ) );			
			ZeroMemory( &playerParam[id], sizeof( PlayerParam ) );
			playerParam[id].pos = Vector3( -10.0f + 5.0f * id, 0.0f, 0.0f );
		}
	}
	
	//	�T�[�o�[������
	bool	GameParam::InitializeServer( void )
	{
		//	WinSock������
		WSADATA	wsaData;
		
		//	�v������WinSock�̃o�[�W����
		WSAStartup( MAKEWORD( 1, 1 ), &wsaData );

		//	UDP�T�[�o�[������
		bool out = Initialize( PORT_NUM );

		return	out;
	}

//-------------------------------------------------------------------------------------
//	�X�V�E�`��
//-------------------------------------------------------------------------------------

	//	�`��
	void	GameParam::Render( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			char str[256];
			sprintf_s( str, "%dP ", p + 1 );

			//	�A�N�e�B�u��ԂȂ���\��
			if ( playerInfo[p].active )
			{
				//	�A�N�e�B�u���ݒ�
				strcat( str, "active  " );

				//	���O�ݒ�
				strcat( str, playerInfo[p].name );
				
				//	���W�ݒ�
				Vector3 pos = playerParam[p].pos;
				char posInfo[256];
				sprintf_s( posInfo, "  pos : %.2f, %.2f, %.2f", pos.x, pos.y, pos.z );
				strcat( str, posInfo );
			}

			IEX_DrawText( str, 20, 100 + p * 30, 500, 200, 0xFFFFFF00 );
		}

	}

//-------------------------------------------------------------------------------------
//	��M�E���M
//-------------------------------------------------------------------------------------

	//	���M
	int		GameParam::Send( int client )
	{
		NET_CHARA	netChara;
		netChara.com = COMMANDS::CHARA_INFO;
		
		//	�S�N���C�A���g�Ɋe�v���C���[�̏��𑗐M����
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	�v���C���[���A�N�e�B�u��ԂłȂ���΃X�L�b�v
			if ( playerInfo[p].active == false )		continue;

			Vector3	pos = playerParam[p].pos;
			netChara.id = p;
			netChara.x = pos.x;
			netChara.y = pos.y;
			netChara.z = pos.z;
			netChara.angle = playerParam[p].angle;

			UDPServer::Send( client, ( LPSTR )&netChara, sizeof( NET_CHARA ) );

			printf( "%dP�ɍ��W���M���܂����B\n", p + 1 );
		}

		//	�R�}���h�I�[��`����
		char	end = -1;
		UDPServer::Send( client, &end, 1 );

		return	client;
	}

	//	��M( ( �� ) �v�֐��� )
	int		GameParam::Receive( void )
	{
		int		client = -1;
		char	data[256];

		//	�f�[�^�T�C�Y�擾
		//	�N���C�A���g����̃f�[�^��M�ƃN���C�A���g�ԍ��̎�M
		int	size = sizeof( data );
		client = UDPServer::Receive( data, &size );
		if ( size <= 0 )	return	-1;
		if ( client < 0 )	return	-1;
		
		//	�e��M����
		switch ( data[DATA_INFO::COMMAND] )
		{
		case COMMANDS::CHARA_INFO:
			{
				NET_CHARA*	netChara = ( NET_CHARA* )&data;
				playerParam[client].pos = Vector3( netChara->x, netChara->y, netChara->z );
				playerParam[client].angle = netChara->angle;
			}
			break;

		case COMMANDS::SIGN_UP:
			{
				//	�󂯎�����f�[�^���N���C�A���g���ɕϊ�
				NET_IN* netIn= ( NET_IN* )&data;
				SetPlayer( client, netIn->name );

				//	�\���̂�id�����o��ݒ�
				netIn->id = client;

				//	�N���C�A���g�ɕԐM
				UDPServer::Send( client, ( LPSTR )netIn, sizeof( NET_IN ) );

				//	�������W�𑗐M
				NET_CHARA	netChara;
				netChara.com = COMMANDS::CHARA_INFO;
				netChara.id = client;
				netChara.x = gameManager->GetInitPos( client ).x;
				netChara.y = gameManager->GetInitPos( client ).y;
				netChara.z = gameManager->GetInitPos( client ).z;
				netChara.angle = 0.0f;
				UDPServer::Send( client, ( LPSTR )&netChara, sizeof( NET_CHARA ) );

				//	�N���C�A���g�S���Ƀf�[�^�𑗐M
				for ( int p = 0; p < PLAYER_MAX; p++ )
				{
					if ( playerInfo[p].active == false )	continue;
					UDPServer::Send( p, ( LPSTR )netIn, sizeof( NET_IN ) );
				}

				//	�V�K�̃N���C�A���g�ɑS���̃f�[�^�𑗐M
				for ( int p = 0; p < PLAYER_MAX; p++ )
				{
					if ( playerInfo[p].active == false )	continue;

					netIn->id = p;
					strcpy( netIn->name, playerInfo[p].name );
					UDPServer::Send( client, ( LPSTR )netIn, sizeof( NET_IN ) );
				}

				printf( "%dP���Q�킵�܂����B\n", client + 1 );
			}
			break;

		case COMMANDS::SIGN_OUT:
			{
				//	�v���C���[�A�N�e�B�u��false�ɂ���
				playerInfo[client].active = false;

				//	�N���C�A���g�����
				CloseClient( client );

				NET_OUT	out;
				out.com = COMMANDS::SIGN_OUT;
				out.id = client;

				//	�S���ɏ�񑗐M
				for ( int p = 0; p < PLAYER_MAX; p++ )
				{
					if ( playerInfo[p].active == false )	continue;
					UDPServer::Send( p, ( LPSTR )&out, sizeof( NET_OUT ) );
				}

				printf( "%dP���E�ނ��܂����B\n", client + 1 );
			}
			break;
		}
		return	client;
	}

//-------------------------------------------------------------------------------------
//	���ݒ�
//-------------------------------------------------------------------------------------

	//	�v���C���[���̐ݒ�
	void	GameParam::SetPlayer( int id, const LPSTR name )
	{
		//	id�Ԗڂ̃v���C���[���A�N�e�B�u�ɂ��A�����󂯎��
		playerInfo[id].active = true;
		strcpy( playerInfo[id].name, name );
		
		//	�����ʒu�ݒ�
		Vector3	pos = gameManager->GetInitPos( id );
		playerParam[id].pos = pos;
		playerParam[id].angle = 0.0f;
	}

	//	�v���C���[�p�����[�^�̐ݒ�
	void	GameParam::SetPlayerParam( int id, const Vector3& pos, float angle )
	{
		playerParam[id].pos = pos;
		playerParam[id].angle = angle;
	}

	//	�v���C���[�p�����[�^�̐ݒ�
	void	GameParam::SetPlayerParam( int id, const PlayerParam& param )
	{
		playerParam[id].pos = param.pos;
		playerParam[id].angle = param.angle;
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


