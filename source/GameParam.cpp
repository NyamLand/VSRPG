
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
		NET_IN		netIn;
		netIn.com = COMMANDS::SIGN_UP;
		netIn.id = -1;
		strcpy( netIn.name, name );

		//	�T�[�o�[�Ƀv���C���[���𑗐M
		SocketClient::Send( ( LPSTR )&netIn, sizeof( netIn ) );

		//	�l�h�c�擾
		int	size = SocketClient::Receive( ( LPSTR )&netIn, sizeof( netIn ) );
		if ( size <= 0 )	return	false;
		myIndex = netIn.id;
		SetPlayerInfo( netIn.id, netIn.name );

		//	�������W�擾
		NET_CHARA netChara;
		SocketClient::Receive( ( LPSTR )&netChara, sizeof( netChara ) );
		playerManager->GetPlayer()->SetPos( Vector3( netChara.x, netChara.y, netChara.z ) );
		return	true;
	}

	//	�E��
	void	GameParam::CloseClient( void )
	{
		NET_OUT	netOut;
		netOut.com = SIGN_OUT;
		netOut.id = myIndex;
		SocketClient::Send( ( LPSTR )&netOut, sizeof( NET_OUT ) );
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
		NET_CHARA	netChara;

		//	�v���C���[�̈ʒu��񑗐M( ��Ŋ֐��� )
		netChara.com = COMMANDS::CHARA_INFO;
		netChara.id = myIndex;
		netChara.x = playerManager->GetPlayer()->GetPos().x;
		netChara.y = playerManager->GetPlayer()->GetPos().y;
		netChara.z = playerManager->GetPlayer()->GetPos().z;
		netChara.angle = playerManager->GetPlayer()->GetAngle();
		SocketClient::Send( ( LPSTR )&netChara, sizeof( NET_CHARA ) );
	}

//----------------------------------------------------------------------------------
//	�f�[�^����M
//----------------------------------------------------------------------------------

	//	��M
	void	GameParam::Receive( void )
	{
		char data[256];

		//	�f�[�^����M
		for (;;)
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
			if ( data[COMMAND] == NO_COMMAND )	{ return; }

			//	�擪�o�C�g�ŕ���
			switch ( data[COMMAND] )
			{
			case COMMANDS::CHARA_INFO:
				{
					NET_CHARA*	netChara = ( NET_CHARA* )&data;
					SetPlayerParam( netChara->id, Vector3( netChara->x, netChara->y, netChara->z ), netChara->angle );
				}
				break;

			case COMMANDS::SIGN_UP:
				{
					NET_IN*	netIn = ( NET_IN* )&data;
					SetPlayerInfo( netIn->id, netIn->name );
					printf( "%dP %s���Q�����܂����B\n", netIn->id, netIn->name );
				}
				break;

			case COMMANDS::SIGN_OUT:
				{
					NET_OUT*	netOut = ( NET_OUT* )&data;
					playerInfo[netOut->id].active = false;
					printf( "%dP %s���񂪃��O�A�E�g���܂����B\n", netOut->id, playerInfo[netOut->id].name );
				}
				break;

			default:
				printf( "????\n" );
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
	void	GameParam::SetPlayerInfo( int id, const LPSTR name )
	{
		playerInfo[id].active = true;
		strcpy( playerInfo[id].name, name );
	}

	//	�v���C���[�p�����[�^�ݒ�
	void	GameParam::SetPlayerParam( int id, const Vector3& pos, float angle )
	{
		playerParam[id].pos = pos;
		playerParam[id].angle = angle;
	}

	//	�v���C���[�p�����[�^�ݒ�
	void	GameParam::SetPlayerParam( int id, PlayerParam& param )
	{
		playerParam[id].pos = param.pos;
		playerParam[id].angle = param.angle;
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