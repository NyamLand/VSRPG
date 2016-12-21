
#pragma once

//***************************************************************
//
//	ItemSelect�N���X
//
//***************************************************************

//	include
#include	"Image.h"

//	class
class ItemSelect
{
private:
	int	posX, posY;
	int	select1, select2, before;
	float	percentage;
	float	percentage1;
	float	percentage2;
	float	circleGage;
	Image*		itemImage[4];

public:
	//	�������E�J��
	ItemSelect( void );
	~ItemSelect( void );
	bool	Initialize( int id );

	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );
	
	//	����֐�

};
