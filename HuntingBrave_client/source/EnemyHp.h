
#pragma once

//***************************************************************
//
//	ENEMYHpUIクラス
//
//***************************************************************
#include	"Singleton.h"
namespace HP_MAX
{
	enum
	{
		WIDTH = 768,				//	画像横幅
		HEIGHT = 64,				//	画像縦幅
	};
}


//	class
class EnemyHpUI
{
private:
	Image* hpFrame_obj;
	Image* hp_obj;
	Image* hpBack_obj;
	int	posx, posy, width, height;

public:
	//	初期化・解放
	EnemyHpUI(int x, int y, int w, int h);
	~EnemyHpUI(void);

	//	更新・描画
	void	Update(void);
	void	Render(void);
};

