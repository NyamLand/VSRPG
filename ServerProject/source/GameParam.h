
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

	//	���[�h�ʊ֐��|�C���^
	int( GameParam::*ReceiveFunction[DATA_MODE::DATA_MAX])( int client, LPSTR data );

public:
	//	�������E���
	GameParam( void );
	~GameParam( void );
	bool	InitializeServer( void );

	//	�`��
	void	Render( void );

	//	��M�E���M
	int		Receive( void );
	int		Send( int client );

	//	���ݒ�
	void	SetPlayer( int id, LPSTR name, int type );
	void	SetPlayerParam( int id, PlayerParam& param );
	void	SetPlayerParam( int id, Vector3& pos, float angle, int motion );

	//	�e���[�h����
	int		PosReceive( int client, LPSTR data );
	int		MoveReceive( int client, LPSTR data );
	int		ChatReceive( int client, LPSTR data );
	int		SignUpReceive( int client, LPSTR data );
	int		SignOutReceive( int client, LPSTR data );

	//	���擾
	bool	GetPlayerActive( int id );
	PlayerParam& GetPlayerParam( int id );
};

