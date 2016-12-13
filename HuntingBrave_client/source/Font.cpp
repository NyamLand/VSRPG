
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"Font.h"

//***************************************************************
//
//	Fontクラス
//
//***************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	Font::Font( char* fontName )
	{
		UINT	fontWidth		=	50;
		UINT	fontHeight	=	60;
		UINT	fontWeight	=	15;
		UINT	mipLevels		=	1;

		D3DXCreateFont(
			iexSystem::Device,								//	デバイス
			fontHeight,											//	フォント高さ
			0,															//	文字幅
			fontWeight,											//	文字太さ
			mipLevels,											//	ミップマップレベル
			FALSE,													//	イタリック
			SHIFTJIS_CHARSET,							//	文字セット
			OUT_DEFAULT_PRECIS,						//	出力精度
			DEFAULT_QUALITY,								//	出力品質
			DEFAULT_PITCH | FF_DONTCARE,		//	ピッチとファミリー
			fontName,											//	書体名
			&gFont );												//	出力
	}

	//	デストラクタ
	Font::~Font( void )
	{
		gFont->Release();
	}

//----------------------------------------------------------------------------------------------
//	描画
//----------------------------------------------------------------------------------------------

	//	描画
	void	Font::DrawFont( char* str, int x, int y, int width, int height, DWORD color )
	{
		RECT	rect;
		rect.left = x;
		rect.top = y;
		rect.right = x + width;
		rect.bottom = y = height;

		gFont->DrawTextA( NULL, str, -1, &rect, DT_LEFT, color );
	}
