
#pragma once

//***************************************************************
//
//	ScoreUIクラス
//
//***************************************************************

namespace SCORE_MAX
{
	enum
	{
		ICON_SIZE = 64,				//	画像幅
	};
}


//	class
class ScoreUI
{
private:
	Image* icon;
	NumberUI*	number;
	int	posx, posy, size;

public:
	//	初期化・解放
	ScoreUI(int x, int y, int w, int h);
	~ScoreUI(void);

	//	更新・描画
	void	Update(void);
	void	ScoreManager(void);
	void	SetParam(int x, int y, int w, int h);
	void	SetRenderFlag(bool c);
	void	SetScore(int s);
	void	NumberSet(Image* img, const int num, const int digit);
	void	Render(void);
};

