
#pragma once

//***************************************************************
//
//	Font�N���X
//
//***************************************************************

//	include

//	class
class Font
{
private:
	LPD3DXFONT	gFont;

public:
	//	�������E���
	Font( char* fontName );
	~Font( void );

	//	�`��
	void	DrawFont( char* str, int x, int y, int width, int height, DWORD color);
};
