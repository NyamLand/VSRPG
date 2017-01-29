
#pragma once

//***************************************************************
//
//	PlayerManager�N���X
//
//***************************************************************

//	include
#include	"Singleton.h"
#include	"Suppin.h"
#include	"Fighter.h"
#include	"Magician.h"
#include	"Player.h"

//	class
class PlayerManager : public Singleton<PlayerManager>
{
	friend class Singleton<PlayerManager>;

private:
	Player*		player[PLAYER_MAX];

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
	void	RenderHp( void );

	//	����֐�
	void	ClassChange( int id, char nextClass );
	void	Receive( const LPSTR& data );
	
	//	���ݒ�
	void	SetPlayer( int id );

	//	���擾
	Player*&	GetPlayer( int id );
};

#define	playerManager ( PlayerManager::GetInstance() )
