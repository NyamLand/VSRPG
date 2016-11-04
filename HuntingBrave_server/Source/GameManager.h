
#pragma once

//*****************************************************************************************************************************
//
//	GameManager�N���X
//
//*****************************************************************************************************************************

//	include
#include	"GameData.h"
#include	"Timer.h"

//	class
class GameManager
{
private:
	PlayerParam	initPlayerParam[PLAYER_MAX];
	Timer*	timer;

public:
	//	�������E���
	GameManager( void );
	~GameManager( void );

	//	�X�V
	void	Update( void );

	//	����֐�
	void	TimerUpdate( void );

	//	���ݒ�

	//	���擾
	Timer*	GetTimer( void )const;
	PlayerParam	GetInitInfo( int id )const;
};

extern	GameManager*	gameManager;