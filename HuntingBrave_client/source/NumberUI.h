
#pragma once

//***************************************************************
//
//	NumberUI�N���X
//
//***************************************************************

#define	DIGIT_MAX 4

namespace NUM_COLOR
{
	enum
	{
		WHITE,	//	���F�p�x�[�X
		RED,
		PURPLE,
		GREEN,
	};
}

//	class
class NumberUI
{
private:
//	Image* icon;
	Image* number[DIGIT_MAX];
	int numbox[DIGIT_MAX];
	int	num, digit;
	int	color;
	int	posx, posy, size;

public:
	//	�������E���
	NumberUI(int x, int y, int w, int h);
	~NumberUI(void);

	//	�X�V�E�`��
	void	Update(const Image* icon);
	void	NumberManager(void);
	void	SetParam(int x, int y, int w, int h);
	void	SetRenderFlag(bool c);
	void	NumberSet(Image* img, const int num, const int digit, const Image* icon, int color);
	void	SetNum(int n);
	void	SetColor(int c);
	void	SetColor(float r, float g, float b);
	void	Render(void);
};

