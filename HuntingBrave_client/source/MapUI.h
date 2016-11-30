
#pragma once

//***************************************************************
//
//	MapUIクラス
//
//***************************************************************

namespace MAP_MAX
{
	enum
	{
		WIDTH = 512,				//	画像横幅
		HEIGHT = 512,				//	画像縦幅
	};
}


//	class
class MapUI
{
private:
	Image*	obj;
	int	posx, posy, width, height;

public:
	//	初期化・解放
	MapUI(int x, int y, int w, int h);
	~MapUI(void);

	//	更新・描画
	void	Update(void);
	void	Render(void);
};

