
#pragma once

//***************************************************************
//
//	MapUI�N���X
//
//***************************************************************

namespace MAP_MAX
{
	enum
	{
		WIDTH = 512,				//	�摜����
		HEIGHT = 512,				//	�摜�c��
	};
}


//	class
class MapUI
{
private:
	Image*	obj;
	int	posx, posy, width, height;

public:
	//	�������E���
	MapUI(int x, int y, int w, int h);
	~MapUI(void);

	//	�X�V�E�`��
	void	Update(void);
	void	Render(void);
};

