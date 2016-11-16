
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
		SetPlayerParam( myIndex, receiveCharaData.pos, receiveCharaData.angle, receiveCharaData.motion );
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

		SendAttackParam();
	}

//----------------------------------------------------------------------------------------------
//	�f�[�^���M
//----------------------------------------------------------------------------------------------

	//	��񑗐M
	void	GameParam::SendPlayerInfo( void )
	{
		//	�X�e�B�b�N���͏��擾
		float axisX = 0.0f, axisY = 0.0f;
		GetStickInput( axisX, axisY );

		//	�t���[�����擾
		int	frame = playerManager->GetPlayer( myIndex )->GetFrame();

		//	���͏��擾
		char		inputType = inputManager->NO_INPUT;
		char		buttonType = inputManager->GetInput( inputType );

		//	���M���ݒ�
		SendPlayerData	sendPlayerData( axisX, axisY, buttonType, inputType, frame  );

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
		//	���擾
		AttackInfo	attackInfo = playerManager->GetPlayer( myIndex )->GetAttackInfo();

		//	�U�����Ă��Ȃ���΃X�L�b�v
		//if ( attackInfo.attackParam == AttackInfo::NO_ATTACK )	return;

		//	���ݒ�
		SendAttackData	sendAttackData( 
			attackInfo.attackParam, 
			attackInfo.collisionShape.capsule.p1,
			attackInfo.collisionShape.capsule.p2,
			attackInfo.collisionShape.capsule.r );
		//	���M
		send( ( LPSTR )&sendAttackData, sizeof( sendAttackData ) );
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
		SetPlayerParam( 
			receiveCharaData->id, 
			receiveCharaData->pos, 
			receiveCharaData->angle, 
			receiveCharaData->motion );
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
	void	GameParam::SetPlayerParam( int id, const Vector3& pos, float angle, int motion )
	{
		playerParam[id].pos = pos;
		playerParam[id].angle = angle;
		playerParam[id].motion = motion;
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

	//	�X�e�B�b�N���͏��擾( �Ԃ�l�ɓ��͂̒����A�����ɓ��͒l�������� )
	float	GameParam::GetStickInput( float& outX, float& outY )
	{
		outX = ( float )input[0]->Get( KEY_AXISX ) * 0.001f;
		outY = -( float )input[0]->Get( KEY_AXISY ) * 0.001f;

		return	Vector3( outX, 0.0f, outY ).Length();
	}
