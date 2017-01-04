
#pragma once

//*****************************************************************************************************************************
//
//	ItemManager�N���X
//
//*****************************************************************************************************************************

//	include
#include	"Item.h"

//	class
class ItemManager
{
private:
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
		LED,
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
	//	�������E���
	ItemManager( void );
	~ItemManager( void );
	bool	Initialize( void );
	void	Release( void );

	//	���ݒ�
	void	ChangeItemState( int id, char itemType );
	void	AddItemState( int id, char leftItem, char rightItem );
	void	SetItem( Item* item, char itemType );

	//	�A�C�e������
	void	Heal( int id );
	void	Power( int id );
	void	Defense( int id );

	//	���擾
	bool	GetItemState( int id, char itemType );
};

extern	ItemManager*	itemManager;
