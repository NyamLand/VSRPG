
#pragma once

//*************************************************************************
//
//	LedItem�\����
//
//*************************************************************************

//	include
#include	"Item.h"

//	class
class SpeedItem : public Item
{
private:

public:
	//	�������E���
	SpeedItem( int id );
	~SpeedItem( void )override;

	//	�X�V
	void	Update( void )override;

	//	����֐�
	void	UseItem( void )override;
};
