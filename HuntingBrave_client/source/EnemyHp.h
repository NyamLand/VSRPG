
#pragma once

//***************************************************************
//
//	ENEMYHpUI�N���X
//
//***************************************************************
#include	"Singleton.h"
namespace HP_MAX
{
	enum
	{
		WIDTH = 768,				//	�摜����
		HEIGHT = 64,				//	�摜�c��
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
	//	�������E���
	EnemyHpUI(int x, int y, int w, int h);
	~EnemyHpUI(void);

	//	�X�V�E�`��
	void	Update(void);
	void	Render(void);
};

