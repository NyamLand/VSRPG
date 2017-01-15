
#pragma once

//**************************************************************************
//
//	WaitLoadクラス
//
//**************************************************************************

//	include
#include	"Font.h"
#include	"Timer.h"

//	class
class WaitLoad
{
private:
	Font*	font;
	Timer*	timer;
	char		text[256];
	int		count;

public:
	//	初期化・解放
	WaitLoad( void );
	~WaitLoad( void );

	//	更新・描画
	void	Update( void );
	void	Render( void );
};
