
#include	"iextreme.h"
#include	<thread>
#include	<map>
#include	<vector>
#include	"GameManager.h"
#include	"PlayerManager.h"
#include	"InputManager.h"
#include	"LevelManager.h"
#include	"ItemManager.h"
#include	"PointManager.h"
#include	"EnemyManager.h"
#include	"Collision.h"
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
#define	TIME_MAX	1.0f//( 9.0f * MINUTE + 30.0f )
GameParam*	gameParam = nullptr;

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	GameParam::GameParam( void ) : playerName( nullptr )
	{
		playerName = new PlayerName();
		InitializeGame();
	}

	//	�f�X�g���N�^
	GameParam::~GameParam( void )
	{
		if ( playerName != nullptr )
		{
			delete	playerName;
			playerName = nullptr;
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

	//	�v���C���[������
	void	GameParam::InitializePlayer( int id )
	{
		lifeInfo[id].life = lifeInfo[id].maxLife;
		playerParam[id].pos = gameManager->GetInitInfo( id ).pos;
		//playerParam[id] = gameManager->GetInitInfo( id );
	}

	//	�Q�[��������
	void	GameParam::InitializeGame( void )
	{
		for ( int id = 0; id < PLAYER_MAX; id++ )
		{
			ZeroMemory( &playerInfo[id], sizeof( PlayerInfo ) );
			ZeroMemory( &playerParam[id], sizeof( PlayerParam ) );
			ZeroMemory( &playerStatus[id], sizeof( PlayerStatus ) );
			ZeroMemory( &lifeInfo[id], sizeof( LifeInfo ) );
			int initLife = gameManager->GetInitStatus( UPGRADE_DATA::HP );
			lifeInfo[id].Initialize( initLife );
			gameManager->InitializeStatus( playerStatus[id] );
		}

		itemManager->Initialize();
	}

	//	�Q�[�����Z�b�g
	void	GameParam::ReleaseGame( void )
	{
		playerName->Initialize();
		itemManager->Release();
		playerManager->Release();
		gameManager->Release();
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

		//	�L�[��񃊃Z�b�g
		inputManager->ResetInput( client );

		return client;
	}

	//	��M
	int	GameParam::Receive( char scene )
	{
		//	�f�[�^��M
		char	data[256];
		int	size = sizeof( data );
		int	client = receive( data, &size );
		if( client == -1 ) return -1;

		//	�l�b�g�֘A
		switch ( data[COMMAND] )
		{
		case RECEIVE_COMMAND::PLAYER_INFO:
			client = ReceiveChara( client, data );
			break;

		case RECEIVE_COMMAND::ATTACK_INFO:
			client = ReceiveAttackInfo( client, data );
			break;

		case RECEIVE_COMMAND::INPUT_INFO:
			client = ReceiveInput( client, data );
			break;

		case RECEIVE_COMMAND::LEVEL_INFO:
			client = ReceiveLevelInfo( client, data );
			break;

		case RECEIVE_COMMAND::ENEMY_INFO:
			client = ReceiveEnemyInfo( client, data );
			break;

		case RECEIVE_COMMAND::ITEM_INFO:
			client = ReceiveItemInfo( client, data );
			break;

		case COMMANDS::MATCHING:
			client = ReceiveMatching( client, data );
			break;

		case COMMANDS::SIGN_UP:
			client = ReceiveSignUp( client, data );
			break;

		case COMMANDS::SIGN_OUT:	//	�E��
			client = ReceiveSignOut( client, data );
			break;

		case COMMANDS::RESPONSE:	//	�T�C���A�b�v����
			client = ReceiveResponse( client, data );
			break;

		case COMMANDS::DEBUG:
		{
				collision->SendHitSE( 0 );
				//	���C�t�v�Z
				int damage = 50;
				if ( damage <= 0 )	damage = 5;
				bool isAlive = gameParam->GetLifeInfo( client ).CulcLife(-damage);
				if ( isAlive ) gameParam->GetPlayerParam( client ).effParam = 0.0f;
				else
				{
					//	�v���C���[�����S������
					playerManager->GetPlayer(0)->SetDeath();
				}
		}
			break;

		default:	//	�Q�[����񏈗�
			client = -1;
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
		SendCharaData sendCharaData(player,
			attackInfo[player].attackParam,
			playerParam[player].pos,
			playerParam[player].angle,
			playerParam[player].effParam,
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
		Matching	matching( client, gameManager->GetMatchingInfo( client ).isComplete );

		//	���M
		send( player, ( char* )&matching, sizeof( matching ) );
	}

	//	�L����񑗐M
	void	GameParam::SendKillInfo( int killer, int dead )
	{
		struct
		{
			char com;
			char responseCom;
			int killer;
			int dead;
		} killInfo;
		killInfo.com = COMMANDS::RESPONSE;
		killInfo.responseCom = RESPONSE_COMMAND::KILL_INFO;
		killInfo.killer = killer;
		killInfo.dead = dead;

		//	���M
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			send( i, ( char* )&killInfo, sizeof( killInfo ) );
		}
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

		//	�J�����A���O���擾
		playerParam[client].cameraAngle = receivePlayerData->cameraAngle;
		
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
		return	-1;
	}

	//	���͏��擾
	int	GameParam::ReceiveInput( int client, const LPSTR& data )
	{
		ReceiveInputData*	receiveInputData = ( ReceiveInputData* )data;

		//	�{�^���̓��͏��ݒ�
		inputManager->SetInput( client, receiveInputData->key, receiveInputData->keyState );
		return	-1;
	}

	//	�������擾
	int	GameParam::ReceiveEnemyInfo( int client, const LPSTR& data )
	{
		switch ( data[1] )
		{
		case RECEIVE_ENEMY_COMMAND::BIG_ENEMY_HUNT:
			//	�_���v�Z
			pointManager->ReceiveHuntInfo( client, data );

			//	�o���l�v�Z
			levelManager->ReceiveHuntInfo( client, data );
			break;

		case RECEIVE_ENEMY_COMMAND::SMALL_ENEMY_HUNT:
			//	�_���v�Z
			pointManager->ReceiveHuntInfo( client, data );

			//	�o���l�v�Z
			levelManager->ReceiveHuntInfo( client, data );
			break;

		case RECEIVE_ENEMY_COMMAND::PLAYER_HIT:
			{
				//	���C�t�v�Z
				int damage = 5;
				bool isAlive = gameParam->GetLifeInfo( client ).CulcLife( -damage );
				if (isAlive) gameParam->GetPlayerParam( client ).effParam = 0.0f;
				else
				{
					//	�v���C���[�����S������
					playerManager->GetPlayer( client )->SetDeath();
				}
			}
			break;

		case RECEIVE_ENEMY_COMMAND::CLIENT_OK:
			enemyManager->Receive( client, data );
			break;

		default:
			break;
		}

		return	-1;
	}

	//	���x�����擾
	int	GameParam::ReceiveLevelInfo( int client, const LPSTR& data )
	{
		ReceiveLevelData*	receiveLevelData = ( ReceiveLevelData* )data;
		levelManager->AddLevel( client, receiveLevelData->levelType );
		levelManager->SendLevel( client, receiveLevelData->levelType );
		levelManager->SendAllStatus( client );

		return	-1;
	}

	//	�A�C�e�����擾
	int	GameParam::ReceiveItemInfo( int client, const LPSTR& data )
	{
		itemManager->ReceiveData( client, data );
		return	-1;
	}

//----------------------------------------------------------------------------------------------
//	���O�C���֘A��M����
//----------------------------------------------------------------------------------------------

	//	�T�C���A�b�v����M
	int	GameParam::ReceiveSignUp( int client, const LPSTR& data )
	{
		if ( gameManager->GetGameState() )
		{
			return	-1;
		}

		//	���O�ۑ�
		SignUp* signUp = ( SignUp* )data;
		playerName->SetName( client, signUp->name );
		char*	name = playerName->GetName( client );
		strcpy( playerInfo[client].name, name );

		//	�̍��ۑ�
		playerInfo[client].frontTitle = signUp->frontTitle;
		playerInfo[client].backTitle = signUp->backTitle;

		//	ID��ԐM
		signUp->id = client;
		send( client, ( char* )signUp, sizeof( SignUp ) );

		return	-1;
	}

	//	�T�C���A�E�g����M
	int	GameParam::ReceiveSignOut( int client, const LPSTR& data )
	{
		//	�v���C���[���
		ZeroMemory( &playerInfo[client], sizeof( PlayerInfo ) );
		
		//	�\�P�b�g�����
		CloseClient( client );

		//	���ݒ�
		SignOut	signOut( client );

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
		gameManager->SetMatchingInfo( client, matching->isComplete );

		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	�A�N�e�B�u�łȂ��v���C���[�͂Ƃ΂�
			if ( playerInfo[p].active == false ) continue;
			SendMatchingInfo( /*��M�����v���C���[���*/client, /*���M���������̃v���C���[*/p );
		}

		return	-1;
	}

	//	�ԓ�����f
	int	GameParam::ReceiveResponse( int client, const LPSTR& data )
	{
		Response*	response = ( Response* )data;

		switch ( response->responseCom )
		{
		case RESPONSE_COMMAND::SIGN_UP:
			client = SignUpResponse( client );
			break;

		case RESPONSE_COMMAND::GAME_START:
			client = GameStartResponse( client );
			break;
		}

		return	client;
	}

//----------------------------------------------------------------------------------------------
//	�����R�}���h���̏���
//----------------------------------------------------------------------------------------------

	//	�T�C���A�b�v��������M
	int	GameParam::SignUpResponse( int client )
	{
		//	�ԓ����Ԃ��Ă����̂ŃA�N�e�B�u�ɂ���
		SetPlayer( client, playerInfo[client].name );

		//	������񑗐M
		{
			//	�������擾
			PlayerParam		initParam = gameManager->GetInitInfo( client );

			//	�������ݒ�
			SendCharaData	sendCharaData( client,
				AttackInfo::NO_ATTACK,
				initParam.pos, initParam.angle, initParam.effParam, initParam.motion,
				lifeInfo[client].life );

			//	������񑗐M
			send( client, ( LPSTR )&sendCharaData, sizeof( sendCharaData ) );
		}

		//	�����p�����[�^���M
		levelManager->SendAllStatus( client );

		//	�T�C���A�b�v����ݒ�
		SignUp		signUp( client, 
			playerName->GetNameIndex( client ),
			playerInfo[client].frontTitle, 
			playerInfo[client].backTitle );

		//	�S���Ƀf�[�^���M
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( playerInfo[p].active == false ) continue;
			send( p, ( char* )&signUp, sizeof( signUp ) );
		}

		//	�S�f�[�^���M
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( playerInfo[p].active == false ) continue;
			signUp.id = p;
			signUp.frontTitle = playerInfo[p].frontTitle;
			signUp.backTitle = playerInfo[p].backTitle;

			//	���O�C���f�b�N�X�R�s�[
			for ( int i = 0; i < 4; i++ )
			{
				signUp.name[i] = playerName->GetNameIndex( p )[i];
			}
			send( client, ( char* )&signUp, sizeof( signUp ) );
		}
		printf( "%dP %s���񂪎Q�����܂����B\n", client + 1, signUp.name );

		return	client;
	}

	//	�Q�[���J�n��������M
	int	GameParam::GameStartResponse( int client )
	{
		gameManager->GetMatchingInfo( client ).isComplete = true;

		//	�S�����������ŃX�^�[�g
		if ( gameManager->PlayerCheck() )
		{
			gameManager->MatchingInfoInitialize();
			gameManager->SetGameState( true );
			gameManager->GetTimer()->Start( TIME_MAX * 3 );
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
	}

	//	�v���C���[�p�����[�^�ݒ�
	void	GameParam::SetPlayerParam( int id, const Vector3& pos, float angle, float effParam, int motion )
	{
		playerParam[id].pos    = pos;
		playerParam[id].angle  = angle;
		playerParam[id].motion = motion;
		playerParam[id].effParam = effParam;
	}
