
#pragma once

//***************************************************************
//
//	ItemUIクラス
//
//***************************************************************

namespace ITEM_MAX
{
	enum
	{
		WIDTH = 512,				//	画像横幅
		HEIGHT = 256,				//	画像縦幅
		SPX	= 0,
		SPY = 256 * 3,
	};
}


//	class
class ItemUI
{
private:
	Image*		obj;
	Image*		icon[2];
	int	posx, posy, width, height;
	float	itemInterval[2];

public:
	//	初期化・解放
	ItemUI(int x, int y, int w, int h);
	~ItemUI(void);

	//	更新・描画
	void	Update(void);
	void	Render(void);
};

