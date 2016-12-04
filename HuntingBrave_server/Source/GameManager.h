
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
	PlayerParam		initPlayerParam[PLAYER_MAX];
	Timer*	timer;
	bool		timeUp;
	bool		gameState;

public:
	//	�������E���
	GameManager( void );
	~GameManager( void );
	void	MatchingInfoInitialize( void );

	//	�X�V
	void	Update( void );

	//	����֐�
	bool	PlayerCheck( void );
	void	ChangeScene( char& out, char nextScene );

	//	���擾
	Timer*&	GetTimer( void );
	PlayerParam	GetInitInfo( int id )const;
	MatchingInfo&	GetMatchingInfo( int id );
	bool	GetTimeUp( void );
	bool	GetGameState( void );
};

extern	GameManager*	gameManager;