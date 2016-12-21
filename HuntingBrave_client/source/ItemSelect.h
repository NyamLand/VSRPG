
#pragma once

//***************************************************************
//
//	ItemSelectクラス
//
//***************************************************************

//	include
#include	"Image.h"

//	class
class ItemSelect
{
private:
	int	posX, posY;
	int	select1, select2, before;
	float	percentage;
	float	percentage1;
	float	percentage2;
	float	circleGage;
	Image*		itemImage[4];

public:
	//	初期化・開放
	ItemSelect( void );
	~ItemSelect( void );
	bool	Initialize( int id );

	//	更新・描画
	void	Update( void );
	void	Render( void );
	
	//	動作関数

};
