
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"Image.h"
#include	<vector>
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
NumberUI::NumberUI(int x, int y, int w, int h, int digit)
{
	//	���W�A�T�C�Y���i�[
	size = w;
	posx = x;
	posy = y;	//	height / 6 = �A�C�R���T�C�Y��1/6���]�����󂯂�
	number.clear();
	numbox.clear();

	number.resize(digit);
	numbox.resize(digit);

	DIGIT_MAX = digit;
	slide_state = true;
	//	�o���l�̒l
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		number[i] = new Image();
		number[i]->Initialize("DATA/UI/main_UI/Number.png", posx, posy, size, size, 0, 0, 0, 0);	//	������

		numbox[i] = -1;
	}
	num = 0;
	digit = 0;
	color = NUM_COLOR::WHITE;
}

//	�f�X�g���N�^
NumberUI::~NumberUI(void)
{
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		SafeDelete(number[i]);
	}
}



//---------------------------------------------------------------------------------------
//	�X�V
//---------------------------------------------------------------------------------------

//	�X�V
void	NumberUI::Update(const Image* icon)
{
	//	�o���l��1�����ɕ�����
	NumberManager();

	//	�e�l�ɍ��킹���p�����[�^������
	//	�A�C�R������
	if (icon != null)
	{
		for (int i = 0; i < DIGIT_MAX; i++){
			NumberSet(number[i], numbox[i], i, icon, color);
		}
	}
	//	�A�C�R���Ȃ�
	else
	{
		for (int i = 0; i < DIGIT_MAX; i++){
			NumberSet(number[i], numbox[i], i, color);
		}
	}

}

//---------------------------------------------------------------------------------------
//	����֐�
//---------------------------------------------------------------------------------------

//	�o���l�̒l�����֐�
void	NumberUI::NumberManager(void)
{

	//	�������̓��ꕨ��p��(������)
	digit = (int)log10((float)num) + 1;				//	����
	if (num == 0) digit = 1;
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		numbox[i] = -1;
	}

	if (!slide_state)	digit = DIGIT_MAX;
	//-------------------------------------------------------
	//	�����A�ő包���𒴂����l�̏ꍇ�ő包���̍ő吔��\��
	//-------------------------------------------------------
	if (DIGIT_MAX < digit)
	{
		for (int i = 0; i < DIGIT_MAX; i++)
		{
			numbox[i] = 9;
		}
		return;
	}
	//-------------------------------------------------------


	for (int i = 0; i < digit; i++)
	{
		int n = 10;	//	�ׂ���v�Z�p
		for (int j = digit - 2; j > i; j--){		//	-2�ׂ͂���v�Z�̂��߂Ɍ��炵�Ă���
			n *= 10;
		}

		//-------------------------
		//	1�̈ʂ̎��̂�
		//-------------------------
		if (i == digit - 1)
		{
			numbox[i] = num % 10;
			continue;
		}

		//-------------------------
		//	���̑��̈�
		//-------------------------
		numbox[i] = num / n % 10;
	}

}

//	�A�C�R������
void	NumberUI::NumberSet(Image* img, const int num, const int digit, const Image* icon, int color)
{
	//	0�`9�ȊO�̒l�̏ꍇ��΂��B
	if (num < 0 || num > 9)
	{
		img->renderflag = false;
		return;
	}

	//	�����ɑΉ������z�u
	img->w = size;	img->h = size;
	img->x = icon->x + icon->w / 2 + img->w / 2 + (img->w * digit); // �A�C�R���̉E�̈ʒu����T�C�Y�̔���*���ŏꏊ���Ƃ�
	img->y = posy;

	//	���l�ɑΉ������؂���͈͎w��
	img->sx = num * 64;	img->sy = 64 * color;
	img->sw = 64;		img->sh = 64;
	
	img->renderflag = true;
}

//	�A�C�R���Ȃ�
void	NumberUI::NumberSet(Image* img, const int num, const int digit, int color)
{
	//	0�`9�ȊO�̒l�̏ꍇ��΂��B
	if (num < 0 || num > 9)
	{
		img->renderflag = false;
		return;
	}

	//	�����ɑΉ������z�u
	img->w = size;	img->h = size;
	img->x = posx + img->w / 2 + (img->w * digit);
	img->y = posy;

	//	���l�ɑΉ������؂���͈͎w��
	img->sx = num * 64;	img->sy = 64 * color;
	img->sw = 64;		img->sh = 64;

	img->renderflag = true;
}

//---------------------------------------------------------------------------------------
//	�`��
//---------------------------------------------------------------------------------------

void	NumberUI::Render(int mode)
{

	for (int i = 0; i < DIGIT_MAX; i++)
	{
		number[i]->Render(mode);
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

}

void	NumberUI::SetRenderFlag(bool c)
{
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		number[i]->renderflag = c;
	}
}

void	NumberUI::SetNum(int n)
{
	num = n;
}

void	NumberUI::SetColor(int c)
{
	color = c;
}

void	NumberUI::SetSlide(bool state)
{
	slide_state = state;
}

Image*	NumberUI::GetNumber(int num)
{
	return number[num];
}

void	NumberUI::SetColor(float r, float g, float b)
{
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		number[i]->color = Vector3(r, g, b);
	}
}

//---------------------------------------------------------------------------------------
//	���擾
//---------------------------------------------------------------------------------------

