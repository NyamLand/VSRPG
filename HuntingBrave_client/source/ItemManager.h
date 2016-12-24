
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

	//	初期化・解放
	ItemManager( void );
	~ItemManager( void );

public:
	bool Initialize( char itemType1, char itemType2 );

	//	更新・描画
	void	Update( void );
	void	Render( void );

	//	動作関数
	void	SendItemState( char item );
	void	UseItem( ITEM_POS itemPos );

	//	情報設定
	
	//	情報取得
	float GetInterval( ITEM_POS itemPos )const{ return item[itemPos].percentage; }
};
