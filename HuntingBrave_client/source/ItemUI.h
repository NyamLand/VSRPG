
#pragma once

//***************************************************************
//
//	ItemUIクラス
//
//***************************************************************

//	include
#include	"ItemManager.h"

//	class
class ItemUI
{
private:
	Image*		obj;
	Image*		icon[ITEM_POS::ITEM_MAX];
	int	posx, posy, width, height;
	float	itemInterval[ITEM_POS::ITEM_MAX];

public:
	//	初期化・解放
	ItemUI(int x, int y, int w, int h);
	~ItemUI(void);

	void	IconInitialize( void );

	//	更新・描画
	void	Update(void);
	void	Render(void);
};

