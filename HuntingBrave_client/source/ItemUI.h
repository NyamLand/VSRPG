
#pragma once

//***************************************************************
//
//	ItemUI�N���X
//
//***************************************************************

//	include
#include	"ItemManager.h"

//	class
class ItemUI
{
private:
	Image*		obj;
	Image*		icon[ITEM_POS::ITEM_MAX];
	int	posx, posy, width, height;
	float	itemInterval[ITEM_POS::ITEM_MAX];

public:
	//	�������E���
	ItemUI(int x, int y, int w, int h);
	~ItemUI(void);

	void	IconInitialize( void );

	//	�X�V�E�`��
	void	Update(void);
	void	Render(void);
};

