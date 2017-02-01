
#pragma once

//***************************************************************
//
//	TimeUpUI�N���X
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
	//	�������E���
	TimeUpUI();
	~TimeUpUI(void);

	//	�X�V�E�`��
	bool	Update(void);
	void	TimeUpManager(void);
	void	Render(void);
};

