
#pragma once

//***************************************************************
//
//	GameParam�N���X
//
//***************************************************************

//	include
#include	"GameData.h"
#include	"UDPServer.h"

//	class
class GameParam : public UDPServer
{
private:
	PlayerInfo	playerInfo[PLAYER_MAX];
	PlayerParam	playerParam[PLAYER_MAX];

public:
	//	�������E���
	GameParam( void );
	bool InitializeServer( void );

	//	�f�[�^����M
	int Receive( void );
	int Send( int client );

	//	���M����
	void	SendCharaInfo( int client );

	//	��M����
	void	ReceiveChara( int client, const LPSTR& data );
	void	ReceiveSignUp( int client, const LPSTR& data );
	void	ReceiveSignOut( int client, const LPSTR& data );

	//	���ݒ�
	void SetPlayerParam( int id, PlayerParam& param );
	void SetPlayer( int id, char* name );
	void SetPlayerParam( int id, Vector3& pos, float angle );
	PlayerParam& getPlayerParam( int id ){ return playerParam[id]; }

	//	���擾
	bool GetPlayerActive( int id ){ return playerInfo[id].active; }
};
