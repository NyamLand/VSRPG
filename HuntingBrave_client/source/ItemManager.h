
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

namespace
{
	namespace ITEM_POS
	{
		enum
		{
			LEFT_ITEM,
			RIGHT_ITEM,
			ITEM_MAX
		};
	}

	namespace ITEM_TYPE
	{
		enum
		{
			HEAL,
			ATK,
			DEF,
			LED,
			TYPE_MAX
		};
	}
}

//	class
class ItemManager : public Singleton<ItemManager>
{
	friend Singleton<ItemManager>;

public:

private:

	ItemInfo	item[ITEM_POS::ITEM_MAX];

	//	�������E���
	ItemManager( void );
	~ItemManager( void );

public:
	bool Initialize( char itemType1, char itemType2 );

	//	�X�V�E�`��
	void	Update( void );

	//	����֐�
	void	SendItemState( char item );
	void	UseItem( char itemPos );

	//	���ݒ�
	
	//	���擾
	char	GetItemType( char itemPos )const{ return item[itemPos].type; }
	float GetInterval( char itemPos )const{ return item[itemPos].percentage; }
};

#define	itemManager ( ItemManager::GetInstance() )