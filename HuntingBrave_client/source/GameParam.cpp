
#include	"iextreme.h"
#include	"GameData.h"
#include	"GameManager.h"
#include	"PlayerManager.h"
#include	"InputManager.h"
#include	<thread>
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
			ZeroMemory( &pointInfo[id], sizeof( PointInfo ) );
			ZeroMemory( &matchingInfo[id], sizeof( MatchingInfo ) );
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
		SignUp signUp( -1, name );
		send( ( char* )&signUp, sizeof( signUp ) );

		//	�lID�擾
		if( receive( ( char* )&signUp, sizeof( signUp ) ) <= 0 ) return false;
		myIndex = signUp.id;

		//	�������W�擾
		ReceiveCharaData	receiveCharaData;
		if ( receive( ( LPSTR )&receiveCharaData, sizeof( receiveCharaData ) ) <= 0 )	return	false;
		SetPlayerParam( myIndex, 
			receiveCharaData.pos, receiveCharaData.angle, 
			receiveCharaData.motion, receiveCharaData.life );
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
			case RECEIVE_COMMAND::CHARA_INFO:	//	�ړ����
				ReceiveCharaInfo( data );
				break;

			case RECEIVE_COMMAND::GAME_INFO:	//	�Q�[�����
				ReceiveGameInfo( data );
				break;

			case RECEIVE_COMMAND::POINT_INFO:	//	�_�����
				ReceivePointInfo( data );
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

		//	�_���f�[�^���M
		SendPointInfo();

		//	�U���f�[�^���M
		SendAttackParam();

		//	�}�b�`���O��񑗐M
		SendMatching();

		//	���͏�񑗐M
		SendInputInfo();
	}

//----------------------------------------------------------------------------------------------
//	�f�[�^���M
//----------------------------------------------------------------------------------------------

	//	��񑗐M
	void	GameParam::SendPlayerInfo( void )
	{
		//	�X�e�B�b�N���͏��擾
		float axisX = 0.0f, axisY = 0.0f;
		inputManager->GetStickInputLeft( axisX, axisY );

		//	�t���[�����擾
		int	frame = playerManager->GetPlayer( myIndex )->GetFrame();

		//	���M���ݒ�
		SendPlayerData	sendPlayerData( axisX, axisY, frame  );

		send( ( LPSTR )&sendPlayerData, sizeof( sendPlayerData ) );
	}

	//	�_����񑗐M
	void	GameParam::SendPointInfo( void )
	{
		//	���Z�����O�Ȃ�X�L�b�v
		if ( pointInfo[myIndex].addPoint == 0 )	return;

		//	���i�[
		SendPointData	sendPointData( pointInfo[myIndex].addPoint );

		//	���M
		send( ( LPSTR )&sendPointData, sizeof( sendPointData ) );

		//	���Z��񃊃Z�b�g
		pointInfo[myIndex].addPoint = 0;
	}

	//	�U����񑗐M
	void	GameParam::SendAttackParam( void )
	{
		//	���ݒ�
		AttackInfo	atkInfo = attackInfo[myIndex];
		SendAttackData	sendAttackData( atkInfo.pos1, atkInfo.pos2, atkInfo.radius );

		//	���M
		send( ( LPSTR )&sendAttackData, sizeof( sendAttackData ) );
	}

	//	�}�b�`���O��ԑ��M
	void	GameParam::SendMatching( void )
	{
		Matching	matching;
		matching.id = myIndex;
		matching.isComplete = gameManager->GetIsComplete();
		send( ( LPSTR )&matching, sizeof( matching ) );
	}

	//	���͏�񑗐M
	void	GameParam::SendInputInfo( void )
	{
		//	���U���{�^����ԑ��M
		CheckInputData( KEY_TYPE::B );
		
		//	���@�U���{�^����ԑ��M
		CheckInputData( KEY_TYPE::A );

		//	
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
	}

	//	�T�C���A�E�g����M
	void	GameParam::ReceiveSignOutInfo( const LPSTR& data )
	{
		SignOut*	signOut = ( SignOut* )data;

		RemovePlayerInfo( signOut->id ); 
	}

//----------------------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------------------

	//	���̓`�F�b�N�����M
	void	GameParam::CheckInputData( int key )
	{
		//	���̓`�F�b�N
		int inputType = KEY( key );
		if ( inputType == 0 )	return; 

		//	���M
		SendInputData		sendInputData( key, inputType );
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

		playerManager->SetPlayer( id );
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

//----------------------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------------------
