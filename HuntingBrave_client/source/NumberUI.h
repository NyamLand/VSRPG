
#pragma once

//***************************************************************
//
//	NumberUIクラス
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
	//	初期化・解放
	NumberUI(int x, int y, int w, int h);
	~NumberUI(void);

	//	更新・描画
	void	Update(void);
	void	NumberManager(void);
	void	SetParam(int x, int y, int w, int h);
	void	SetRenderFlag(bool c);
	void	NumberSet(Image* img, const int num, const int digit);
	void	Render(void);
};

