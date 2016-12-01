
#pragma once

//*****************************************************************************************************************************
//
//	GameManagerクラス
//
//*****************************************************************************************************************************

//	include
#include	"GameData.h"
#include	"Timer.h"

//	define
namespace
{
	namespace SCENE
	{
		enum
		{
			MATCHING,
			MAIN,
			RESULT
		};
	}
}

//	class
class GameManager
{
private:
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
	void	TimerUpdate( void );

	//	情報取得
	Timer*	GetTimer( void )const;
	PlayerParam	GetInitInfo( int id )const;
};

extern	GameManager*	gameManager;