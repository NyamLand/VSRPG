
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
			playerParam[id].angle = 0.0f;
			playerParam[id].motion = 0;
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
		Initialize( PORT_NUM );

		return	true;
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
		//	�S�N���C�A���g�Ɋe�v���C���[�̏��𑗐M����
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	�v���C���[���A�N�e�B�u��ԂłȂ���΃X�L�b�v
			if ( playerInfo[p].active == false )		continue;

			NET_MOVE	netMove;
			netMove.com = COMMANDS::CHARA_INFO;
			netMove.id = p;
			netMove.x = playerParam[p].pos.x;
			netMove.y = playerParam[p].pos.y;
			netMove.z = playerParam[p].pos.z;

			UDPServer::Send( client, ( LPSTR )&netMove, sizeof( NET_MOVE ) );
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
		int	size = sizeof( data );

		//	�N���C�A���g����̃f�[�^��M�ƃN���C�A���g�ԍ��̎�M
		client = UDPServer::Receive( data, &size );
		
		if ( client == -1 )		return	-1;

		//	�e��M����
		switch ( data[0] )
		{
		case COMMANDS::CHARA_INFO:
			{
				NET_MOVE*	move = ( NET_MOVE* )data;
				playerParam[client].pos = Vector3( move->x, move->y, move->z );
			}
			break;

		case COMMANDS::SIGN_UP:
			{
				//	�󂯎�����f�[�^���N���C�A���g���ɕϊ�
				NET_INFO*	info = ( NET_INFO* )&data;
				SetPlayer( client, info->name, info->type );

				//	�\���̂�id�����o��ݒ�
				info->id = client;

				//	�N���C�A���g�ɕԐM
				UDPServer::Send( client, ( LPSTR )info, sizeof( NET_INFO ) );

				int a = 0;
				//	�������W�𑗐M
				NET_MOVE*	netMove = ( NET_MOVE* )data;
				netMove->com = COMMANDS::CHARA_INFO;
				netMove->id = client;
				netMove->x = gameManager->GetInitPos( client ).x;
				netMove->y = gameManager->GetInitPos( client ).y;
				netMove->z = gameManager->GetInitPos( client ).z;
				UDPServer::Send( client, ( LPSTR )netMove, sizeof( NET_MOVE ) );

				//	�N���C�A���g�S���Ƀf�[�^�𑗐M
				for ( int p = 0; p < PLAYER_MAX; p++ )
				{
					if ( playerInfo[p].active == false )	continue;
					UDPServer::Send( p, ( LPSTR )info, sizeof( NET_INFO ) );
				}

				//	�V�K�̃N���C�A���g�ɑS���̃f�[�^�𑗐M
				for ( int p = 0; p < PLAYER_MAX; p++ )
				{
					if ( playerInfo[p].active == false )	continue;
					info->id = p;
					info->type = playerInfo[p].type;

					strcpy( info->name, playerInfo[p].name );
					UDPServer::Send( client, ( LPSTR )info, sizeof( NET_INFO ) );
				}
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
		Vector3	pos = gameManager->GetInitPos( id );
		playerParam[id].pos = pos;
		playerParam[id].angle = 0.0f;
		playerParam[id].motion = 1;
		//playerParam[id].move = Vector3( 0.0f, 0.0f, 0.0f );
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


