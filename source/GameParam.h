
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
	//	�����̃v���C���[�ԍ�
	int	myIndex;

	//	Player���
	PlayerInfo		playerInfo[PLAYER_MAX];
	PlayerParam	playerParam[PLAYER_MAX];

	//	��M�֐��|�C���^
	void( GameParam::*ReceiveFunction[DATA_MODE::DATA_MAX] )( LPSTR data );

public:
	//	�������E���
	GameParam( void );
	~GameParam( void );
	bool	InitializeClient( LPSTR addr, int nPort, LPSTR name, int type );
	void	CloseClient( void );

	//	�X�V
	void	Update( void );

	//	����M
	void	Send( void );
	void	Receive( void );

	//	��M�֐�
	void	PosReceive( LPSTR data );
	void	MoveReceive( LPSTR data );
	void	ChatReceive( LPSTR data );
	void	SignUpReceive( LPSTR data );
	void	SignOutReceive( LPSTR data );

	//	���ݒ�
	void	SetPlayerInfo( int id, LPSTR name, int type );
	void	SetPlayerParam( int id, PlayerParam& param );
	void	SetPlayerParam( int id, Vector3& pos, float angle, int motion );
	
	//	���擾
	PlayerParam GetPlayerParam( int id )const;
	PlayerInfo	GetMyInfo( int id )const;
	int		GetMyIndex( void )const;
};

extern	GameParam*	gameParam;
