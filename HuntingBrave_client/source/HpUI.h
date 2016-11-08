
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
	//	�������E���
	HpUI(int x, int y, int w, int h);
	~HpUI(void);

	//	�X�V�E�`��
	void	Update(void);
	void	Render(void);
};

