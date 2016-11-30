
#pragma once

//***************************************************************
//
//	ExpUIクラス
//
//***************************************************************

namespace EXP_MAX
{
	enum
	{
		ICON_SIZE = 64,				//	画像幅
		DIGIT_MAX = 4,				//	数字最大桁数 
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
	//	初期化・解放
	ExpUI(int x, int y, int w, int h);
	~ExpUI(void);

	//	更新・描画
	void	Update(void);
	void	ExpManager(void);
	void	NumberSet(Image* img, const int num, const int digit);
	void	Render(void);
};

