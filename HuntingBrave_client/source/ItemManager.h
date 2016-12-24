
#pragma once

//**********************************************************************
//
//	Interpolation�N���X
//
//**********************************************************************

//	include
#include	"Timer.h"
#include	"Singleton.h"

struct ItemInfo
{
	char type;
	bool	state;
	float percentage;
};

//	class
class ItemManager : public Singleton<ItemManager>
{
	friend Singleton<ItemManager>;

private:
	enum ITEM_POS
	{
		LEFT_ITEM,
		RIGHT_ITEM,
		ITEM_MAX
	};

	enum ITEM_TYPE
	{
		HEAL,
		ATK,
		DEF,
		LED,
		TYPE_MAX
	};

	ItemInfo	item[ITEM_MAX];

	//	�������E���
	ItemManager( void );
	~ItemManager( void );

public:
	bool Initialize( char itemType1, char itemType2 );

	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );

	//	����֐�
	void	SendItemState( char item );
	void	UseItem( ITEM_POS itemPos );

	//	���ݒ�
	
	//	���擾
	float GetInterval( ITEM_POS itemPos )const{ return item[itemPos].percentage; }
};
