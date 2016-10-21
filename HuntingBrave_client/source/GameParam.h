
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

	//	���M����
	void	SendChraraInfo( void );
	
	//	��M����
	void	ReceiveCharaInfo( const LPSTR& data );
	void	ReceiveSignUp( const LPSTR& data );
	void	ReceiveSignOut( const LPSTR& data );

	//	�v���C���[�p�����[�^����
	void SetPlayerParam( int id, const PlayerParam& param );
	void SetPlayerParam( int id, const Vector3& pos );
	PlayerParam GetPlayerParam( int id ){ return playerParam[id]; }
	PlayerInfo	GetPlayerInfo( int id ){ return playerInfo[id]; }
	
	//	���ݒ�
	void  SetPlayerInfo( int id, char* name );
	void  RemovePlayerInfo( int id );
	
	//	���擾
	bool  GetPlayerActive( int id ){ return playerInfo[id].active; }
	int		GetMyIndex( void ){ return myIndex; }
	char* GetPlayerName( int id ){ return playerInfo[id].name; }
};

extern	GameParam*	gameParam;