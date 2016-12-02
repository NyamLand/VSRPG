
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
	MatchingInfo	matchingInfo[PLAYER_MAX];
	PlayerParam	initPlayerParam[PLAYER_MAX];
	Timer*	timer;
	char	scene;

public:
	//	�������E���
	GameManager( void );
	~GameManager( void );

	//	�X�V
	void	Update( void );

	//	����֐�
	bool	PlayerCheck( void );

	//	���擾
	Timer*	GetTimer( void )const;
	PlayerParam	GetInitInfo( int id )const;
	MatchingInfo&	GetMatchingInfo( int id );
};

extern	GameManager*	gameManager;