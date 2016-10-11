
#include	"iextreme.h"
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
			ZeroMemory( &playerInfo[id], sizeof( playerInfo[id] ) );
			ZeroMemory( &playerParam[id], sizeof( playerParam[id] ) );
		}

		//	�֐��|�C���^�ݒ�
		ReceiveFunction[DATA_MODE::POS] = &GameParam::PosReceive;
		ReceiveFunction[DATA_MODE::MOVE] = &GameParam::MoveReceive;
		ReceiveFunction[DATA_MODE::CHAT] = &GameParam::ChatReceive;
		ReceiveFunction[DATA_MODE::SIGN_UP] = &GameParam::SignUpReceive;
		ReceiveFunction[DATA_MODE::SIGN_OUT] = &GameParam::SignOutReceive;
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
		info.com = DATA_MODE::SIGN_UP;
		info.type = type;
		strcpy( info.name, name );

		//	�T�[�o�[�Ƀv���C���[���𑗐M
		SocketClient::Send( ( LPSTR )&info, sizeof( info ) );

		//	�l�h�c�擾
		int	size = SocketClient::Receive( ( LPSTR )&info, sizeof( info ) );
		if ( size <= 0 )	return	false;
		myIndex = info.id;

		//	�������W�擾
		NET_POS netPos;
		netPos.com = DATA_MODE::POS;
		netPos.id = myIndex;
		SocketClient::Receive( ( LPSTR )&netPos, sizeof( netPos ) );
		playerManager->GetPlayer()->SetPos( netPos.pos );
		return	true;
	}

	//	�E��
	void	GameParam::CloseClient( void )
	{
		char	com = DATA_MODE::SIGN_OUT;
		SocketClient::Send( &com, sizeof( char ) );
	}

//----------------------------------------------------------------------------------
//	�X�V
//----------------------------------------------------------------------------------

	//	�X�V
	void	GameParam::Update( void )
	{
		//	�S�f�[�^��M
		Receive();

		//	�ʒu�f�[�^���M
		NET_POS	netData;

		//	�v���C���[�̈ʒu��񑗐M( ��Ŋ֐��� )
		netData.com = POS;
		netData.pos = playerManager->GetPlayer()->GetPos();
		SocketClient::Send( ( char* )&netData, sizeof( netData ) );
	}

//----------------------------------------------------------------------------------
//	�f�[�^����M
//----------------------------------------------------------------------------------

	//	��M
	void	GameParam::Receive( void )
	{
		char data[256];

		//	�f�[�^����M
		int	size = SocketClient::Receive( data, 256 );
		if ( size <= 0 )	return;
		if ( data[0] == -1 )	return;

		//	�擪�o�C�g�ŕ���
		( this->*ReceiveFunction[data[0]] )( data );
	}

	//	���M
	void	GameParam::Send( void )
	{

	}

//----------------------------------------------------------------------------------
//	�e�f�[�^��M
//----------------------------------------------------------------------------------
	
	//	���W��M
	void	GameParam::PosReceive( LPSTR data )
	{
		SetPlayerParam(
			*( ( int* )&data[1] ),
			*( ( PlayerParam* )&data[5] ) );
	}

	//	�ړ��l��M
	void	GameParam::MoveReceive( LPSTR data )
	{
		SetPlayerParam(
			*( ( int* )&data[1] ),
			*( ( PlayerParam* )&data[5] ) );
	}

	//	�`���b�g�f�[�^��M
	void	GameParam::ChatReceive( LPSTR data )
	{

	}

	//	�Q������M
	void	GameParam::SignUpReceive( LPSTR data )
	{
		NET_INFO*	info;
		info = ( NET_INFO* )data;
		SetPlayerInfo( info->id, info->name, info->type );
	}

	//	�ގ�����M
	void	GameParam::SignOutReceive( LPSTR data )
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