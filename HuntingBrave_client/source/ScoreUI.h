
#pragma once

//***************************************************************
//
//	ScoreUI�N���X
//
//***************************************************************

namespace HP_MAX
{
	enum
	{
		WIDTH = 1024,				//	�摜����
		HEIGHT = 256,				//	�摜�c��
	};
}


//	class
class ScoreUI
{
private:
	int	posx, posy, width, height;

public:
	//	�������E���
	ScoreUI(void);
	~ScoreUI(void);

	//	�X�V�E�`��
	void	Update(void);
	void	Render(void);
};

