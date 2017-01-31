
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
		SIZE = 32					//	数値サイズ
	};
}


//	class
class HpUI
{
private:
	Image* hpFrame_obj;
	iex2DObj* hpDamage_obj;
	iex2DObj* hp_obj;
	Image* hpBack_obj;
	NumberUI* maxHpUI;
	NumberUI* nowHpUI;
	Image* period;

	int	posx, posy, width, height;
	int hp,max_hp,damage,damage_width,keep_width;
	float damage_volume;

	int hp_damage_sw;
	int hp_w,hp_sw;
	bool damage_state;

public:
	//	初期化・解放
	HpUI(int x, int y, int w, int h);
	~HpUI(void);
	Image*	GetImageHp(){ return hpFrame_obj; }
	//	更新・描画
	void	SetDamage(void);
	void	DamageManager(void);
	void	Update(void);
	void	Render(void);

	//	情報取得・設定
	void	SetHp(int hp);
	void	SetMaxHp(int max_hp);
};

