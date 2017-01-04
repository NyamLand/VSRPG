
#pragma once

//*************************************************************************
//
//	Item構造体
//
//*************************************************************************

//	include
#include	"Timer.h"

//	class
class Item
{
protected:
	bool state;
	Timer*	timer;
	int id;

public:
	//	初期化・解放
	Item( int id );
	virtual	~Item( void );

	//	更新
	virtual	void	Update( void ) = 0;
	bool TimerUpdate( void );
	
	//	動作関数
	virtual	void	UseItem( void ) = 0;
};
