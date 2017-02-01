
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"Image.h"
#include	<vector>
#include	"NumberUI.h"
#include	"TimerUI.h"

//***************************************************************
//
//	TimerUI�N���X
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	�O���[�o��	
//---------------------------------------------------------------------------------------
//	include
#define	TIME_DIGIT	2
//---------------------------------------------------------------------------------------
//	�������E���
//---------------------------------------------------------------------------------------

//	�R���X�g���N�^
TimerUI::TimerUI(int x, int y, int w, int h)
{
	//	���W�A�T�C�Y���i�[
	size = w;
	posx = x;
	posy = y;	//	height / 6 = �A�C�R���T�C�Y��1/6���]�����󂯂�
	color = NUM_COLOR::WHITE;

	//	�^�C�}�[�̒l
	number[TIME::MIN] = new NumberUI(x - (size * 2.5f), y, w, h, TIME_DIGIT);
	number[TIME::SECOND] = new NumberUI(x + (size * 0.5f) , y, w, h, TIME_DIGIT);
	number[TIME::MIN]->SetSlide(false);
	number[TIME::SECOND]->SetSlide(false);

	period = new Image();
	period->Initialize("DATA/UI/main_UI/Number.png", posx, posy, size, size, 64 * 10, 64 * color , 64, 64);

	//	���o�p�^�C�}�[
	number_wave[TIME::MIN] = new NumberUI(x - (size * 2.5f), y, w, h, TIME_DIGIT);
	number_wave[TIME::SECOND] = new NumberUI(x + (size * 0.5f), y, w, h, TIME_DIGIT);
	number_wave[TIME::MIN]->SetSlide(false);
	number_wave[TIME::SECOND]->SetSlide(false);

	period_wave = new Image();
	period_wave->Initialize("DATA/UI/main_UI/Number.png", posx, posy, size, size, 64 * 10, 64 * color, 64, 64);
}

//	�f�X�g���N�^
TimerUI::~TimerUI(void)
{

}



//---------------------------------------------------------------------------------------
//	�X�V�E�`��
//---------------------------------------------------------------------------------------

//	�X�V
void	TimerUI::Update(void)
{
	timer = gameManager->GetTime();

	number[TIME::MIN]->SetNum(timer / 60);
	number[TIME::SECOND]->SetNum((int)timer % 60);

	number[TIME::MIN]->Update();
	number[TIME::SECOND]->Update();

	//	30�b�؂��Ă���̉��o
	if (timer > 30) return;

	

	for (int i = 0; i < TIME_DIGIT; i++){
		number_wave[TIME::MIN]->GetNumber(i)->SetWave(0.017f);
		number_wave[TIME::MIN]->GetNumber(i)->WaveUpdate(32, 1.0f);

		number_wave[TIME::SECOND]->GetNumber(i)->SetWave(0.017f);
		number_wave[TIME::SECOND]->GetNumber(i)->WaveUpdate(32, 1.0f);
	}
	period_wave->SetWave(0.017f);
	period_wave->WaveUpdate(32, 1.0f);

	number_wave[TIME::MIN]->SetNum(timer / 60);
	number_wave[TIME::SECOND]->SetNum((int)timer % 60);

	number_wave[TIME::MIN]->Update();
	number_wave[TIME::SECOND]->Update();
}

//	�`��
void	TimerUI::Render(void)
{
	char str[64];
	sprintf_s( str, "timer = %f�b",timer );
	IEX_DrawText( str, 600, 100, 400, 100, 0xFF00FF00 );

	period->Render(IMAGE_MODE::ADOPTPARAM);
	number[TIME::MIN]->Render();
	number[TIME::SECOND]->Render();

	if (timer > 30) return;
	period_wave->Render(IMAGE_MODE::WAVE);
	number_wave[TIME::MIN]->Render(IMAGE_MODE::WAVE);
	number_wave[TIME::SECOND]->Render(IMAGE_MODE::WAVE);

	//time_obj->Render( IMAGE_MODE::FLASH );
}

//--------------------------------------------------------------------------------------
//	����֐�-
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	���ݒ�
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	���擾
//---------------------------------------------------------------------------------------

