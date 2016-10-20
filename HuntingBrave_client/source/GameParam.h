
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

public:
	//	�������E���
	GameParam( void );
	~GameParam( void );
	bool InitializeClient( char* addr, int nPort, char* name );
	void CloseClient( void );

	//	�f�[�^�X�V�i����M�j
	void Update( void );
	void Receive( void );

	//	�v���C���[�p�����[�^����
	void SetPlayerParam( int id, PlayerParam& param );
	void SetPlayerParam( int id, Vector3& pos );
	PlayerParam GetPlayerParam( int id ){ return playerParam[id]; }
	PlayerInfo	GetPlayerInfo( int id ){ return playerInfo[id]; }
	
	//	�v���C���[��񑀍�
	void  SetPlayerInfo( int id, char* name );
	void  RemovePlayerInfo( int id );

	bool  GetPlayerActive( int id ){ return playerInfo[id].active; }
	int   GetMyIndex(){ return myIndex; }
	char* GetPlayerName( int id ){ return playerInfo[id].name; }
};

extern	GameParam*	gameParam;


