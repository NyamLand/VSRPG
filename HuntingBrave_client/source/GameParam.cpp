
#include	"iextreme.h"
#include	"system/Framework.h"
#include	<thread>
#include	"Camera.h"
#include	"GameData.h"
#include	"GameManager.h"
#include	"PlayerManager.h"
#include	"InputManager.h"
#include	"MagicManager.h"
#include	"LevelManager.h"
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

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	GameParam::GameParam( void ) : myIndex( -1 ), inputAcceptance( true )
	{
		//	�v���C���[�f�[�^������
		for ( int id = 0; id < PLAYER_MAX; id++ )
		{
			ZeroMemory( &playerInfo[id], sizeof( PlayerInfo ) );
			ZeroMemory( &playerParam[id], sizeof( PlayerParam ) );
			ZeroMemory( &playerParam[id], sizeof( PlayerStatus ) );
			ZeroMemory( &pointInfo[id], sizeof( PointInfo ) );
			ZeroMemory( &matchingInfo[id], sizeof( MatchingInfo ) );
		}
	}

	//	�f�X�g���N�^
	GameParam::~GameParam( void )
	{
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
			ZeroMemory( &pointInfo[id], sizeof( PointInfo ) );
			ZeroMemory( &matchingInfo[id], sizeof( MatchingInfo ) );
		}

		ZeroMemory( &playerStatus, sizeof( PlayerStatus ) );

		return	true;
	}
	
	//	�N���C�A���g������
	bool	GameParam::InitializeClient( char* addr, int nPort, char* name )
	{
		//	������
		Initialize();

		//	�N���C�A���g������
		InitializeUDP( nPort, addr );

		//	�^�C�v�Ɩ��O�̑��M
		SignUp signUp( -1, name );
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
		ReceiveAllStatusData	receiveAllStatus;
		if ( receive( ( LPSTR )&receiveAllStatus, sizeof( receiveAllStatus ) ) <= 0 )	return	false;
		levelManager->CulcAllStatus( receiveAllStatus );
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
				ReceivePointInfo( data );
				break;

			case RECEIVE_COMMAND::CHARA_INFO:
				ReceiveCharaInfo( data );
				break;

			case RECEIVE_COMMAND::MAGIC_INFO:
				ReceiveMagicInfo( data );
				break;

			case RECEIVE_COMMAND::MAGIC_APPEND:
				ReceiveMagicAppendInfo( data );
				break;

			case RECEIVE_COMMAND::MAGIC_ERASE:
				ReceiveMagicEraseInfo( data );
				break;

			case RECEIVE_COMMAND::LEVEL_INFO:
				ReceiveLevelInfo( data );
				break;

			case RECEIVE_COMMAND::EXP_INFO:
				ReceiveExpInfo( data );
				break;

			case RECEIVE_COMMAND::CLASS_CHANGE_INFO:
				ReceiveClassChangeInfo( data );
				break;

			case RECEIVE_COMMAND::STATUS_INFO:
				ReceiveStatusInfo( data );
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
		float axisX, axisY, axisRX, axisRY;
		axisX = axisY = axisRX, axisRY = 0.0f;
		inputManager->GetStickInputLeft( axisX, axisY );
		inputManager->GetStickInputLeft( axisRX, axisRY );

		//	�t���[�����擾
		int frame = playerManager->GetPlayer( myIndex )->GetFrame();

		//	���M
		SendPlayerData	sendPlayerData( axisX, axisY, axisRX, axisRY, frame );
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

	//	������񑗐M
	void	GameParam::SendHuntInfo( char enemyType )
	{
		SendHuntData	sendHuntData( enemyType );
		send( ( LPSTR )&sendHuntData, sizeof( sendHuntData ) );
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

	//	�_������M
	void	GameParam::ReceivePointInfo( const LPSTR& data )
	{
		ReceivePointData*	receivePointData = ( ReceivePointData* )data;
		SetPointInfo( receivePointData->id, receivePointData->point );
	}
	
	//	���@����M
	void	GameParam::ReceiveMagicInfo( const LPSTR& data )
	{
		ReceiveMagicData	* receiveMagicData = ( ReceiveMagicData* )data;
		magicManager->SetPos( receiveMagicData->index, receiveMagicData->pos );
	}

	//	���@�ǉ�����M
	void	GameParam::ReceiveMagicAppendInfo( const LPSTR& data )
	{
		ReceiveMagicAppend*	receiveMagicAppend = ( ReceiveMagicAppend* )data;
		magicManager->Append( 
			receiveMagicAppend->id,
			receiveMagicAppend->pos, 
			receiveMagicAppend->angle );
	}

	//	���@��������M
	void	GameParam::ReceiveMagicEraseInfo( const LPSTR& data )
	{
		ReceiveMagicErase*	receiveMagicErase = ( ReceiveMagicErase* )data;
		magicManager->Erase( receiveMagicErase->index );
	}

	//	���x������M
	void	GameParam::ReceiveLevelInfo( const LPSTR& data )
	{
		ReceiveLevelData* receiveLevelData = ( ReceiveLevelData* )data;
		levelManager->SetLevelInfo( receiveLevelData->levelType, receiveLevelData->level );
	}

	//	�o���l����M
	void	GameParam::ReceiveExpInfo( const LPSTR& data )
	{
		ReceiveExpData*	receiveExpdata = ( ReceiveExpData* )data;
		levelManager->SetExp( receiveExpdata->exp );
	}

	//	�N���X�`�F���W����M
	void	GameParam::ReceiveClassChangeInfo( const LPSTR& data )
	{
		ReceiveClassChangeData* receiveData = ( ReceiveClassChangeData* )data;
		playerManager->ClassChange( receiveData->id, receiveData->nextClass );
	}

	//	�X�e�[�^�X��M
	void	GameParam::ReceiveStatusInfo( const LPSTR& data )
	{
		levelManager->CulcStatus( data );
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
		SetPlayerInfo( signUp->id, signUp->name );
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
	void	GameParam::SetPlayerInfo( int id, char* name )
	{
		playerInfo[id].active = true;
		strcpy( playerInfo[id].name, name );
	}

	//	�_�����ݒ�
	void	GameParam::SetPointInfo( int id, int point )
	{
		pointInfo[id].point = point;
	}

	//	�}�b�`���O���ݒ�
	void	GameParam::SetMatchingInfo( int id, bool isComplete )
	{
		matchingInfo[id].isComplete = isComplete;
	}

	//	���Z���ݒ�
	void	GameParam::AddPoint( int id, int addPoint )
	{
		pointInfo[id].addPoint += addPoint;
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
