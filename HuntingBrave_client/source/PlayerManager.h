
#pragma once

//***************************************************************
//
//	PlayerManager�N���X
//
//***************************************************************

//	include
#include	"Singleton.h"
#include	"Player.h"

//	class
class PlayerManager : public Singleton<PlayerManager>
{
	friend class Singleton<PlayerManager>;

private:
	//	�p�����[�^
	Player*	player[PLAYER_MAX];

	//	�������E���
	PlayerManager( void );
	~PlayerManager( void )override;

public:
	//	�������E���
	bool	Initialize( void );
	void	Release( void );

	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );

	//	���ݒ�
	void	SetPlayer( int id );

	//	���擾
	Player*&	GetPlayer( int id );
};

#define	playerManager ( PlayerManager::GetInstance() )
