
#pragma once

//***************************************************************
//
//	ItemUI�N���X
//
//***************************************************************

namespace ITEM_MAX
{
	enum
	{
		WIDTH = 512,				//	�摜����
		HEIGHT = 256,				//	�摜�c��
		SPX	= 0,
		SPY = 256 * 3,
	};
}


//	class
class ItemUI
{
private:
	Image*		obj;
	Image*		icon[2];
	int	posx, posy, width, height;
	float	itemInterval[2];

public:
	//	�������E���
	ItemUI(int x, int y, int w, int h);
	~ItemUI(void);

	//	�X�V�E�`��
	void	Update(void);
	void	Render(void);
};

