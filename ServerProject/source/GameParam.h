
#pragma once

//***************************************************************
//
//	GameParam�N���X
//
//***************************************************************

//	include
#include	"UDPServer.h"
#include	"GameData.h"

//	class
class GameParam : public UDPServer
{
private:
	PlayerInfo	playerInfo[PLAYER_MAX];
	PlayerParam	playerParam[PLAYER_MAX];

public:
	//	�������E���
	GameParam( void );
	bool	InitializeServer( void );

	//	�`��
	void	Render( void );

	//	��M�E���M
	int		Receive( void );
	int		Send( int client );

	//	���ݒ�
	void	SetPlayer( int id, const LPSTR name );
	void	SetPlayerParam( int id, const PlayerParam& param );
	void	SetPlayerParam( int id, const Vector3& pos, float angle );

	//	���擾
	bool	GetPlayerActive( int id );
	PlayerParam& GetPlayerParam( int id );
};

