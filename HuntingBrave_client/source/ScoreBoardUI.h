
#pragma once

//***************************************************************
//
//	ScoreUIクラス
//
//***************************************************************



#include	"GameData.h"
#include	"ScoreUI.h"
#include	"ExpUI.h"

namespace BOARD_MAX
{
	enum
	{
		BOARD_WIDTH = 1280,		//	画像幅
		BOARD_HEIGHT = 720,		//	画像高さ
		BOARD_MARGIN = 100,		//	画像余白部分
		ICON_SIZE = 64,
	};
}


//	class
class ScoreBoardUI
{
private:
	Image*		board;
	Image*		p_icon[PLAYER_MAX];
	ScoreUI*	score[PLAYER_MAX];
	ExpUI*		exp[PLAYER_MAX];
	int	posx, posy, width,	height;
	bool	boardState;

public:
	//	初期化・解放
	ScoreBoardUI(int x, int y, int w, int h);
	~ScoreBoardUI(void);

	//	更新・描画
	void	Update(void);
	void	Render(void);
};

