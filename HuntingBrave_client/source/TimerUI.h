
#pragma once

//***************************************************************
//
//	TimerUI�N���X
//
//***************************************************************

//	include

//	class
class TimerUI
{
private:
	int		timer;
	Image* time_obj;

public:
	//	�������E���
	TimerUI(void);
	~TimerUI(void);

	//	�X�V�E�`��
	void	Update(void);
	void	Render(void);
};

