
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
	Font( char* fontName, UINT fontSize );
	~Font( void );

	//	�`��
	void	DrawFont( char* str, int x, int y, int width, int height, DWORD color);
};
