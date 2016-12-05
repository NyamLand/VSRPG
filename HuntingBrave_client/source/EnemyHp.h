
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
	int mode_type;
	float	width, height;
	float	hp;
	float maxHp;

public:
	//	初期化・解放
	EnemyHpUI( void );
	~EnemyHpUI(void);
	void Initilaize(int type, float maxhp);

	//	更新・描画
	void	Update( void );
	void	Render(float hp, Vector3 pos, Vector3 up);
};

