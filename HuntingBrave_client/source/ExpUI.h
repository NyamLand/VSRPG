
#pragma once

//***************************************************************
//
//	ExpUI�N���X
//
//***************************************************************

namespace EXP_MAX
{
	enum
	{
		ICON_SIZE = 64,				//	�摜��
	};
}

#include	"NumberUI.h"


//	class
class ExpUI
{
private:
	Image* icon;
	Image* number[DIGIT_MAX];
	int numbox[DIGIT_MAX];
	int	exp, exp_digit;
	int	posx, posy, size;

public:
	//	�������E���
	ExpUI(int x, int y, int w, int h);
	~ExpUI(void);

	//	�X�V�E�`��
	void	Update(void);
	void	ExpManager(void);
	void	SetParam(int x, int y, int w, int h);
	void	SetRenderFlag(bool c);
	void	NumberSet(Image* img, const int num, const int digit);
	Image*	GetImageExp(){ return icon; }
	void	Render(void);
};

