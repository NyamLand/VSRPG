
#pragma once

//*************************************************************************
//
//	LedItem�\����
//
//*************************************************************************

//	include
#include	"Item.h"

//	class
class LedItem : public Item
{
private:

public:
	//	�������E���
	LedItem( int id );
	~LedItem( void )override;

	//	�X�V
	void	Update( void )override;

	//	����֐�
	void	UseItem( void )override;
};
