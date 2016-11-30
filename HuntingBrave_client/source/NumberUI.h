
#pragma once

//***************************************************************
//
//	NumberUI�N���X
//
//***************************************************************

#define	DIGIT_MAX 4

//	class
class NumberUI
{
private:
	Image* icon;
	Image* number[DIGIT_MAX];
	int numbox[DIGIT_MAX];
	int	score, score_digit;
	int	posx, posy, size;

public:
	//	�������E���
	NumberUI(int x, int y, int w, int h);
	~NumberUI(void);

	//	�X�V�E�`��
	void	Update(void);
	void	NumberManager(void);
	void	SetParam(int x, int y, int w, int h);
	void	SetRenderFlag(bool c);
	void	NumberSet(Image* img, const int num, const int digit);
	void	Render(void);
};

