
#pragma once

//***************************************************************
//
//	ENEMYHpUIクラス
//
//***************************************************************
#include	"Singleton.h"

namespace
{
	namespace HP_MAX
	{
		enum
		{
			WIDTH = 768,				//	画像横幅
			HEIGHT =128,				//	画像縦幅
		};

	}

	namespace HPUI_TYPE
	{
		enum
		{
			PLAYER,
			ENEMY,
		};
	}
}

//	class
class EnemyHpUI
{
private:
	iex2DObj* hpFrame_obj;
	iex2DObj* hp_obj;
	int	width, height;
	int hp;
	int mode_type;
	int maxHp;

public:
	//	初期化・解放
	EnemyHpUI( void );
	~EnemyHpUI(void);
	void Initilaize(int type, int maxhp);

	//	更新・描画
	void	Update( void );
	void	Render(int hp, Vector3 pos, Vector3 up);
};

