
#pragma once

//***************************************************************
//
//	TimerUI�N���X
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
	NumberUI*	number[2];	//	min�Asecond
	float	timer;
	int		color;
	int		posx, posy, size;

public:
	//	�������E���
	TimerUI(int x, int y, int w, int h);
	~TimerUI(void);

	//	�X�V�E�`��
	void	Update(void);
	void	Render(void);
};

