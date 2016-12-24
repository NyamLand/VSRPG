
#pragma once

//**********************************************************************
//
//	Interpolation�N���X
//
//**********************************************************************

//	include
#include	"Timer.h"
#include	"Image.h"

//	class
class Item
{
protected:
	Image*		itemImage;
	Timer*		timer;
	int posX, posY;
	float	percentage;
	bool	itemState;

public:
	//	�������E���
	Item( void );
	~Item( void );
	bool	Initialize( void );
	
	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );

	//	���ݒ�
	void	UseItem( void );
	void	SendItemStatus( void );
	
	//	���擾
	
};
