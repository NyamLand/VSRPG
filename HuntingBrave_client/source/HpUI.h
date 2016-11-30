
#pragma once

//***************************************************************
//
//	HpUIクラス
//
//***************************************************************

namespace HP_MAX
{
	enum
	{
		WIDTH = 1024,				//	画像横幅
		HEIGHT = 256,				//	画像縦幅
	};
}


//	class
class HpUI
{
private:
	Image* hpFrame_obj;
	Image* hpDamage_obj;
	Image* hp_obj;
	Image* hpBack_obj;
	int	posx, posy, width, height;

public:
	//	初期化・解放
	HpUI(int x, int y, int w, int h);
	~HpUI(void);

	//	更新・描画
	void	Update(void);
	void	Render(void);
};

