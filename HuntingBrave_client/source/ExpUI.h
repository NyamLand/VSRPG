
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
		DIGIT_MAX = 4,				//	�����ő包�� 
	};
}


//	class
class ExpUI
{
private:
	Image* icon;
	Image* number[EXP_MAX::DIGIT_MAX];
	int numbox[EXP_MAX::DIGIT_MAX];
	int	exp, exp_digit;
	int	posx, posy, size;

public:
	//	�������E���
	ExpUI(int x, int y, int w, int h);
	~ExpUI(void);

	//	�X�V�E�`��
	void	Update(void);
	void	ExpManager(void);
	void	NumberSet(Image* img, const int num, const int digit);
	void	Render(void);
};

