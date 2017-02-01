
#pragma once

//*****************************************************************************************************************************
//
//	ItemManagerクラス
//
//*****************************************************************************************************************************

//	include
#include	"HealItem.h"
#include	"SpeedItem.h"
#include	"AttackItem.h"
#include	"DefenseItem.h"

//	class
class ItemManager
{
public:
	struct ItemState
	{
		Item*	leftItem;
		Item*	rightItem;
	};

	enum ITEM_TYPE
	{
		HEAL,
		ATK,
		DEF,
		SPEED,
		TYPE_MAX,
		SET_ITEM
	};

	enum ITEM_POS
	{
		LEFT_ITEM,
		RIGHT_ITEM,
		ITEM_MAX
	};

private:
	ItemState		itemState[PLAYER_MAX];

public:
	//	初期化・解放
	ItemManager( void );
	~ItemManager( void );
	bool	Initialize( void );
	void	Release( void );

	//	更新
	void	Update( void );

	//	情報設定
	void	ReceiveData( int id, const LPSTR& data );
	void	ChangeItemState( int id, char itemType );
	void	AddItemState( int id, const LPSTR& data );
	void	SetItem( int id, Item*& item, char itemType );

	//	情報取得
};

extern	ItemManager*	itemManager;
