
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"Font.h"

//***************************************************************
//
//	Font�N���X
//
//***************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	Font::Font( char* fontName )
	{
		UINT	fontWidth		=	50;
		UINT	fontHeight	=	60;
		UINT	fontWeight	=	15;
		UINT	mipLevels		=	1;

		D3DXCreateFont(
			iexSystem::Device,								//	�f�o�C�X
			fontHeight,											//	�t�H���g����
			0,															//	������
			fontWeight,											//	��������
			mipLevels,											//	�~�b�v�}�b�v���x��
			FALSE,													//	�C�^���b�N
			SHIFTJIS_CHARSET,							//	�����Z�b�g
			OUT_DEFAULT_PRECIS,						//	�o�͐��x
			DEFAULT_QUALITY,								//	�o�͕i��
			DEFAULT_PITCH | FF_DONTCARE,		//	�s�b�`�ƃt�@�~���[
			fontName,											//	���̖�
			&gFont );												//	�o��
	}

	//	�f�X�g���N�^
	Font::~Font( void )
	{
		gFont->Release();
	}

//----------------------------------------------------------------------------------------------
//	�`��
//----------------------------------------------------------------------------------------------

	//	�`��
	void	Font::DrawFont( char* str, int x, int y, int width, int height, DWORD color )
	{
		RECT	rect;
		rect.left = x;
		rect.top = y;
		rect.right = x + width;
		rect.bottom = y = height;

		gFont->DrawTextA( NULL, str, -1, &rect, DT_LEFT, color );
	}
