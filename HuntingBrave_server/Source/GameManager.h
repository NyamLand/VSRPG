
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
	PlayerParam	initPlayerParam[PLAYER_MAX];
	Timer*	timer;

public:
	//	初期化・解放
	GameManager( void );
	~GameManager( void );

	//	更新
	void	Update( void );

	//	動作関数
	void	TimerUpdate( void );

	//	情報設定

	//	情報取得
	Timer*	GetTimer( void )const;
	PlayerParam	GetInitInfo( int id )const;
};

extern	GameManager*	gameManager;