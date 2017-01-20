
#pragma once

//***************************************************************
//
//	TimerUIクラス
//
//***************************************************************



namespace TIME_MAX
{
	enum
	{
		WIDTH = 64,
		HEIGHT = 64,
	};
}

namespace TIME
{
	enum
	{
		MIN,
		SECOND,
	};
}

//	class
class TimerUI
{
private:
	Image*	period;
	NumberUI*	number[2];	//	min、second
	float	timer;
	int		color;
	int		posx, posy, size;

public:
	//	初期化・解放
	TimerUI(int x, int y, int w, int h);
	~TimerUI(void);

	//	更新・描画
	void	Update(void);
	void	Render(void);
};

