
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"Image.h"
#include	<vector>
#include	"NumberUI.h"
#include	"ExpUI.h"
#include	<math.h>

//***************************************************************
//
//	ExpUI�N���X
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	�O���[�o��	
//---------------------------------------------------------------------------------------

namespace
{
	const int NEED_EXP_SRC_POS_Y = 256;
	const int NEED_EXP_SRC_WIDTH = 256;
	const int NEED_EXP_SRC_HEIGHT = 128;
}

//---------------------------------------------------------------------------------------
//	�������E���
//---------------------------------------------------------------------------------------

//	�R���X�g���N�^
ExpUI::ExpUI(int x, int y, int w, int h)
{
	//	���W�A�T�C�Y���i�[
	size = w;	posx = x;	posy = y;

	//	EXP�����A�C�R��
	icon = new Image();
	icon->Initialize("DATA/UI/main_UI/ExpIcon.png", posx, posy, size, size, 0, 0, EXP_MAX::ICON_SIZE, EXP_MAX::ICON_SIZE);

	//	�o���l�̒l
	number = new NumberUI(x, y, w / 2, h, EXP_DIGIT);
}

//	�f�X�g���N�^
ExpUI::~ExpUI(void)
{
	SafeDelete( icon );
	SafeDelete( number );
}



//---------------------------------------------------------------------------------------
//	�X�V
//---------------------------------------------------------------------------------------

//	�X�V
void	ExpUI::Update(void)
{
	number->SetColor(NUM_COLOR::GREEN);
	number->Update(icon);
	
}

//---------------------------------------------------------------------------------------
//	�`��
//---------------------------------------------------------------------------------------

//	�`��
void	ExpUI::Render(void)
{
	icon->Render(IMAGE_MODE::ADOPTPARAM);

	number->Render();
}

//---------------------------------------------------------------------------------------
//	����֐�
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	���ݒ�
//---------------------------------------------------------------------------------------
void	ExpUI::SetParam(int x, int y, int w, int h)
{
	size = w;
	posx = x;
	posy = y;	//	height / 6 = �A�C�R���T�C�Y��1/6���]�����󂯂�

	//	SCORE�����A�C�R��
	icon->x = x;	icon->y = y;	icon->w = w;	icon->h = h;

	number->SetParam(x, y, w / 2, h);

}

void	ExpUI::SetRenderFlag(bool c)
{
	icon->renderflag = c;
	number->SetRenderFlag(c);
}

void	ExpUI::SetExp(int e)
{
	number->SetNum(e);
}

//***************************************************************
//
//	NeedExpUI�N���X
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	�������E���
//---------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	NeedExpUI::NeedExpUI( int x, int y, int w, int h ) : ExpUI( x, y, w, h )
	{
		//	���W�A�T�C�Y���i�[
		size = w;	posx = x;	posy = y;

		//	EXP�����A�C�R��
		icon = new Image();
		icon->Initialize( "DATA/UI/BackGround/Upgrade_UIparts.png", posx, posy, size, size, 
			0, NEED_EXP_SRC_POS_Y, 
			NEED_EXP_SRC_WIDTH, NEED_EXP_SRC_HEIGHT );

		//	�o���l�̒l
		number = new NumberUI( x, y, w / 2, h, EXP_DIGIT );
	}

	NeedExpUI::~NeedExpUI( void )
	{

	}