
#include	"iextreme.h"
#include	"system/Framework.h"
#include	<thread>
#include	<vector>
#include	"GlobalFunction.h"
#include	"Random.h"
#include	"Camera.h"
#include	"GameData.h"
#include	"GameManager.h"
#include	"PlayerManager.h"
#include	"InputManager.h"
#include	"MagicManager.h"
#include	"LevelManager.h"
#include	"PointManager.h"
#include	"NetEnemyManager.h"
#include	"UIManager.h"
#include	"Sound.h"
#include	"sceneTitle.h"
#include	"sceneMatching.h"
#include	"sceneMain.h"
#include	"sceneResult.h"
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

//	���͏��
#define	MIN_INPUT_STICK		0.3f

namespace SE_TYPE
{
	enum 
	{
		ATTACK_SE,
		MAGIC_SE,
	};
}

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	GameParam::GameParam( void ) : playerName( nullptr ),
		myIndex( -1 ), inputAcceptance( true ), deathFlag( false )
	{
		//	�v���C���[�f�[�^������
		for ( int id = 0; id < PLAYER_MAX; id++ )
		{
			ZeroMemory( &playerInfo[id], sizeof( PlayerInfo ) );
			ZeroMemory( &playerParam[id], sizeof( PlayerParam ) );
			ZeroMemory( &playerParam[id], sizeof( PlayerStatus ) );
			ZeroMemory( &matchingInfo[id], sizeof( MatchingInfo ) );
		}

		//	�v���C���[��������
		playerName = new PlayerName();
		playerName->Initialize();
	}

	//	�f�X�g���N�^
	GameParam::~GameParam( void )
	{
		SafeDelete( playerName );
		CloseClient();
	}

	//	������
	bool	GameParam::Initialize( void )
	{
		//	�v���C���[�f�[�^������
		for ( int id = 0; id < PLAYER_MAX; id++ )
		{
			ZeroMemory( &playerInfo[id], sizeof( PlayerInfo ) );
			ZeroMemory( &playerParam[id], sizeof( PlayerParam ) );
			ZeroMemory( &matchingInfo[id], sizeof( MatchingInfo ) );
		}
		ZeroMemory( &playerStatus, sizeof( PlayerStatus ) );

		return	true;
	}
	
	//	�N���C�A���g������
	bool	GameParam::InitializeClient( char* addr, int nPort, int* name )
	{
		//	������
		Initialize();

		//	�N���C�A���g������
		InitializeUDP( nPort, addr );

		//	�^�C�v�Ɩ��O�̑��M
		char frontTitle = ( char )random->GetInt( 0, 19 );
		char backTitle = ( char )random->GetInt( 0, 9 );
		SignUp signUp( -1, name, frontTitle, backTitle );
		send( ( char* )&signUp, sizeof( signUp ) );

		//	�lID�擾
		if( receive( ( char* )&signUp, sizeof( signUp ) ) <= 0 ) return false;
		myIndex = signUp.id;

		//	�ԓ�
		Response	response( RESPONSE_COMMAND::SIGN_UP );
		send( ( LPSTR )&response, sizeof( response ) );

		//	�������W�擾
		ReceiveCharaData	receiveCharaData;
		if ( receive( ( LPSTR )&receiveCharaData, sizeof( receiveCharaData ) ) <= 0 )	return	false;
		SetPlayerParam( myIndex, 
			receiveCharaData.pos, receiveCharaData.angle, 
			receiveCharaData.motion, receiveCharaData.life );

		//	�����p�����[�^��M
		char	data[30];
		if ( receive( data, sizeof( data ) ) <= 0 )	return	false;
		levelManager->Receive( data );

		return true;
	}

	//	�E��
	void	GameParam::CloseClient( void )
	{
		//	�E�ރ��b�Z�[�W���M
		SignOut	signOut( myIndex );
		send( ( LPSTR )&signOut, sizeof( SignOut ) );
	}

//----------------------------------------------------------------------------------------------
//	�f�[�^����M
//----------------------------------------------------------------------------------------------

	//	�f�[�^���M
	void	GameParam::Send( void )
	{
		//	�L�����N�^�[��񑗐M
		SendPlayerInfo();

		//	���͏�񑗐M
		SendInputInfo();

		//	debug�p
		//if (KEY(KEY_TYPE::SELECT) == 3){
		//	char debug = COMMANDS::DEBUG;
		//	send(&debug, 1);
		//}
	}

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
			if( data[COMMAND] == RECEIVE_COMMAND::NO_COMMAND ) break;

			//	�擪�o�C�g�i�R�}���h�j�ɂ�鏈������
			switch( data[COMMAND] )
			{
			case RECEIVE_COMMAND::GAME_INFO:
				ReceiveGameInfo( data );
				break;

			case RECEIVE_COMMAND::POINT_INFO:
				pointManager->Receive( data );
				break;

			case RECEIVE_COMMAND::CHARA_INFO:
				ReceiveCharaInfo( data );
				break;

			case RECEIVE_COMMAND::MAGIC_INFO:
				magicManager->Receive( data );
				break;

			case RECEIVE_COMMAND::CLASS_CHANGE_INFO:
				playerManager->Receive( data );
				break;

			case RECEIVE_COMMAND::STATUS_INFO:
				levelManager->Receive( data );
				break;

			case RECEIVE_COMMAND::ENEMY_INFO:
				//netEnemyManager->Receive( data );
				break;

			case COMMANDS::MATCHING:
				ReceiveMatching( data );
				break;

			case COMMANDS::SIGN_UP:		//	�Q�����
				ReceiveSignUpInfo( data );
				break;

			case COMMANDS::SIGN_OUT:		//	�E�ޏ��
				ReceiveSignOutInfo( data );
				break;

			case COMMANDS::RESPONSE:
				ReceiveResponse( data );
				break;

			default:
				break;
			}
		}
	}

	//	�f�[�^���M
	void	GameParam::Update( void )
	{
		//	�S�f�[�^��M
		Receive();

		//	�L�����N�^�[��񑗐M
		SendPlayerInfo();

		//	���͏�񑗐M
		SendInputInfo();
	}

//----------------------------------------------------------------------------------------------
//	�f�[�^���M
//----------------------------------------------------------------------------------------------

	//	�v���C���[��񑗐M
	void	GameParam::SendPlayerInfo( void )
	{
		//	�X�e�B�b�N���͏��擾
		float axisX, axisY;
		axisX = axisY = 0.0f;
		inputManager->GetStickInputLeft( axisX, axisY );

		//	�t���[�����擾
		int frame = 0;
		if ( playerManager->GetPlayer( myIndex ) != nullptr )
		{
			frame =playerManager->GetPlayer( myIndex )->GetFrame();
		}

		//	�J���������ݒ�
		Vector3	vEye( mainView->GetTarget() - mainView->GetPos() );
		float	cameraAngle = atan2f( vEye.x, vEye.z );

		//	���M
		SendPlayerData	sendPlayerData( axisX, axisY, cameraAngle, frame );
		send( ( LPSTR )&sendPlayerData, sizeof( sendPlayerData ) );
	}

	//	�U����񑗐M
	void	GameParam::SendAttackParam( void )
	{
		//	���ݒ�
		AttackInfo	atkInfo = attackInfo[myIndex];
		SendAttackData	sendAttackData( atkInfo.shape, atkInfo.radius, atkInfo.vec1, atkInfo.vec2 );

		//	���M
		send( ( LPSTR )&sendAttackData, sizeof( sendAttackData ) );
	}

	//	�}�b�`���O��ԑ��M
	void	GameParam::SendMatching( void )
	{
		Matching	matching( myIndex, true );
		send( ( LPSTR )&matching, sizeof( matching ) );
	}

	//	���͏�񑗐M
	void	GameParam::SendInputInfo( void )
	{
		//	����{�^������
		CheckInputData( KEY_TYPE::A );

		//	���U���{�^������
		CheckInputData( KEY_TYPE::B );
		
		//	���@�U���{�^������
		CheckInputData( KEY_TYPE::X );

		//	Y�{�^������
		CheckInputData( KEY_TYPE::Y );

		//	���j���[�{�^������
		CheckInputData( KEY_TYPE::START );
	}

	//	�T�C���A�E�g���M
	void	GameParam::SendSignOut( void )
	{

	}

	//	�����R�}���h���M
	void	GameParam::SendResponseInfo( char com )
	{
		Response		response( com );
		send( ( LPSTR )&response, sizeof( response ) );
	}

//----------------------------------------------------------------------------------------------
//	�f�[�^��M
//----------------------------------------------------------------------------------------------

	//	�L��������M
	void	GameParam::ReceiveCharaInfo( const LPSTR& data )
	{
		//	��M���
		ReceiveCharaData*	receiveCharaData = ( ReceiveCharaData* )data;

		if ( receiveCharaData->id == myIndex )
		{
			if ( !deathFlag )
			{
				if ( receiveCharaData->motion == MOTION_NUM::FALL )
				{
					sound->MuteVolume( BGM::MAIN );
				}

				if ( receiveCharaData->motion == MOTION_NUM::DEAD )
				{
					deathFlag = true;
					sound->PlayBGM( BGM::DEAD );
				}
			}
			else
			{
				if ( receiveCharaData->motion != MOTION_NUM::DEAD )
				{
					sound->MuteVolume( BGM::DEAD );
					sound->ResetVolume( BGM::MAIN );
					deathFlag = false;
				}
			}
		}

		//	���ݒ�
		attackInfo[receiveCharaData->id].attackParam = 
			receiveCharaData->attackParam;

		SetPlayerParam( 
			receiveCharaData->id, 
			receiveCharaData->pos, 
			receiveCharaData->angle, 
			receiveCharaData->motion,
			receiveCharaData->life );
	}

	//	�Q�[������M
	void	GameParam::ReceiveGameInfo( const LPSTR& data )
	{
		ReceiveGameData*	receiveGameData = ( ReceiveGameData* )data;
		gameManager->SetTimer( receiveGameData->limitTimer );
	}

//----------------------------------------------------------------------------------------------
//	���O�C���֘A��M
//----------------------------------------------------------------------------------------------

	//	�}�b�`���O���
	void	GameParam::ReceiveMatching( const LPSTR& data )
	{
		Matching*	matching = ( Matching* )data;
		SetMatchingInfo( matching->id, matching->isComplete );
	}

	//	�T�C���A�b�v����M
	void	GameParam::ReceiveSignUpInfo( const LPSTR& data )
	{
		SignUp*	signUp = ( SignUp* )data;
		playerName->SetName( signUp->id, signUp->name );
		LPSTR name = playerName->GetName( signUp->id );
		SetPlayerInfo( signUp->id, name, signUp->frontTitle, signUp->backTitle );
		sound->PlaySE( SE::JOIN );
	}

	//	�T�C���A�E�g����M
	void	GameParam::ReceiveSignOutInfo( const LPSTR& data )
	{
		SignOut*	signOut = ( SignOut* )data;

		RemovePlayerInfo( signOut->id ); 
	}

	//	�ԓ�����M
	void	GameParam::ReceiveResponse( const LPSTR& data )
	{
		Response*	response = ( Response* )data;

		switch ( response->responseCom )
		{
		case	RESPONSE_COMMAND::SIGN_UP:
			break;

		case RESPONSE_COMMAND::CHANGE_SCENE:
			gameManager->SetChangeSceneFrag( true );
			break;

		case RESPONSE_COMMAND::GAME_START:
			break;

		case RESPONSE_COMMAND::KILL_INFO:
			{
				KillInfo*	killInfo = ( KillInfo* )data;
				uiManager->SetKillLog( killInfo->killer, killInfo->dead );
			}
			break;
			
		case RESPONSE_COMMAND::HIT_SE_TYPE:
			{
				switch ( data[2] )
				{
				case SE_TYPE::ATTACK_SE:
					sound->PlaySE( SE::ATTACK_HIT1 );
					break;

				case SE_TYPE::MAGIC_SE:
					sound->PlaySE( SE::MAGIC_HIT );
					break;
				}
			}
			break;
		}
	}

//----------------------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------------------

	//	�L�[���`�F�b�N
	void	GameParam::CheckInputData( char keyType )
	{
		char keyState = ( char )KEY( keyType );
		if ( keyState == KEY_STATE::STAY || 
			keyState == KEY_STATE::NO_INPUT )	return;

		//	���M
		SendInputData	sendInputData( keyType, keyState );
		send( ( LPSTR )&sendInputData, sizeof( sendInputData ) );
	}

//----------------------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------------------

	//	�v���C���[���ݒ�
	void	GameParam::SetPlayerInfo( int id, char* name, char frontTitle, char backTitle )
	{
		playerInfo[id].active = true;
		strcpy( playerInfo[id].name, name );
		playerInfo[id].frontTitle = frontTitle;
		playerInfo[id].backTitle = backTitle;
	}

	//	�}�b�`���O���ݒ�
	void	GameParam::SetMatchingInfo( int id, bool isComplete )
	{
		matchingInfo[id].isComplete = isComplete;
	}

	//	�v���C���[�E��
	void	GameParam::RemovePlayerInfo( int id )
	{
		playerInfo[id].active = false;
	}

	//	�v���C���[�p�����[�^�ݒ�
	void	GameParam::SetPlayerParam( int id, const Vector3& pos, float angle, int motion, int life )
	{
		playerParam[id].pos = pos;
		playerParam[id].angle = angle;
		playerParam[id].motion = motion;
		playerParam[id].life = life;
	}

	//	�v���C���[�p�����[�^�ݒ�
	void	GameParam::SetPlayerParam( int id, const PlayerParam& param )
	{
		playerParam[id].pos = param.pos;
		playerParam[id].angle  = param.angle;
	}
