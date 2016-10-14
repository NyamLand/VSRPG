
#include	"iextreme.h"
#include	<thread>
#include	"GlobalFunction.h"
#include	"PlayerManager.h"
#include	"GameParam.h"

//***************************************************************
//
//	GameParam�N���X
//
//***************************************************************

//----------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------

GameParam*	gameParam = nullptr;

//----------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------

	//	�R���X�g���N�^
	GameParam::GameParam( void )
	{
		//	�v���C���[�f�[�^������
		for ( int id = 0; id < PLAYER_MAX; id++ )
		{
			ZeroMemory( &playerInfo[id], sizeof( PlayerInfo ) );
			ZeroMemory( &playerParam[id], sizeof( PlayerParam ) );
		}
	}

	//	�f�X�g���N�^
	GameParam::~GameParam( void )
	{
		CloseClient();
	}

	//	�N���C�A���g������
	bool	GameParam::InitializeClient( LPSTR addr, int nPort, LPSTR name, int type )
	{
		//	�N���C�A���g������
		InitializeUDP( nPort, addr );

		//	�^�C�v�Ɩ��O�̑��M
		NET_INFO	info;
		info.com = COMMANDS::SIGN_UP;
		info.id = -1;
		info.type = type;
		strcpy( info.name, name );

		//	�T�[�o�[�Ƀv���C���[���𑗐M
		SocketClient::Send( ( LPSTR )&info, sizeof( info ) );

		//	�l�h�c�擾
		int	size = SocketClient::Receive( ( LPSTR )&info, sizeof( info ) );
		if ( size <= 0 )	return	false;
		myIndex = info.id;
		SetPlayerInfo( info.id, info.name, info.type );

		//	�������W�擾
		NET_MOVE netMove;
		netMove.com = COMMANDS::CHARA_INFO;
		netMove.id = myIndex;
		SocketClient::Receive( ( LPSTR )&netMove, sizeof( netMove ) );
		playerManager->GetPlayer()->SetPos( Vector3( netMove.x, 0.0f, netMove.z ) );
		return	true;
	}

	//	�E��
	void	GameParam::CloseClient( void )
	{
		char	com = COMMANDS::SIGN_OUT;
		SocketClient::Send( &com, sizeof( char ) );
	}

//----------------------------------------------------------------------------------
//	�X�V
//----------------------------------------------------------------------------------

	//	�X�V
	void	GameParam::Update( void )
	{
		//	�S�f�[�^��M
		//Receive();

		//	�ʒu�f�[�^���M
		NET_MOVE	netMove;

		//	�v���C���[�̈ʒu��񑗐M( ��Ŋ֐��� )
		netMove.com = COMMANDS::CHARA_INFO;
		netMove.id = myIndex;
		netMove.x = playerManager->GetPlayer()->GetPos().x;
		netMove.y = playerManager->GetPlayer()->GetPos().y;
		netMove.z = playerManager->GetPlayer()->GetPos().z;
		SocketClient::Send( ( LPSTR )&netMove, sizeof( NET_MOVE ) );

		printf( "���W�𑗐M���܂����B\n" );
	}

//----------------------------------------------------------------------------------
//	�f�[�^����M
//----------------------------------------------------------------------------------

	//	��M
	void	GameParam::Receive( void )
	{
		char data[256];

		//	�f�[�^����M
		//for (;;)
		{
			//	��M
			int	size = SocketClient::Receive( data, 256 );

			//	��M�o����T�C�Y���Ȃ���΃��[�v�𔲂���
			if ( size <= 0 )	
			{ 
				printf( "size = %d\n", size );
				return; 
			}

			//	�擪�A�h���X���s���Ȃ�΃��[�v�𔲂���
			if ( data[0] == -1 )	{ return; }

			//	�擪�o�C�g�ŕ���
			switch ( data[0] )
			{
			case COMMANDS::CHARA_INFO:
				{
					NET_MOVE*	netMove = ( NET_MOVE* )data;
					SetPlayerParam( netMove->id, Vector3( netMove->x, 0.0f, netMove->z ), 0.0f, 0 );
					printf( "���W��M���܂����B\n" );
				}
				break;

			case COMMANDS::SIGN_UP:
				{
					NET_INFO*	info;
					info = ( NET_INFO* )data;

					SetPlayerInfo( info->id, info->name, info->type );

					printf( "�T�C���A�b�v���܂����B\n" );
				}
				break;

			case COMMANDS::SIGN_OUT:
				break;
			}
		}
	}

	//	���M
	void	GameParam::Send( void )
	{

	}

//----------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------

	//	�v���C���[���ݒ�
	void	GameParam::SetPlayerInfo( int id, LPSTR name, int type )
	{
		playerInfo[id].active = true;
		playerInfo[id].type = type;
		strcpy( playerInfo[id].name, name );
	}

	//	�v���C���[�p�����[�^�ݒ�
	void	GameParam::SetPlayerParam( int id, Vector3& pos, float angle, int motion )
	{
		playerParam[id].pos = pos;
		playerParam[id].angle = angle;
		playerParam[id].motion = motion;
	}

	//	�v���C���[�p�����[�^�ݒ�
	void	GameParam::SetPlayerParam( int id, PlayerParam& param )
	{
		playerParam[id].pos = param.pos;
		playerParam[id].angle = param.angle;
		playerParam[id].motion = param.motion;
	}

//----------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------

	//	�e�v���C���[���擾
	PlayerInfo	GameParam::GetPlayerInfo( int id )const
	{
		return	playerInfo[id];
	}

	//	�e�v���C���[�p�����[�^�擾
	PlayerParam GameParam::GetPlayerParam( int id )const
	{
		return	playerParam[id];
	}

	//	������Id�擾
	PlayerInfo	GameParam::GetMyInfo( int id )const
	{
		return	playerInfo[id];
	}

	//	������ID�擾( Player�ԍ� )
	int		GameParam::GetMyIndex( void )const
	{
		return	myIndex;
	}