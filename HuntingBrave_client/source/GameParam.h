
#pragma once

//*****************************************************************************************************************************
//
//	GameParam�N���X
//
//*****************************************************************************************************************************

//	include
#include	"GameData.h"
#include	"CharaInfo.h"
#include	"SocketClient.h"

//	class
class GameParam : public SocketClient
{
private:
	//	�v���C���[�ԍ�
	int		myIndex;
	bool		inputAcceptance;	//	���͎�t

	PlayerInfo		playerInfo[PLAYER_MAX];
	PlayerParam	playerParam[PLAYER_MAX];
	AttackInfo	attackInfo[PLAYER_MAX];
	PointInfo		pointInfo[PLAYER_MAX];

public:
	//	�������E���
	GameParam( void );
	~GameParam( void );
	bool InitializeClient( char* addr, int nPort, char* name );
	void CloseClient( void );

	//	�f�[�^�X�V�i����M�j
	void Update( void );
	void Receive( void );

	//	���M����
	void	SendPlayerInfo( void );
	void	SendPointInfo( void );
	void	SendAttackParam( void );

	//	��M����
	void	ReceiveCharaInfo( const LPSTR& data );
	void	ReceivePointInfo( const LPSTR& data );
	void	ReceiveSignUpInfo( const LPSTR& data );
	void	ReceiveSignOutInfo( const LPSTR& data );
	void	ReceiveGameInfo( const LPSTR& data );

	//	�v���C���[�p�����[�^����
	void	SetPlayerParam( int id, const PlayerParam& param );
	void	SetPlayerParam( int id, const Vector3& pos, float angle, int motion, int life );
	
	//	���ݒ�
	void  SetPlayerInfo( int id, char* name );
	void	SetPointInfo( int id, int addPoint );
	void	AddPoint( int id, int point );
	void  RemovePlayerInfo( int id );
	
	//	���擾
	PlayerParam GetPlayerParam( int id )const{ return playerParam[id]; }
	PlayerInfo	GetPlayerInfo( int id )const{ return playerInfo[id]; }
	AttackInfo&	GetAttackInfo( int id ){ return	attackInfo[id]; }
	PointInfo&	GetPointInfo( int id ){ return	pointInfo[id]; }
	bool		GetPlayerActive( int id ){ return playerInfo[id].active; }
	int		GetMyIndex( void ){ return myIndex; }
	char*	GetPlayerName( int id ){ return playerInfo[id].name; }
	float		GetStickInput( float& outX, float& outY );
};

extern	GameParam*	gameParam;