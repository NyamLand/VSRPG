
#include	"iextreme.h"
#include	"GameData.h"
#include	"GameManager.h"
#include	"PlayerManager.h"
#include	"GameParam.h"

//***************************************************************
//
//	GameParam�N���X
//
//***************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

GameParam*	gameParam = nullptr;

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

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
	bool	GameParam::InitializeClient( char* addr, int nPort, char* name )
	{
		//	�N���C�A���g������
		InitializeUDP( nPort, addr );

		//	�^�C�v�Ɩ��O�̑��M
		NET_IN netIn( -1, name );
		send( ( char* )&netIn, sizeof( netIn ) );

		//	�lID�擾
		if( receive( ( char* )&netIn, sizeof( netIn ) ) <= 0 ) return false;
		myIndex = netIn.id;

		//	�������W�擾
		NET_CHARA	netChara;
		if ( receive( ( LPSTR )&netChara, sizeof( NET_CHARA ) ) <= 0 )	return	false;
		SetPlayerPos( myIndex, netChara.pos );

		return true;
	}

	//	�E��
	void	GameParam::CloseClient( void )
	{
		//	�E�ރ��b�Z�[�W���M
		NET_OUT	netOut( myIndex );
		send( ( LPSTR )&netOut, sizeof( NET_OUT ) );
	}

//----------------------------------------------------------------------------------------------
//	�f�[�^����M
//----------------------------------------------------------------------------------------------

	//	�f�[�^��M
	void	GameParam::Receive( void )
	{
		//	�S�f�[�^��M
		for(;;)
		{
			//	��M
			char	data[256];
			int size = receive( data, 256 );
			if( size <= 0 ) break;
		
			//	�f�[�^�I�[����
			if( data[COMMAND] == NO_COMMAND ) break;

			//	�擪�o�C�g�i�R�}���h�j�ɂ�鏈������
			switch( data[COMMAND] )
			{
				case COMMANDS::CHARA_INFO:	//	�ړ����
					ReceiveCharaInfo( data );
					break;

				case COMMANDS::CHARA_RECEIVEDATA:	//�K�v���S��
					ReceiveCharaDATA( data );
					break;

				case COMMANDS::CHAR_MOVE:	//	�ړ����
					ReceiveCharaMove( data );
					break;

				case COMMANDS::GAME_INFO:	//	�Q�[�����
					ReceiveGameInfo( data );
					break;

				case COMMANDS::SIGN_UP:		//	�Q�����
					ReceiveSignUp( data );
					break;

				case COMMANDS::SIGN_OUT:		//	�E�ޏ��
					ReceiveSignOut( data );
					break;
			}
		}
	}

	//	�f�[�^���M
	void	GameParam::Update( void )
	{
		//	�S�f�[�^��M
		Receive();

		//	�ړ��f�[�^���M
		//SendChraraInfo();

		//	�ړ��f�[�^���M
		SendMove();
	}

//----------------------------------------------------------------------------------------------
//	�f�[�^���M
//----------------------------------------------------------------------------------------------

	//	�ړ���񑗐M
	void	GameParam::SendChraraInfo( void )
	{
		NET_CHARA	netChara( myIndex, 
			playerManager->GetPlayer( myIndex )->GetPos(),
			playerManager->GetPlayer( myIndex )->GetAngle(),
			0 );

		send( ( LPSTR )&netChara, sizeof( NET_CHARA ) );
	}

	//	�ړ���񑗐M
	void	GameParam::SendMove( void )
	{
		//	�ړ��f�[�^���M
		float axisX = ( float )input[0]->Get( KEY_AXISX ) * 0.001f;
		float axisY = -( float )input[0]->Get( KEY_AXISY ) * 0.001f;
		NET_MOVE	netMove( myIndex, axisX, axisY );
		send( ( LPSTR )&netMove, sizeof( netMove ) );
	}

//----------------------------------------------------------------------------------------------
//	�f�[�^��M
//----------------------------------------------------------------------------------------------

	//	�L��������M
	void	GameParam::ReceiveCharaInfo( const LPSTR& data )
	{
		NET_CHARA*	netChara = ( NET_CHARA* )data;
		SetPlayerParam( netChara->id, netChara->pos, netChara->angle, netChara->motion );
	}

	//	�Q�[������M
	void	GameParam::ReceiveGameInfo( const LPSTR& data )
	{
		NET_GAME*	gameInfo = ( NET_GAME* )data;
		gameManager->SetTimer( gameInfo->limitTimer );
	}


	//*****************************************
	//		��ł����Ƃ���

	//�󂯎����S��
	void	GameParam::ReceiveCharaDATA(const LPSTR& data)
	{
		//NET_CHAR_RECEIVEDATA* d = (NET_CHAR_RECEIVEDATA*)data;
		////playerParam[client].axis = d->axis;
		//float	length = sqrtf(d->axisX * d->axisX + d->axisY * d->axisY) * 0.001f;

		//////	���͂�����Έړ�����
		//if (length >= 0.3f)
		//{
		//	Vector3 m = Vector3(sinf(d->angle), 0.0f, cosf(d->angle)) * 0.5;
		//	playerParam[client].pos += m;
		//}
	}


	//*****************************************


	//	�R���g���[���[����M
	void	GameParam::ReceiveControllerAxis(int client, const LPSTR& data)
	{
		NET_CONTROLLE_AXIS* d = (NET_CONTROLLE_AXIS*)data;
		//playerParam[client].axisX = d->axisX;
		//playerParam[client].axisY = d->axisY;
	}

	//	�L�����ړ��ʏ���M
	void	GameParam::ReceiveCharaMove( const LPSTR& data)
	{
		NET_CHARA_MOVE* netChara = (NET_CHARA_MOVE*)data;
		SetPlayerMove( netChara->id, netChara->move );
	}

	//	�T�C���A�b�v����M
	void	GameParam::ReceiveSignUp( const LPSTR& data )
	{
		NET_IN*	netIn = ( NET_IN* )data;
		SetPlayerInfo( netIn->id, netIn->name );
	}

	//	�T�C���A�E�g����M
	void	GameParam::ReceiveSignOut( const LPSTR& data )
	{
		RemovePlayerInfo( ( ( NET_OUT* )data )->id ); 
	}

//----------------------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------------------

	//	�v���C���[���ݒ�
	void	GameParam::SetPlayerInfo( int id, char* name )
	{
		playerInfo[id].active = true;
		strcpy( playerInfo[id].name, name );

		playerManager->SetPlayer( id );
	}

	//	�v���C���[�E��
	void	GameParam::RemovePlayerInfo( int id )
	{
		playerInfo[id].active = false;
	}

	//	�v���C���[�p�����[�^�ݒ�
	void	GameParam::SetPlayerPos( int id, const Vector3& pos )
	{
		playerParam[id].pos = pos;
		playerParam[id].angle  = 0.0f;
	}

	//	�v���C���[�p�����[�^�ݒ�
	void	GameParam::SetPlayerParam( int id, const Vector3& pos, float angle, int motion )
	{
		playerParam[id].pos = pos;
		playerParam[id].angle = angle;
		playerParam[id].motion = motion;
	}

	void	GameParam::SetPlayerMove(int id, const Vector3& move)
	{
		//playerParam[id].move = move;
		playerParam[id].angle = 0.0f;
	}

	//	�v���C���[�p�����[�^�ݒ�
	void	GameParam::SetPlayerParam( int id, const PlayerParam& param )
	{
		playerParam[id].pos = param.pos;
		//playerParam[id].move = param.move;
		playerParam[id].angle  = param.angle;
	}
