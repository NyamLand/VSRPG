
#include	"iextreme.h"
#include	"GameManager.h"
#include	"PlayerManager.h"
#include	"InputManager.h"
#include	<thread>
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
	int	GameParam::Send( int client )
	{
		if( client == -1 ) return -1;

		//	�S�f�[�^���M
		for ( int clientNum = 0; clientNum < PLAYER_MAX; clientNum++ )
		{
			//	
			if( playerInfo[clientNum].active == false ) continue;

			//	�A�N�e�B�u�łȂ��v���C���[�͂Ƃ΂�
			if ( playerInfo[clientNum].active == false ) continue;

			//	�ړ���񑗐M
			SendCharaInfo( client, clientNum );

			//	�_����񑗐M
			SendPointInfo( client, clientNum );	
		}
		
		//	�Q�[����񑗐M
		SendGameInfo( client );

		//	�I�[�ʒm
		char end = -1;
		send( client, &end, 1 );
		return client;
	}

	//	��M
	int	GameParam::Receive( void )
	{
		char	data[256];
		int		size = sizeof( data );
		int		client = receive( data, &size );
		if( client == -1 ) return -1;
		
		switch( data[COMMAND] )
		{
		case RECEIVE_COMMAND::PLAYER_INFO:		//	�p�����[�^���
			client = ReceiveChara( client, data );
			break;

		case RECEIVE_COMMAND::POINT_INFO:		//	�_�����
			client = ReceivePoint( client, data );
			break;

		case RECEIVE_COMMAND::ATTACK_INFO:		//	�U�����
			client = ReceiveAttackParam( client , data );
			break;

		case COMMANDS::SIGN_UP:	//	�V�K�Q��
			client = ReceiveSignUp( client, data );
			break;

		case COMMANDS::SIGN_OUT:	//	�E��
			client = ReceiveSignOut( client, data );
			break;
		}

		return client;
	}

//----------------------------------------------------------------------------------------------
//	���M����
//----------------------------------------------------------------------------------------------

	//	�L������񑗐M
	void	GameParam::SendCharaInfo( int client, int player )
	{
		//	���ݒ�
		SendCharaData sendCharaData( player, 
			playerParam[player].pos, 
			playerParam[player].angle,
			playerParam[player].motion,
			playerParam[player].life );

		//	���M
		send( client, ( LPSTR )&sendCharaData, sizeof( sendCharaData ) );
	}

	//	�Q�[����񑗐M
	void	GameParam::SendGameInfo( int client )
	{
		//	���ݒ�
		SendGameData	 sendGameData( gameManager->GetTimer()->GetLimitTime() ); 

		//	���M
		send( client, ( LPSTR )&sendGameData, sizeof( sendGameData ) );
	}

	//	�_����񑗐M
	void	GameParam::SendPointInfo( int client, int player )
	{
		//	���ݒ�
		SendPointData	sendPointData( player, pointInfo[player].point );
		
		//	���M
		send( client, ( char* )&sendPointData, sizeof( sendPointData ) );
	}

//----------------------------------------------------------------------------------------------
//	��M����
//----------------------------------------------------------------------------------------------

	//	�L��������M
	int	GameParam::ReceiveChara( int client, const LPSTR& data )
	{
		ReceivePlayerData* receivePlayerData = ( ReceivePlayerData* )data;
		
		//	�X�e�B�b�N�̓��͏��ݒ�
		inputManager->SetAxis( client, receivePlayerData->axisX,	receivePlayerData->axisY );

		//	�{�^���̓��͏��ݒ�
		inputManager->SetInput( client, receivePlayerData->button, receivePlayerData->inputType );
		
		//	�t���[�����ݒ�
		playerParam[client].frame = receivePlayerData->frame;

		return	client;
	}

	//	�_������M
	int	GameParam::ReceivePoint( int client, const LPSTR& data )
	{
		ReceivePointData*	receivePointData = ( ReceivePointData* )data;
		pointInfo[client].point += receivePointData->addPoint;
		
		//	�S�v���C���[�ɑ��M
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			SendPointInfo( client, p );
		}

		return	-1;
	}

	//	�U������M
	int	GameParam::ReceiveAttackParam( int client, const LPSTR& data )
	{
		ReceiveAttackData*	receiveAttackData = ( ReceiveAttackData* )data;
		
		attackInfo[client].attackParam = ( AttackInfo::ATTACK_PARAM )receiveAttackData->attackParam;
		attackInfo[client].collisionShape.SetCapsule( 
			Capsule( 	receiveAttackData->attackPos1, 
							receiveAttackData->attackPos2,
							receiveAttackData->radius ) );
		attackInfo[client].collisionShape.shapeType = SHAPE_TYPE::CAPSULE;
		attackInfo[client].power = 1;
		return	-1;
	}

	//	�T�C���A�b�v����M
	int	GameParam::ReceiveSignUp( int client, const LPSTR& data )
	{
		//	���O�ۑ�
		SignUp* signUp = ( SignUp* )data;
		SetPlayer( client, signUp->name );

		//	ID��ԐM
		signUp->id = client;
		send( client, ( char* )signUp, sizeof( SignUp ) );

		//	�������W�𑗐M
		PlayerParam	initParam = gameManager->GetInitInfo( client );
		SendCharaData	sendCharaData( client, 
			initParam.pos, initParam.angle, initParam.motion, 
			initParam.life );
		send( client, ( LPSTR )&sendCharaData, sizeof( sendCharaData ) );

		//	�S���Ƀf�[�^���M
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( playerInfo[p].active == false ) continue;
			send( p, ( char* )signUp, sizeof( SignUp ) );
		}

		//	�S�f�[�^���M
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( playerInfo[p].active == false ) continue;
			signUp->id = p;
			strcpy( signUp->name, playerInfo[p].name );
			send( client, ( char* )signUp, sizeof( SignUp ) );
		}
		printf( "%dP %s���񂪎Q�����܂����B\n", client + 1, signUp->name );

		return	client;
	}

	//	�T�C���A�E�g����M
	int	GameParam::ReceiveSignOut( int client, const LPSTR& data )
	{
		//	�v���C���[���
		ReleasePlayer( client );

		SignOut	signOut( client );

		//	�\�P�b�g�����
		CloseClient( client );

		//	�S���Ƀf�[�^���M
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( playerInfo[p].active == false ) continue;
			send( p, ( char* )&signOut, sizeof( SignOut ) );
		}
		printf( "%dP %s���񂪒E�ނ��܂����B\n", client + 1, playerInfo[client].name );

		return	client;
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

