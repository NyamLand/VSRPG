
#pragma once

//*************************************************************************
//
//	AttackItem構造体
//
//*************************************************************************

//	include
#include	"Item.h"

//	class
class AttackItem : public Item
{
private:

public:
	//	初期化・解放
	AttackItem( int id );
	~AttackItem( void )override;

	//	更新
	void	Update( void )override;

	//	動作関数
	void	UseItem( void )override;
};
