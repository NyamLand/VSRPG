
#pragma once

//***************************************************************
//
//	NumberUI�N���X
//
//***************************************************************


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
	std::vector<Image*> number;
	std::vector<int>	numbox;
	int	num, digit, DIGIT_MAX;
	int	color;
	int	posx, posy, size;

public:
	//	�������E���
	NumberUI(int x, int y, int w, int h, int digit);
	~NumberUI(void);

	//	�X�V�E�`��
	void	Update(const Image* icon = null);
	void	NumberManager(void);
	void	SetParam(int x, int y, int w, int h);
	void	SetRenderFlag(bool c);
	void	NumberSet(Image* img, const int num, const int digit, const Image* icon, int color);
	void	NumberSet(Image* img, const int num, const int digit, int color);
	void	SetNum(int n);
	void	SetColor(int c);
	void	SetColor(float r, float g, float b);
	void	Render(void);
};

