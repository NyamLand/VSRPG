
#pragma once

//***************************************************************
//
//	GameParam�N���X
//
//***************************************************************

//	include
#include	"GameData.h"
//#include	"winsock.h"
#include	"SocketClient.h"

//	class
class GameParam : public SocketClient
{
private:
	int	myIndex;

	//	Player���
	PlayerInfo		playerInfo[PLAYER_MAX];
	PlayerParam	playerParam[PLAYER_MAX];
	
public:
	//	�������E���
	GameParam( void );
	~GameParam( void );
	bool	InitializeClient( LPSTR addr, int nPort, LPSTR name, int type );
	void	CloseClient( void );

	//	�X�V
	void	Update( void );

	//	����M
	void	Receive( void );

	//	���ݒ�
	void	SetPlayerInfo( int id, LPSTR name, int type );
	void	SetPlayerParam( int id, PlayerParam& param );
	void	SetPlayerParam( int id, Vector3& pos, float angle, int motion );
	
	//	���擾
	PlayerParam& GetPlayerParam( int id );
};
