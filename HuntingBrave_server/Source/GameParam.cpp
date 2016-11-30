
#include	"iextreme.h"
#include	<thread>
#include	<map>
#include	"GameManager.h"
#include	"PlayerManager.h"
#include	"InputManager.h"
#include	"LevelManager.h"
#include	"PointManager.h"
#include	"GameParam.h"

//*****************************************************************************************************************************
//
//		�Q�[���f�[�^�Ǘ�
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

#define	INIT_LIFE		5
GameParam*	gameParam = nullptr;

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
			ZeroMemory( &lifeInfo[id], sizeof( LifeInfo ) );
			ZeroMemory( &matchingInfo[id], sizeof( MatchingInfo ) );
			lifeInfo[id].Initialize( INIT_LIFE );
		}

		//	�֐��|�C���^
		ReceiveFunction[RECEIVE_COMMAND::PLAYER_INFO] = &GameParam::ReceiveChara;
		ReceiveFunction[RECEIVE_COMMAND::ATTACK_INFO] = &GameParam::ReceiveAttackInfo;
		ReceiveFunction[RECEIVE_COMMAND::INPUT_INFO] = &GameParam::ReceiveInput;
		ReceiveFunction[RECEIVE_COMMAND::LEVEL_INFO] = &GameParam::ReceiveLevelInfo;
		ReceiveFunction[RECEIVE_COMMAND::HUNT_INFO] = &GameParam::ReceiveHuntInfo;
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

	//	�v���C���[������
	void	GameParam::InitializePlayer( int id )
	{
		lifeInfo[id].Initialize( INIT_LIFE );
		playerParam[id] = gameManager->GetInitInfo( id );
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
			//	�A�N�e�B�u�łȂ��v���C���[�͂Ƃ΂�
			if ( playerInfo[clientNum].active == false ) continue;

			//	�ړ���񑗐M
			SendCharaInfo( client, clientNum );
		}
		
		//	�Q�[����񑗐M
		SendGameInfo( client );

		//	�I�[�ʒm
		char end = -1;
		send( client, &end, 1 );
		return client;
	}

	//	��M
	int	GameParam::Receive( char scene )
	{
		char	data[256];
		int	size = sizeof( data );
		int	client = receive( data, &size );
		if( client == -1 ) return -1;
		
		//	�l�b�g�֘A
		switch( data[COMMAND] )
		{
		case COMMANDS::MATCHING:	//	�}�b�`���O
			client = ReceiveMatching( client, data );
			break;

		case COMMANDS::SIGN_UP:	//	�V�K�Q��
			client = ReceiveSignUp( client, data );
			break;

		case COMMANDS::SIGN_OUT:	//	�E��
			client = ReceiveSignOut( client, data );
			break;

		default:
			//	�Q�[����񏈗�
			client = ( this->*ReceiveFunction[data[COMMAND]] )( client, data );
		}

		return client;
	}

//----------------------------------------------------------------------------------------------
//	�V�[�����̎�M����
//----------------------------------------------------------------------------------------------

	//	�^�C�g����M����
	void	GameParam::TitleReceive( int client, const LPSTR& data )
	{

	}

	//	�}�b�`���O��M����
	void	GameParam::MatchingReceive( int client, const LPSTR& data )
	{

	}

	//	���C����M����
	void	GameParam::MainReceive( int client, const LPSTR& data )
	{

	}

	//	���U���g��M����
	void	GameParam::ResultReceive( int client, const LPSTR& data )
	{

	}

//----------------------------------------------------------------------------------------------
//	���M����
//----------------------------------------------------------------------------------------------

	//	�L������񑗐M
	void	GameParam::SendCharaInfo( int client, int player )
	{
		//	���ݒ�
		SendCharaData sendCharaData( player, 
			attackInfo[player].attackParam,
			playerParam[player].pos, 
			playerParam[player].angle,
			playerParam[player].motion,
			lifeInfo[player].life );

		//	���M
		send( client, ( LPSTR )&sendCharaData, sizeof( sendCharaData ) );
	}

	//	�Q�[����񑗐M
	void	GameParam::SendGameInfo( int client )
	{
		//	���ݒ�
		SendGameData	 sendGameData( gameManager->GetTimer()->GetRemainingTime() ); 

		//	���M
		send( client, ( LPSTR )&sendGameData, sizeof( sendGameData ) );
	}

	//	�}�b�`���O��񑗐M
	void	GameParam::SendMatchingInfo( int client, int player )
	{
		//	���ݒ�
		Matching	matching( player, matchingInfo[player].isComplete );

		//	���M
		send( client, ( char* )&matching, sizeof( matching ) );
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

		//	�t���[�����ݒ�
		playerParam[client].frame = receivePlayerData->frame;

		return	client;
	}

	//	�U������M
	int	GameParam::ReceiveAttackInfo( int client, const LPSTR& data )
	{
		ReceiveAttackData*	receiveAttackData = ( ReceiveAttackData* )data;
		
		//	�U�����ݒ�
		attackInfo[client].shapeType = receiveAttackData->shape;
		attackInfo[client].vec1 = receiveAttackData->vec1;
		attackInfo[client].vec2 = receiveAttackData->vec2;
		attackInfo[client].radius = receiveAttackData->radius;
		attackInfo[client].power = 1;
		return	-1;
	}

	//	���͏��擾
	int	GameParam::ReceiveInput( int client, const LPSTR& data )
	{
		ReceiveInputData*	receiveInputData = ( ReceiveInputData* )data;

		//	�{�^���̓��͏��ݒ�
		inputManager->SetInput( client, 
			receiveInputData->keyType, receiveInputData->keyState );

		return	-1;
	}

	//	�������擾
	int	GameParam::ReceiveHuntInfo( int client, const LPSTR& data )
	{
		ReceiveHuntData*	receiveHuntData = ( ReceiveHuntData* )data;

		//	��^�̎��_�������Z
		if ( receiveHuntData->enemyType == ENEMY_EXP::BIG_ENEMY )
		{
			pointManager->CalcPoint( client, 1000 );
			pointManager->SendPoint( client );
		}

		//	�o���l�v�Z
		levelManager->CalcExp( client, receiveHuntData->enemyType );
		levelManager->SendExp( client );
		return	-1;
	}

	//	���x�����擾
	int	GameParam::ReceiveLevelInfo( int client, const LPSTR& data )
	{
		ReceiveLevelData*	receiveLevelData = ( ReceiveLevelData* )data;
		levelManager->AddLevel( client, receiveLevelData->levelType );
		levelManager->SendLevel( client, receiveLevelData->levelType );

		return	-1;
	}

//----------------------------------------------------------------------------------------------
//	���O�C���֘A��M����
//----------------------------------------------------------------------------------------------

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
			AttackInfo::NO_ATTACK,
			initParam.pos, initParam.angle, initParam.motion, 
			lifeInfo[client].life );
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

	//	�}�b�`���O����M
	int	GameParam::ReceiveMatching( int client, const LPSTR& data )
	{
		Matching*	matching = ( Matching* )data;
		matchingInfo[client].isComplete = matching->isComplete;

		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	�A�N�e�B�u�łȂ��v���C���[�͂Ƃ΂�
			if ( playerInfo[p].active == false ) continue;
			SendMatchingInfo( client, p );
		}

		return	-1;
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
