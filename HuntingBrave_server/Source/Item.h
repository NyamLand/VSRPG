
#pragma once

//*************************************************************************
//
//	Item�\����
//
//*************************************************************************

//	include
#include	"Timer.h"

//	class
class Item
{
protected:
	bool state;
	Timer*	timer;
	int id;

public:
	//	�������E���
	Item( int id );
	virtual	~Item( void );

	//	�X�V
	virtual	void	Update( void ) = 0;
	bool TimerUpdate( void );
	
	//	����֐�
	virtual	void	UseItem( void ) = 0;
};
