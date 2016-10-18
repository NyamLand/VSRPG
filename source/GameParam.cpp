
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
		playerManager->GetPlayer()->SetPos( netChara.pos );
		return	true;
	}

	//	�E��
	void	GameParam::CloseClient( void )
	{
		NET_OUT	netOut;
		netOut.id = myIndex;
		SocketClient::Send( ( LPSTR )&netOut, sizeof( NET_OUT ) );
	}

//----------------------------------------------------------------------------------
//	�X�V
//----------------------------------------------------------------------------------

	//	�X�V
	void	GameParam::Update( void )
	{
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
			if ( size <= 0 )	return; 

			//	�擪�A�h���X���s���Ȃ�΃��[�v�𔲂���
			if ( data[COMMAND] == NO_COMMAND )	{ return; }

			//	�擪�o�C�g�ŕ���
			switch ( data[COMMAND] )
			{
			case COMMANDS::CHARA_INFO:
				CharaInfoReceive( data );
				break;

			case COMMANDS::SIGN_UP:
				SignUpReceive( data );
				break;

			case COMMANDS::SIGN_OUT:
				SignOutReceive( data );
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
		//	�ʒu�f�[�^���M
		SendCharaData();
	}

//----------------------------------------------------------------------------------
//	��M����
//----------------------------------------------------------------------------------

	//	�L�����f�[�^��M
	void	GameParam::CharaInfoReceive( const LPSTR& data )
	{
		NET_CHARA*	netChara = ( NET_CHARA* )data;
		SetPlayerParam( netChara->id, netChara->pos, netChara->angle );
	}

	//	�T�C���A�b�v��M
	void	GameParam::SignUpReceive( const LPSTR& data )
	{
		NET_IN*	netIn = ( NET_IN* )data;
		SetPlayerInfo( netIn->id, netIn->name );
		printf( "%dP %s���Q�����܂����B\n", netIn->id, netIn->name );
	}

	//	�T�C���A�E�g��M
	void	GameParam::SignOutReceive( const LPSTR& data )
	{
		NET_OUT*	netOut = ( NET_OUT* )data;
		playerInfo[netOut->id].active = false;
		printf( "%dP %s���񂪃��O�A�E�g���܂����B\n", netOut->id, playerInfo[netOut->id].name );
	}

//----------------------------------------------------------------------------------
//	���M����
//----------------------------------------------------------------------------------

	//	�ʒu�f�[�^���M
	void	GameParam::SendCharaData( void )
	{
		//	�ʒu�f�[�^���M
		NET_CHARA	netChara;

		//	�v���C���[�̈ʒu��񑗐M( ��Ŋ֐��� )
		netChara.id = myIndex;
		netChara.pos = playerManager->GetPlayer()->GetPos();
		netChara.angle = playerManager->GetPlayer()->GetAngle();
		SocketClient::Send( ( LPSTR )&netChara, sizeof( NET_CHARA ) );
	}

//----------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------

	//	�v���C���[���ݒ�
	void	GameParam::SetPlayerInfo( int id, const LPSTR& name )
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
	void	GameParam::SetPlayerParam( int id, const PlayerParam& param )
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