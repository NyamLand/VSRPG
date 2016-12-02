
#pragma once

//***************************************************************
//
//	GameParam�N���X
//
//***************************************************************

//	include
#include	"GameData.h"
#include	"CharaInfo.h"
#include	"ShapeInfo.h"
#include	"UDPServer.h"

//	class
class GameParam : public UDPServer
{
private:
	PlayerInfo		playerInfo[PLAYER_MAX];
	PlayerParam	playerParam[PLAYER_MAX];
	AttackInfo	attackInfo[PLAYER_MAX];
	LifeInfo			lifeInfo[PLAYER_MAX];

	//	�֐��|�C���^
	int ( GameParam::*ReceiveFunction[RECEIVE_COMMAND::COMMAND_MAX] )( int client, const LPSTR& data );

public:
	//	�������E���
	GameParam( void );
	bool InitializeServer( void );
	void	InitializePlayer( int id );

	//	�f�[�^����M
	int Receive( char scene );
	int Send( int client );

	//	�V�[�����Ƃ̎�M����
	int	MainReceive( int client, const LPSTR& data );
	int	MatchingReceive( int client, const LPSTR& data );
	int	ResultReceive( int client, const LPSTR& data );

	//	���M����
	void	SendCharaInfo( int client, int player );
	void	SendMatchingInfo( int client, int player );
	void	SendGameInfo( int client );

	//	��M����
	int	ReceiveChara( int client, const LPSTR& data );
	int	ReceiveAttackInfo( int client, const LPSTR& data );
	int	ReceiveInput( int client, const LPSTR& data );
	int	ReceiveHuntInfo( int client, const LPSTR& data );
	int	ReceiveLevelInfo( int client, const LPSTR& data );

	//	���O�C���֘A��M
	int	ReceiveSignUp( int client, const LPSTR& data );
	int	ReceiveSignOut( int client, const LPSTR& data );
	int	ReceiveMatching( int client, const LPSTR& data );
	int	ReceiveSignUpResponse( int client, const LPSTR& data );

	//	���ݒ�
	void SetPlayerParam( int id, const PlayerParam& param );
	void SetPlayer( int id, char* name );
	void ReleasePlayer( int id );
	void SetPlayerParam( int id, const Vector3& pos, float angle, int motion );

	//	���擾
	bool GetPlayerActive( int id ){ return playerInfo[id].active; }
	PlayerParam&	GetPlayerParam( int id ){ return playerParam[id]; }
	AttackInfo&		GetAttackInfo( int id ){ return attackInfo[id]; }
	LifeInfo&			GetLifeInfo( int id ){ return	lifeInfo[id]; }
};

extern	GameParam*	gameParam;