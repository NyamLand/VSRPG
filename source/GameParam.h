
#pragma once

//***************************************************************
//
//	GameParam�N���X
//
//***************************************************************

//	include
#include	"GameData.h"
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

	//	��M����
	void	CharaInfoReceive( const LPSTR& data );
	void	SignUpReceive( const LPSTR& data );
	void	SignOutReceive( const LPSTR& data );

	//	���M����
	void	SendCharaData( void );

	//	���ݒ�
	void	SetPlayerInfo( int id, const LPSTR& name );
	void	SetPlayerParam( int id, const PlayerParam& param );
	void	SetPlayerParam( int id, const Vector3& pos, float angle );
	
	//	���擾
	PlayerInfo	GetPlayerInfo( int id )const;
	PlayerParam GetPlayerParam( int id )const;
	PlayerInfo	GetMyInfo( int id )const;
	int		GetMyIndex( void )const;
};

extern	GameParam*	gameParam;
