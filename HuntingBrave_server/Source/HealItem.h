
#pragma once

//*************************************************************************
//
//	HealItem�\����
//
//*************************************************************************

//	include
#include	"Item.h"

//	class
class HealItem : public Item
{
private:

public:
	//	�������E���
	HealItem( int id );
	~HealItem( void )override;

	//	�X�V
	void	Update( void )override;

	//	����֐�
	void	UseItem( void )override;
};
