
#pragma once

//*****************************************************************************************************************************
//
//	ItemManagerクラス
//
//*****************************************************************************************************************************

//	include

//	class
class ItemManager
{
private:
	enum ITEM_TYPE
	{
		HEAL,
		ATK,
		DEF,
		LED
	};
	std::map<char, bool>	itemMap[PLAYER_MAX];

public:
	//	初期化・解放
	ItemManager( void );
	~ItemManager( void );
	bool	Initialize( void );
	void	Release( void );

	//	情報設定
	void	ChangeItemState( int id, char itemType );
	void	AddItemState( int id, char itemType );

	//	アイテム効果
	void	Heal( int id );
	void	Power( int id );
	void	Defense( int id );

	//	情報取得
	bool	GetItemState( int id, char itemType );
};

extern	ItemManager*	itemManager;
