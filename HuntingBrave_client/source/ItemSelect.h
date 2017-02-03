
#pragma once

//***************************************************************
//
//	ItemSelectクラス
//
//***************************************************************

//	include
#include	"ItemManager.h"
#include	"Image.h"

//	class
class ItemSelect
{
private:
	//	構造体
	struct ItemIcon
	{
		bool checkState;
		Image*		itemImage;
	};

	struct Result
	{
		bool checkState;
		Image*		resultImage;
		int Width, Height;
	};

private:
	//	パラメータ
	int	posX, posY;
	int	select, before;
	int	itemPos;
	float	percentage;
	float	percentage1;
	float	percentage2;
	ItemIcon		itemIcon[ITEM_TYPE::TYPE_MAX];
	Result			result;
	Image*			checkImage[ITEM_TYPE::TYPE_MAX];
	char				selectItem[ITEM_POS::ITEM_MAX];

public:
	//	初期化・開放
	ItemSelect( void );
	~ItemSelect(void);
	bool	Initialize();
	bool	Initialize( int id );

	//	更新・描画
	bool	Update( void );
	void	Render( void );

	//	動作関数
	bool	OpenItem( void );
	void	MoveCursor( void );
	bool	MoveInterpolation( void );
	bool	Dicision( void );
	bool	ResultCheck(void);
};
