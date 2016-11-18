
#pragma once

//*****************************************************************************************************************************
//
//	GameParam�N���X
//
//*****************************************************************************************************************************

//	include
#include	"GameData.h"
#include	"SocketClient.h"

//	class
class GameParam : public SocketClient
{
private:
	int		myIndex;

	PlayerInfo	playerInfo[PLAYER_MAX];
	PlayerParam	playerParam[PLAYER_MAX];
	PointInfo		pointInfo[PLAYER_MAX];
	MatchingInfo		matchingInfo[PLAYER_MAX];

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
	void	SendChraraInfo( void );
	void	SendMove( void );
	void	SendPoint( void );
	void	SendMatching(void);

	//	��M����
	void	ReceiveCharaInfo(const LPSTR& data);
	void	ReceiveCharaDATA(const LPSTR& data);
	void	ReceiveControllerAxis(int client, const LPSTR& data);
	void	ReceiveCharaMove(const LPSTR& data);

	void	ReceivePoint( const LPSTR& data );
	void	ReceiveMatching(const LPSTR& data);
	void	ReceiveSignUp( const LPSTR& data );
	void	ReceiveSignOut( const LPSTR& data );
	void	ReceiveGameInfo( const LPSTR& data );

	//	�v���C���[�p�����[�^����
	void	SetPlayerParam( int id, const PlayerParam& param );
	void	SetPlayerParam( int id, const Vector3& pos, float angle, int motion );
	void	SetPlayerPos(int id, const Vector3& pos);
	void	SetPlayerMove(int id, const Vector3& move);
	
	//	���ݒ�
	void  SetPlayerInfo( int id, char* name );
	void	SetPointInfo( int id, int addPoint );
	void	SetMachingInfo(int id, bool isComplete);
	void	AddPoint( int id, int point );
	void  RemovePlayerInfo( int id );
	
	//	���擾
	PlayerParam GetPlayerParam( int id )const{ return playerParam[id]; }
	PlayerInfo	GetPlayerInfo( int id )const{ return playerInfo[id]; }
	PointInfo&		GetPointInfo(int id){ return	pointInfo[id]; };
	MatchingInfo&		GetMatchingInfo(int id){ return	matchingInfo[id]; };
	bool  GetPlayerActive( int id ){ return playerInfo[id].active; }
	int		GetMyIndex( void ){ return myIndex; }
	char* GetPlayerName( int id ){ return playerInfo[id].name; }
	float	GetStickInput( float& outX, float& outY );
};

extern	GameParam*	gameParam;