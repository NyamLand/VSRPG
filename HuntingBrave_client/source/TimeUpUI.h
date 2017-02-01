
#pragma once

//***************************************************************
//
//	TimeUpUIクラス
//
//***************************************************************



namespace TIMEUP_MAX
{
	enum
	{
		WIDTH = 512,
		HEIGHT = 512,
	};
}


//	class
class TimeUpUI
{
private:
	Image* obj;
	Image* obj_wave;
	int	posx, posy, width, height;
	bool flag;

public:
	//	初期化・解放
	TimeUpUI();
	~TimeUpUI(void);

	//	更新・描画
	bool	Update(void);
	void	TimeUpManager(void);
	void	Render(void);
};

