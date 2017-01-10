
#pragma once

//*************************************************************************
//
//	DefenseItem構造体
//
//*************************************************************************

//	include
#include	"Item.h"

//	class
class DefenseItem : public Item
{
private:

public:
	//	初期化・解放
	DefenseItem( int id );
	~DefenseItem( void )override;

	//	更新
	void	Update( void )override;

	//	動作関数
	void	UseItem( void )override;
};
