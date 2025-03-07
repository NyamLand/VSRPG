
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
	bool	Initialize( int x, int y, int w, int h );

	//	更新・描画
	void	Update( int* name );
	void	Render( void );
	void	NormalCharacterSet( int* name, int index );
	void	VoicedSpotCharacterSet( int* name, int index );

	//	情報設定
	void	SetPos( int posx, int posy );
	void	SetSpace( int space );
};
