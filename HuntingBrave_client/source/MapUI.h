
#pragma once

//***************************************************************
//
//	MapUIクラス
//
//***************************************************************

//	include
#include	"GameData.h"

//	class
class MapUI
{
private:
	Image*	back;
	Image*		player[PLAYER_MAX];
	int	posx, posy, width, height;

public:
	//	初期化・解放
	MapUI( void );
	~MapUI( void );

	//	更新・描画
	void	Update( void );
	void	Render( void );
};

