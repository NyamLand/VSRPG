
#pragma once

//*****************************************************************************************************************************
//
//	GameManagerクラス
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
	//	初期化・解放
	GameManager( void );
	~GameManager( void );
	void	MatchingInfoInitialize( void );

	//	更新
	void	Update( void );

	//	動作関数
	bool	PlayerCheck( void );
	void	ChangeScene( char& out, char nextScene );

	//	情報取得
	Timer*&	GetTimer( void );
	PlayerParam	GetInitInfo( int id )const;
	MatchingInfo&	GetMatchingInfo( int id );
	bool	GetTimeUp( void );
	bool	GetGameState( void );
};

extern	GameManager*	gameManager;