
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
	Player*	player;

	//	�������E���
	PlayerManager( void );
	~PlayerManager( void )override;

public:
	//	�������E���
	bool	Initialize( void )override;
	void	Release( void )override;

	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );

	//	���ݒ�
	void	SetPlayer( int id, int type );

	//	���擾
	Player*	GetPlayer( void );
};

#define	playerManager ( PlayerManager::GetInstance() )
