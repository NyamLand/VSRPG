
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"Image.h"
#include	<vector>
#include	"NumberUI.h"
#include	"TimeUpUI.h"
#include	<math.h>

//***************************************************************
//
//	TimeUpUI�N���X
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	�O���[�o��	
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
//	�������E���
//---------------------------------------------------------------------------------------

//	�R���X�g���N�^
TimeUpUI::TimeUpUI() : flag(false)
{
	//	���W�A�T�C�Y���i�[
	width = TIMEUP_MAX::WIDTH;		height = TIMEUP_MAX::HEIGHT;		posx = iexSystem::ScreenWidth / 2;		posy = iexSystem::ScreenHeight / 2;

	//	SCORE�����A�C�R��
	obj = new Image();
	obj->Initialize("DATA/UI/main_UI/time_up.png", posx, posy, 0, 0, 0, 0, TIMEUP_MAX::WIDTH, TIMEUP_MAX::HEIGHT);

	//	���o�p
	obj_wave = new Image();
	obj_wave->Initialize("DATA/UI/main_UI/time_up.png", posx, posy, width, height, 0, 0, TIMEUP_MAX::WIDTH, TIMEUP_MAX::HEIGHT);



}

//	�f�X�g���N�^
TimeUpUI::~TimeUpUI(void)
{
	SafeDelete(obj);
	SafeDelete(obj_wave);
}



//---------------------------------------------------------------------------------------
//	�X�V
//---------------------------------------------------------------------------------------

//	�X�V
bool	TimeUpUI::Update(void)
{

	//	�E�F�[�u�J�n
	if (flag)
	{
		if (obj_wave->WaveUpdate(TIMEUP_MAX::WIDTH))	return true;
	}
	else{
		//	���傶��ɑ傫���\��
		obj->SetScaling(0.1f);
		if (obj->ScalingBigUpdate(TIMEUP_MAX::WIDTH))
		{
			obj_wave->SetWave(0.04f);
			flag = true;
		}
	}
	return false;
}

//---------------------------------------------------------------------------------------
//	�`��
//---------------------------------------------------------------------------------------

//	�`��
void	TimeUpUI::Render(void)
{
	obj->Render(IMAGE_MODE::SCALING);

	if (flag)
	{
		obj_wave->Render(IMAGE_MODE::WAVE);
	}
}


//---------------------------------------------------------------------------------------
//	���ݒ�
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
//	���擾
//---------------------------------------------------------------------------------------

