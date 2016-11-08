
#pragma once

//***************************************************************
//
//	ScoreUIクラス
//
//***************************************************************

namespace HP_MAX
{
	enum
	{
		WIDTH = 1024,				//	画像横幅
		HEIGHT = 256,				//	画像縦幅
	};
}


//	class
class ScoreUI
{
private:
	int	posx, posy, width, height;

public:
	//	初期化・解放
	ScoreUI(void);
	~ScoreUI(void);

	//	更新・描画
	void	Update(void);
	void	Render(void);
};

