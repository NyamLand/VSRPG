
#pragma once

//*************************************************************************
//
//	DefenseItem�\����
//
//*************************************************************************

//	include
#include	"Item.h"

//	class
class DefenseItem : public Item
{
private:

public:
	//	�������E���
	~DefenseItem( void )override;

	//	�X�V
	void	Update( void )override;

	//	����֐�
	void	UseItem( void )override;
};
