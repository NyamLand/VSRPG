
#pragma once

//***************************************************************
//
//	PlayerManager�N���X
//
//***************************************************************

//	include
#include	"GameData.h"
#include	"GameParam.h"
#include	"Singleton.h"
#include	"Player.h"

//	class
class PlayerManager : public Singleton<PlayerManager>
{
	friend class Singleton<PlayerManager>;

private:
	//	�p�����[�^
	Player*	player[PLAYER_MAX];

	GameParam*	gameParam;

	//	�������E���
	PlayerManager( void );
	~PlayerManager( void )override;

public:
	//	�������E���
	bool	Initialize( GameParam* gameParam );
	void	Release( void )override;

	//	�X�V�E�`��
	void	Update( int id );

	//	�v���C���[����
	void	SetPlayer( int id, int type );

	//	���擾
	Vector3	GetPos( int id );
};

#define	playerManager ( PlayerManager::GetInstance() )
