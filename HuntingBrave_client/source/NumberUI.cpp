
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"Image.h"
#include	"NumberUI.h"
#include	<math.h>

//***************************************************************
//
//	NumberUI�N���X
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	�O���[�o��	
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	�������E���
//---------------------------------------------------------------------------------------

//	�R���X�g���N�^
NumberUI::NumberUI(int x, int y, int w, int h)
{
	//	���W�A�T�C�Y���i�[
	size = w;
	posx = x;
	posy = y;	//	height / 6 = �A�C�R���T�C�Y��1/6���]�����󂯂�

	//	SCORE�����A�C�R��
	icon = new Image();
//	icon->Initialize("DATA/UI/main_UI/ExpIcon.png", posx, posy, size, size, 0, 0, SCORE_MAX::ICON_SIZE, SCORE_MAX::ICON_SIZE);

	//	�o���l�̒l
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		number[i] = new Image();
		number[i]->Initialize("DATA/UI/main_UI/Number.png", 0, 0, 0, 0, 0, 0, 0, 0);	//	������

		numbox[i] = -1;
	}
	score = 120;
	score_digit = 0;
}

//	�f�X�g���N�^
NumberUI::~NumberUI(void)
{
	SafeDelete(icon);
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		SafeDelete(number[i]);
	}
}



//---------------------------------------------------------------------------------------
//	�X�V
//---------------------------------------------------------------------------------------

//	�X�V
void	NumberUI::Update(void)
{
	//	�o���l��1�����ɕ�����
	NumberManager();

	//	�e�l�ɍ��킹���p�����[�^������
	for (int i = 0; i < DIGIT_MAX; i++){
		NumberSet(number[i], numbox[i], i);
	}


}

//---------------------------------------------------------------------------------------
//	����֐�
//---------------------------------------------------------------------------------------

//	�o���l�̒l�����֐�
void	NumberUI::NumberManager(void)
{

	//	�������̓��ꕨ��p��(������)
	score_digit = (int)log10((float)score) + 1;				//	����
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		numbox[i] = -1;
	}
	//-------------------------------------------------------
	//	�����A�ő包���𒴂����l�̏ꍇ�ő包���̍ő吔��\��
	//-------------------------------------------------------
	if (DIGIT_MAX < score_digit)
	{
		for (int i = 0; i < DIGIT_MAX; i++)
		{
			numbox[i] = 9;
		}
		return;
	}
	//-------------------------------------------------------


	for (int i = 0; i < score_digit; i++)
	{
		int n = 10;	//	�ׂ���v�Z�p
		for (int j = score_digit - 2; j > i; j--){		//	-2�ׂ͂���v�Z�̂��߂Ɍ��炵�Ă���
			n *= 10;
		}

		//-------------------------
		//	1�̈ʂ̎��̂�
		//-------------------------
		if (i == score_digit - 1)
		{
			numbox[i] = score % 10;
			continue;
		}

		//-------------------------
		//	���̑��̈�
		//-------------------------
		numbox[i] = score / n % 10;
	}

}

void	NumberUI::NumberSet(Image* img, const int num, const int digit)
{
	//	0�`9�ȊO�̒l�̏ꍇ��΂��B
	if (num < 0 || num > 9)
	{
		img->renderflag = false;
		return;
	}

	//	�����ɑΉ������z�u
	img->w = size / 2;	img->h = size / 2;

	img->x = icon->x + icon->w / 2 + img->w / 2 + (img->w * digit);	//	�A�C�R���̉E�̈ʒu����T�C�Y�̔���*���ŏꏊ���Ƃ�
	img->y = icon->y;

	//	���l�ɑΉ������؂���͈͎w��
	img->sx = num * 64;	img->sy = 64 * 1;
	img->sw = 64;		img->sh = 64;
}

//---------------------------------------------------------------------------------------
//	�`��
//---------------------------------------------------------------------------------------

void	NumberUI::Render(void)
{
	icon->Render(IMAGE_MODE::ADOPTPARAM);

	for (int i = 0; i < DIGIT_MAX; i++)
	{
		number[i]->Render(IMAGE_MODE::ADOPTPARAM);
	}
}


//---------------------------------------------------------------------------------------
//	���ݒ�
//---------------------------------------------------------------------------------------
void	NumberUI::SetParam(int x, int y, int w, int h)
{
	size = w;
	posx = x;
	posy = y;	//	height / 6 = �A�C�R���T�C�Y��1/6���]�����󂯂�

	//	SCORE�����A�C�R��
	icon->x = x;	icon->y = y;	icon->w = w;	icon->h = h;

}

void	NumberUI::SetRenderFlag(bool c)
{
	icon->renderflag = c;
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		number[i]->renderflag = c;
	}
}
//---------------------------------------------------------------------------------------
//	���擾
//---------------------------------------------------------------------------------------

