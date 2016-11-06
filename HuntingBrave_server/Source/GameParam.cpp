
#include	"iextreme.h"
#include	"GameManager.h"
#include	"PlayerManager.h"
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
			ZeroMemory( &playerInfo[id], sizeof( PlayerInfo ) );
			ZeroMemory( &playerParam[id], sizeof( PlayerParam ) );
			ZeroMemory( &pointInfo[id], sizeof( PointInfo ) );
		}
	}

	//	�T�[�o�[������
	bool GameParam::InitializeServer( void )
	{
		//	WinSock������
		WSADATA	wsaData;
		WSAStartup( MAKEWORD( 1, 1 ), &wsaData );
		bool successInit = Initialize( 7000 );

		if ( successInit )	printf( "�T�[�o�[����������\n" );
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

			//	�Q�[����񑗐M
			SendGameInfo( p );

			//	�ړ���񑗐M
			SendCharaInfo( p );

			//	�_����񑗐M
			SendPointInfo( p );
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
			ReceiveChara( client, data );
			break;

		case COMMANDS::CHARA_RECEIVEDATA:	//�K�v���S��
			ReceiveCharaDATA( client, data );
			break;

		case COMMANDS::CONTROLLE_AXIS:	//�R���g���[���[�����
			ReceiveControllerAxis( client, data );
			break;

		case COMMANDS::CHAR_MOVE:		//	�ړ����
			ReceiveCharaMove( client, data );
			break;

		case COMMANDS::POINT_INFO:		//	�_�����
			ReceivePoint( client, data );
			break;

		case COMMANDS::SIGN_UP:	//	�V�K�Q��
			ReceiveSignUp( client, data );
			break;

		case COMMANDS::SIGN_OUT:	//	�E��
			ReceiveSignOut( client, data );
			break;
		}
		return client;
	}

//----------------------------------------------------------------------------------------------
//	���M����
//----------------------------------------------------------------------------------------------

	//	�L������񑗐M
	void	GameParam::SendCharaInfo( int client )
	{
		//	���ݒ�
		NET_CHARA netChara( client, 
			playerParam[client].pos, 
			playerParam[client].angle,
			playerParam[client].motion );

		//	���M
		send( client, ( LPSTR )&netChara, sizeof( NET_CHARA ) );
	}

	//	�Q�[����񑗐M
	void	GameParam::SendGameInfo( int client )
	{
		//	���ݒ�
		NET_GAME	 netGame( gameManager->GetTimer()->GetLimitTime() ); 

		//	���M
		send( client, ( LPSTR )&netGame, sizeof( NET_GAME ) );
	}

	//	�_����񑗐M
	void	GameParam::SendPointInfo( int client )
	{
		//	���Z�����O���ƃX�L�b�v
		if ( pointInfo[client].addPoint == 0 )	return;

		//	���ݒ�
		NET_POINT	netPoint;
		netPoint.id = client;
		netPoint.point = pointInfo[client].point;
		pointInfo[client].addPoint = 0;

		//	���M
		send( client, ( LPSTR )&netPoint, sizeof( NET_POINT ) );
	}

//----------------------------------------------------------------------------------------------
//	��M����
//----------------------------------------------------------------------------------------------

	//	�L��������M
	void	GameParam::ReceiveChara( int client, const LPSTR& data )
	{
		NET_MOVE* netMove = ( NET_MOVE* )data;
		playerParam[client].moveX = netMove->axisX;
		playerParam[client].moveZ = netMove->axisY;
	}

	//	�_������M
	void	GameParam::ReceivePoint( int client, const LPSTR& data )
	{
		NET_POINT*	netPoint = ( NET_POINT* )data;
		pointInfo[client].addPoint = netPoint->point;
	}



	//*****************************************
	//		��ł����Ƃ���

	//�󂯎����S��
	void	GameParam::ReceiveCharaDATA( int client, const LPSTR& data )
	{
		NET_CHAR_RECEIVEDATA* d = (NET_CHAR_RECEIVEDATA*)data;
		//playerParam[client].axis = d->axis;
		float	length = sqrtf(d->axisX * d->axisX + d->axisY * d->axisY) * 0.001f;

		////	���͂�����Έړ�����
		if (length >= 0.3f)
		{
			Vector3 m = Vector3(sinf(d->angle), 0.0f, cosf(d->angle)) * 0.3f;

			playerParam[client].pos += m;
		}
	}


	//*****************************************

	//	�R���g���[���[����M
	void	GameParam::ReceiveControllerAxis(int client, const LPSTR& data)
	{
		NET_CONTROLLE_AXIS* d = (NET_CONTROLLE_AXIS*)data;
		//playerParam[client].axis = d->axis;
		float	length = sqrtf( d->axisX * d->axisX + d->axisY * d->axisY ) * 0.001f;

		//	���͂�����Έړ�����
		if ( length >= 0.3f )	
		{
			Vector3 m = Vector3(sinf(0), 0.0f, cosf(0)) * 0.3f;
			playerParam[client].pos += m;
		}
	}



	//	�L�����ړ��ʏ���M
	void	GameParam::ReceiveCharaMove(int client, const LPSTR& data)
	{
		NET_MOVE* netMove = ( NET_MOVE* )data;
		playerParam[client].moveX = netMove->axisX;
		playerParam[client].moveZ = netMove->axisY;
	}

	//	�T�C���A�b�v����M
	void	GameParam::ReceiveSignUp( int client, const LPSTR& data )
	{
		//	���O�ۑ�
		NET_IN* netIn = ( NET_IN* )data;
		SetPlayer( client, netIn->name );

		//	ID��ԐM
		netIn->id = client;
		send( client, ( char* )netIn, sizeof( NET_IN ) );

		//	�������W�𑗐M
		PlayerParam	initParam = gameManager->GetInitInfo( client );
		NET_CHARA	netChara( client, initParam.pos, initParam.angle, initParam.motion );
		send( client, ( LPSTR )&netChara, sizeof( netChara ) );

		//	�S���Ƀf�[�^���M
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( playerInfo[p].active == false ) continue;
			send( p, ( char* )netIn, sizeof( NET_IN ) );
		}

		//	�S�f�[�^���M
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( playerInfo[p].active == false ) continue;
			netIn->id = p;
			strcpy( netIn->name, playerInfo[p].name );
			send( client, ( char* )netIn, sizeof( NET_IN ) );
		}
		printf("%dP %s���񂪎Q�����܂����B\n", client + 1, netIn->name);
	}

	//	�T�C���A�E�g����M
	void	GameParam::ReceiveSignOut( int client, const LPSTR& data )
	{
		//	�v���C���[���
		ReleasePlayer( client );

		//	�\�P�b�g�����
		CloseClient( client );

		NET_OUT	netOut( client );

		//	�S���Ƀf�[�^���M
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( playerInfo[p].active == false ) continue;
			send( p, ( char* )&netOut, sizeof( NET_OUT ) );
		}
		printf( "%dP %s���񂪒E�ނ��܂����B\n", client + 1, playerInfo[client].name );
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
		playerParam[id] = gameManager->GetInitInfo( id );
		playerManager->SetPlayer( id );
	}

	//	�v���C���[���
	void	GameParam::ReleasePlayer( int id )
	{
		ZeroMemory( &playerInfo[id], sizeof( PlayerInfo ) );
		//playerManager->ReleasePlayer( id );
	}

	//	�v���C���[�p�����[�^�ݒ�
	void	GameParam::SetPlayerParam( int id, const Vector3& pos, float angle, int motion )
	{
		playerParam[id].pos    = pos;
		playerParam[id].angle  = angle;
		playerParam[id].motion = motion;
	}

	//	�v���C���[�p�����[�^�ݒ�
	void	GameParam::SetPlayerParam( int id, const PlayerParam& param )
	{
		playerParam[id].pos    = param.pos;
		playerParam[id].angle  = param.angle;
	}

	//	�_�����ݒ�
	void	GameParam::SetPointInfo( int id, const PointInfo& pointInfo )
	{
		this->pointInfo[id] = pointInfo;
	}

