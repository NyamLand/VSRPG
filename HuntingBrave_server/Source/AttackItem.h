
#pragma once

//*************************************************************************
//
//	AttackItem�\����
//
//*************************************************************************

//	include
#include	"Item.h"

//	class
class AttackItem : public Item
{
private:

public:
	//	�������E���
	~AttackItem( void )override;

	//	�X�V
	void	Update( void )override;

	//	����֐�
	void	UseItem( void )override;
};
