
#pragma once

//***************************************************************
//
//	PlayerTitleUIクラス
//
//***************************************************************

//	include
#include	"GameData.h"
#include	"Image.h"

//	class
class PlayerTitleUI
{
private:
	int index;
	int front, back;
	int posx, posy;
	Image*	 frontTitleImage;
	Image*	 backTitleImage;

public:
	//	初期化・解放
	PlayerTitleUI( void );
	~PlayerTitleUI( void );
	void	Initialize( int front, int back, int x, int y, int w, int h );

	//	更新
	void	Update( void );

	//	描画
	void	Render( void );

	//	情報設定
	void	SetPos( int x, int y );
	void	SetTitle( int front, int back );
};
