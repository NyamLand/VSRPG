
#pragma once

//***************************************************************
//
//	ScoreUI�N���X
//
//***************************************************************



#include	"GameData.h"
#include	"ScoreUI.h"
#include	"ExpUI.h"

namespace BOARD_MAX
{
	enum
	{
		BOARD_WIDTH = 1280,		//	�摜��
		BOARD_HEIGHT = 720,		//	�摜����
		BOARD_MARGIN = 100,		//	�摜�]������
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
	//	�������E���
	ScoreBoardUI(int x, int y, int w, int h);
	~ScoreBoardUI(void);

	//	�X�V�E�`��
	void	Update(void);
	void	Render(void);
};

