
#include	"iextreme.h"
#include	"GameManager.h"
#include	"PlayerManager.h"
#include	"InputManager.h"
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
		for ( int clientNum = 0; clientNum < PLAYER_MAX; clientNum++ )
		{
			if( playerInfo[clientNum].active == false ) continue;

			//	�Q�[����񑗐M
			SendGameInfo( clientNum );

			//	�e�v���C���[�ɑS�v���C���[�̏��𑗐M
			for ( int player = 0; player < PLAYER_MAX; player++ )
			{
				//	�A�N�e�B�u�łȂ��v���C���[�͂Ƃ΂�
				if ( playerInfo[player].active == false ) continue;

				//	�ړ���񑗐M
				SendCharaInfo( clientNum, player );

				//	�_����񑗐M
				SendPointInfo( clientNum, player );
			}
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
		case RECEIVE_COMMAND::PLAYER_INFO:		//	�p�����[�^���
			ReceiveChara( client, data );
			break;

		case RECEIVE_COMMAND::INPUT_INFO:		//	���͏��
			ReceiveInput( client, data );
			break;

		case RECEIVE_COMMAND::POINT_INFO:		//	�_�����
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
	void	GameParam::SendCharaInfo( int client, int player )
	{
		//	���ݒ�
		SendCharaData sendCharaData( player, 
			playerParam[player].pos, 
			playerParam[player].angle,
			playerParam[player].motion );

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
		//	���Z�����O���ƃX�L�b�v
		if ( pointInfo[player].addPoint == 0 )	return;

		//	���ݒ�
		SendPointData	sendPointData( player, pointInfo[player].point );
		
		//	���M
		send( client, ( char* )&sendPointData, sizeof( sendPointData ) );

		//	���Z�_�����Z�b�g
		pointInfo[player].addPoint = 0;
	}

//----------------------------------------------------------------------------------------------
//	��M����
//----------------------------------------------------------------------------------------------

	//	�L��������M
	void	GameParam::ReceiveChara( int client, const LPSTR& data )
	{
		ReceivePlayerData* receivePlayerData = ( ReceivePlayerData* )data;
		
		//	�X�e�B�b�N�̓��͏��ݒ�
		inputManager->SetAxis( 
			receivePlayerData->id, 
			receivePlayerData->axisX, 
			receivePlayerData->axisY );
		
		//	�t���[�����ݒ�
		playerParam[receivePlayerData->id].frame = receivePlayerData->frame;
	}

	//	�_������M
	void	GameParam::ReceivePoint( int client, const LPSTR& data )
	{
		ReceivePointData*	receivePointData = ( ReceivePointData* )data;
		pointInfo[client].addPoint = receivePointData->addPoint;
	}

	//	���͏���M
	void	GameParam::ReceiveInput( int client, const LPSTR& data )
	{
		ReceiveInputData* receiveInputData = ( ReceiveInputData* )data;
		inputManager->SetInput( 
			receiveInputData->id, receiveInputData->buttonType, receiveInputData->inputType );
	}

	//	�T�C���A�b�v����M
	void	GameParam::ReceiveSignUp( int client, const LPSTR& data )
	{
		//	���O�ۑ�
		SignUp* signUp = ( SignUp* )data;
		SetPlayer( client, signUp->name );

		//	ID��ԐM
		signUp->id = client;
		send( client, ( char* )signUp, sizeof( SignUp ) );

		//	�������W�𑗐M
		PlayerParam	initParam = gameManager->GetInitInfo( client );
		SendCharaData	sendCharaData( client, initParam.pos, initParam.angle, initParam.motion );
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
	}

	//	�T�C���A�E�g����M
	void	GameParam::ReceiveSignOut( int client, const LPSTR& data )
	{
		//	�v���C���[���
		ReleasePlayer( client );

		//	�\�P�b�g�����
		CloseClient( client );

		SignOut	signOut( client );

		//	�S���Ƀf�[�^���M
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( playerInfo[p].active == false ) continue;
			send( p, ( char* )&signOut, sizeof( SignOut ) );
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

