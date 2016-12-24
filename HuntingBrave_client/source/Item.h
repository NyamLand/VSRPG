
#pragma once

//**********************************************************************
//
//	Interpolationクラス
//
//**********************************************************************

//	include
#include	"Timer.h"
#include	"Image.h"

//	class
class Item
{
protected:
	Image*		itemImage;
	Timer*		timer;
	int posX, posY;
	float	percentage;
	bool	itemState;

public:
	//	初期化・解放
	Item( void );
	~Item( void );
	bool	Initialize( void );
	
	//	更新・描画
	void	Update( void );
	void	Render( void );

	//	情報設定
	void	UseItem( void );
	void	SendItemStatus( void );
	
	//	情報取得
	
};
