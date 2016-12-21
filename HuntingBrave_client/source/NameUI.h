
#pragma once

//***************************************************************
//
//	NameUIクラス
//
//***************************************************************

//	include
#include	"Image.h"

//	class
class NameUI
{
private:
	Image*		nameImage[NAME_MAX];
	int	posX, posY;
	int	scale;
	int	space;

public:
	//	初期化・解放
	NameUI( void );
	~NameUI( void );
	bool	Initialize( int x, int y, int w, int h, int* name );

	//	更新・描画
	void	Update( void );
	void	Render( void );

	//	情報設定
	void	SetPos( int posx, int posy );
	void	SetSpace( int space );
};
