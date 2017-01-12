
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"Image.h"
#include	<vector>
#include	"NumberUI.h"
#include	"ScoreUI.h"
#include	<math.h>

//***************************************************************
//
//	ScoreUI�N���X
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	�O���[�o��	
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	�������E���
//---------------------------------------------------------------------------------------

//	�R���X�g���N�^
ScoreUI::ScoreUI(int x, int y, int w, int h)
{
	//	���W�A�T�C�Y���i�[
	size = w;	posx = x;	posy = y;

	//	SCORE�����A�C�R��
	icon = new Image();
	icon->Initialize("DATA/UI/main_UI/BigHuntIcon.png", posx, posy, size, size, 0, 0, SCORE_MAX::ICON_SIZE, SCORE_MAX::ICON_SIZE);

	//	�o���l�̒l
	number = new NumberUI(x, y, w / 2 , h, SCORE_DIGIT);


}

//	�f�X�g���N�^
ScoreUI::~ScoreUI(void)
{
	SafeDelete( icon );
	SafeDelete( number );
}



//---------------------------------------------------------------------------------------
//	�X�V
//---------------------------------------------------------------------------------------

//	�X�V
void	ScoreUI::Update(void)
{
	number->SetColor(1.0f, 0.6f, 0.0f);
	number->Update(icon);

}

//---------------------------------------------------------------------------------------
//	�`��
//---------------------------------------------------------------------------------------

//	�`��
void	ScoreUI::Render(void)
{
	icon->Render(IMAGE_MODE::ADOPTPARAM);

	number->Render();
}


//---------------------------------------------------------------------------------------
//	���ݒ�
//---------------------------------------------------------------------------------------
void	ScoreUI::SetParam(int x, int y, int w, int h)
{
	size = w;
	posx = x;
	posy = y;	//	height / 6 = �A�C�R���T�C�Y��1/6���]�����󂯂�

	//	SCORE�����A�C�R��
	icon->x = x;	icon->y = y;	icon->w = w;	icon->h = h;

	number->SetParam(x, y, w / 2, h);

}

void	ScoreUI::SetRenderFlag(bool c)
{
	icon->renderflag = c;
	number->SetRenderFlag(c);
}

void	ScoreUI::SetScore(int s)
{
	number->SetNum(s);
}
//---------------------------------------------------------------------------------------
//	���擾
//---------------------------------------------------------------------------------------

