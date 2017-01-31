
#pragma once

//***************************************************************
//
//	HpUI�N���X
//
//***************************************************************

namespace HP_MAX
{
	enum
	{
		WIDTH = 1024,				//	�摜����
		HEIGHT = 256,				//	�摜�c��
		SIZE = 32					//	���l�T�C�Y
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
	//	�������E���
	HpUI(int x, int y, int w, int h);
	~HpUI(void);
	Image*	GetImageHp(){ return hpFrame_obj; }
	//	�X�V�E�`��
	void	SetDamage(void);
	void	DamageManager(void);
	void	Update(void);
	void	Render(void);

	//	���擾�E�ݒ�
	void	SetHp(int hp);
	void	SetMaxHp(int max_hp);
};

