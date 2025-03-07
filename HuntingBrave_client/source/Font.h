
#pragma once

//***************************************************************
//
//	Fontクラス
//
//***************************************************************

//	include

//	class
class Font
{
private:
	LPD3DXFONT	gFont;

public:
	//	初期化・解放
	Font( char* fontName, UINT fontSize );
	~Font( void );

	//	描画
	void	DrawFont( char* str, int x, int y, int width, int height, DWORD color);
};
