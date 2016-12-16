
#pragma once

//***************************************************************
//
//	ScoreUI�N���X
//
//***************************************************************

namespace SCORE_MAX
{
	enum
	{
		ICON_SIZE = 64,				//	�摜��
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
	//	�������E���
	ScoreUI(int x, int y, int w, int h);
	~ScoreUI(void);

	//	�X�V�E�`��
	void	Update(void);
	void	ScoreManager(void);
	void	SetParam(int x, int y, int w, int h);
	void	SetRenderFlag(bool c);
	void	SetScore(int s);
	void	NumberSet(Image* img, const int num, const int digit);
	void	Render(void);
};

