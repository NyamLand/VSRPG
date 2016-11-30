
#pragma once

//*****************************************************************************************************************************
//
//	PlayerManager�N���X
//
//*****************************************************************************************************************************

//	include
#include	"GameParam.h"
#include	"Player.h"

//	class
class PlayerManager
{
private:
	Player*	player[PLAYER_MAX];
	GameParam*	gameParam;

public:
	//	�������E���
	PlayerManager( GameParam* gameParam );
	~PlayerManager( void );
	bool	Initialize( void );

	//	�X�V�E�`��
	void	Update( int id );

	//	���ݒ�
	void	PosCheck( int client );
	void	SetPlayer( int id );
	void	ReleasePlayer( int id );

	//	���W�擾
	Vector3	GetPos( int id );
	Player*	&	GetPlayer( int id );
};

extern	PlayerManager*	playerManager;