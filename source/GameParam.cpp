
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"PlayerManager.h"
#include	"UIParam.h"

//***************************************************************
//
//	UIParam�N���X
//
//***************************************************************

//----------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------

UIParam*	UIParam = nullptr;

//----------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------

	//	�R���X�g���N�^
	UIParam::UIParam( void )
	{
		//	�v���C���[�f�[�^������
		for ( int id = 0; id < PLAYER_MAX; id++ ) playerInfo[id].active = false;

		//	�`���b�g������
	}

	//	�f�X�g���N�^
	UIParam::~UIParam( void )
	{
		CloseClient();
	}

	//	�N���C�A���g������
	bool	UIParam::InitializeClient( LPSTR addr, int nPort, LPSTR name, int type )
	{
		//	�N���C�A���g������
		InitializeUDP( nPort, addr );

		//	�^�C�v�Ɩ��O�̑��M
		NET_INFO	info;
		info.com = RECEIVE_MODE::SIGN_UP;
		info.type = type;
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
	void	UIParam::CloseClient( void )
	{
		char	com = RECEIVE_MODE::SIGN_OUT;
		SocketClient::Send( &com, sizeof( char ) );
	}

//----------------------------------------------------------------------------------
//	�X�V
//----------------------------------------------------------------------------------

	//	�X�V
	void	UIParam::Update( void )
	{
		//	�S�f�[�^��M
		Receive();

		//	�ʒu�f�[�^���M
		NET_POS	netData;

		netData.com = POS;
		netData.pos = playerManager->GetPlayer()->GetPos();
		SocketClient::Send( ( char* )&netData, sizeof( netData ) );
		//int a = 0;
	}

//----------------------------------------------------------------------------------
//	�f�[�^����M
//----------------------------------------------------------------------------------

	//	��M
	void	UIParam::Receive( void )
	{
		char data[256];

		//	�f�[�^����M
		int	size = SocketClient::Receive( data, 256 );
		if ( size <= 0 )
		{
			return;
		}
		if ( data[0] == -1 )
		{
			return;
		}
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
	//void	UIParam::Send( PlayerParam playerParam )
	//{
	//	
	//}

//----------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------

	//	�v���C���[���ݒ�
	void	UIParam::SetPlayerInfo( int id, LPSTR name, int type )
	{
		playerInfo[id].active = true;
		playerInfo[id].type = type;
		strcpy( playerInfo[id].name, name );
	}

	//	�v���C���[�p�����[�^�ݒ�
	void	UIParam::SetPlayerParam( int id, Vector3& pos, float angle, int motion )
	{
		playerParam[id].pos = pos;
		playerParam[id].angle = angle;
		playerParam[id].motion = motion;
	}

	//	�v���C���[�p�����[�^�ݒ�
	void	UIParam::SetPlayerParam( int id, PlayerParam& param )
	{
		playerParam[id].pos = param.pos;
		playerParam[id].angle = param.angle;
		playerParam[id].motion = param.motion;
		printf("x = %f y = %f z = %f\n", playerParam[id].pos.x, playerParam[id].pos.y, playerParam[id].pos.z );
	}

//----------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------

