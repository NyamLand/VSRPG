
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameParam.h"

//***************************************************************
//
//	GameParam�N���X
//
//***************************************************************

//----------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------

	//	�R���X�g���N�^
	GameParam::GameParam( void )
	{
		//	�v���C���[�f�[�^������
		for ( int id = 0; id < PLAYER_MAX; id++ ) playerInfo[id].active = false;

		//	�`���b�g������
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
		info.com = RECEIVE_MODE::SIGN_UP;
		strcpy( info.name, name );

		//	�T�[�o�[�Ƀv���C���[���𑗐M
		SocketClient::Send( ( LPSTR )&info, sizeof( info ) );

		//	�l�h�c����Ƃ�
		int	size = SocketClient::Receive( ( LPSTR )&info, sizeof( info ) );
		if ( size <= 0 )	return	false;
		myIndex = info.id;

		return	true;
	}

	//	�E��
	void	GameParam::CloseClient( void )
	{
		char	com = RECEIVE_MODE::SIGN_OUT;
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
		switch ( data[0] )
		{
		case RECEIVE_MODE::MOVE:	//	�L�����f�[�^
			SetPlayerParam( 
				*( ( int* )&data[1] ),
				*( ( PlayerParam* )&data[5] ) );
			break;

		case RECEIVE_MODE::CHAT:	//	�`���b�g
			break;

		case RECEIVE_MODE::SIGN_UP:	//	�V�K�Q��
			{
				NET_INFO*	info;
				info = ( NET_INFO* )data;
				SetPlayerInfo( info->id, info->name, info->type );
			}
			break;

		case RECEIVE_MODE::SIGN_OUT:	//	�ގ�
			break;
		}
	}

	//	���M
	//void	GameParam::Send( PlayerParam playerParam )
	//{
	//	
	//}

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

