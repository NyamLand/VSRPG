
#pragma once

//***************************************************************
//
//	FontƒNƒ‰ƒX
//
//***************************************************************

//	include

//	class
class Font
{
private:
	LPD3DXFONT	gFont;

public:
	//	‰Šú‰»E‰ğ•ú
	Font( char* fontName );
	~Font( void );

	//	•`‰æ
	void	DrawFont( char* str, int x, int y, int width, int height, DWORD color);
};
