
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
	PlayerParam	initPlayerParam[PLAYER_MAX];
	Timer*	timer;
	char	scene;

public:
	//	初期化・解放
	GameManager( void );
	~GameManager( void );

	//	更新
	void	Update( void );

	//	動作関数
	bool	PlayerCheck( void );

	//	情報取得
	Timer*	GetTimer( void )const;
	PlayerParam	GetInitInfo( int id )const;
	MatchingInfo&	GetMatchingInfo( int id );
};

extern	GameManager*	gameManager;