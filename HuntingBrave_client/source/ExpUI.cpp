
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"Image.h"
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

//---------------------------------------------------------------------------------------
//	�������E���
//---------------------------------------------------------------------------------------

//	�R���X�g���N�^
ExpUI::ExpUI(int x, int y, int w, int h)
{
	//	���W�A�T�C�Y���i�[
	size = w / 6;
	posx = x;
	posy = y - h / 2 - size / 6;	//	height / 6 = �A�C�R���T�C�Y��1/6���]�����󂯂�

	//	EXP�����A�C�R��
	icon = new Image();
	icon->Initialize("DATA/UI/main_UI/ExpIcon.png", posx, posy, size, size, 0, 0, EXP_MAX::ICON_SIZE, EXP_MAX::ICON_SIZE);

	//	�o���l�̒l
	for (int i = 0; i < EXP_MAX::DIGIT_MAX; i++)
	{
		number[i] = new Image();
		number[i]->Initialize("DATA/UI/main_UI/Number.png", 0, 0, 0, 0, 0, 0, 0, 0);	//	������
	}
	exp = 9456;
}

//	�f�X�g���N�^
ExpUI::~ExpUI(void)
{
	SafeDelete( icon );
	for (int i = 0; i < EXP_MAX::DIGIT_MAX; i++)
	{
		SafeDelete( number[i] );
	}
}



//---------------------------------------------------------------------------------------
//	�X�V�E�`��
//---------------------------------------------------------------------------------------

//	�X�V
void	ExpUI::Update(void)
{
	ExpManager();
}

void	ExpUI::ExpManager(void)
{

	//	�������̓��ꕨ��p��(������)
	int numbox[EXP_MAX::DIGIT_MAX];
	int	digit = (int)log10((float)exp) + 1;				//	����
	for (int i = 0; i < EXP_MAX::DIGIT_MAX; i++)
	{
		numbox[i] = -1;
	}

	//	�����A�ő包���𒴂����l�̏ꍇ�ő包���̍ő吔��\��
	if (EXP_MAX::DIGIT_MAX < digit)
	{
		for (int i = 0; i < EXP_MAX::DIGIT_MAX; i++)
		{
			numbox[i] = 9;
		}
		return;
	}

	for (int i = 0; i < digit; i++)
	{
		int n = 10;	//	�ׂ���v�Z�p
		for (int j = digit - 2; j > i; j--){		//	-2�ׂ͂���v�Z�̂��߂Ɍ��炵�Ă���
			n *= 10;
		}
		numbox[i] = exp / n;
	}

	char str[64];
	for (int i = 0; i < EXP_MAX::DIGIT_MAX; i++){
		sprintf_s(str, "number = %f", numbox[i]);
		IEX_DrawText(str, 20, 100 + 20 * i, 400, 100, 0xFF00FF00);
	}
	
}

//	�`��
void	ExpUI::Render(void)
{
	icon->Render(IMAGE_MODE::ADOPTPARAM);

}

//---------------------------------------------------------------------------------------
//	����֐�
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	���ݒ�
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	���擾
//---------------------------------------------------------------------------------------

