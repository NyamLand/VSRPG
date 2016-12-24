
#pragma once

//**********************************************************************
//
//	Interpolationクラス
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

	//	初期化・解放
	ItemManager( void );
	~ItemManager( void );

public:
	bool Initialize( char itemType1, char itemType2 );

	//	更新・描画
	void	Update( void );

	//	動作関数
	void	SendItemState( char item );
	void	UseItem( char itemPos );

	//	情報設定
	
	//	情報取得
	char	GetItemType( char itemPos )const{ return item[itemPos].type; }
	float GetInterval( char itemPos )const{ return item[itemPos].percentage; }
};

#define	itemManager ( ItemManager::GetInstance() )