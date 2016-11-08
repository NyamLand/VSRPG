
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"Image.h"
#include	"HpUI.h"

//***************************************************************
//
//	HpUI�N���X
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	�O���[�o��	
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	�������E���
//---------------------------------------------------------------------------------------

//	�R���X�g���N�^
HpUI::HpUI(int x, int y, int w, int h)
{
	//	���W�A�T�C�Y���i�[
	posx = x;	posy = y;	width = w;	height = h;
	
	//	HP�o�[�t���[��
	hpFrame_obj = new Image();
	hpFrame_obj->Initialize("DATA/UI/main_UI/HP_UI.png", posx, posy, width, height, 0, 0, HP_MAX::WIDTH, HP_MAX::HEIGHT);

	//	HP�_���[�W
	hpDamage_obj = new Image();
	hpDamage_obj->Initialize("DATA/UI/main_UI/HP_UI.png", posx, posy, width, height, 0, HP_MAX::HEIGHT * 1, HP_MAX::WIDTH, HP_MAX::HEIGHT);

	//	HP�c��
	hp_obj = new Image();				
	hp_obj->Initialize("DATA/UI/main_UI/HP_UI.png", posx, posy, width, height, 0, HP_MAX::HEIGHT * 2, HP_MAX::WIDTH, HP_MAX::HEIGHT);


	//	HP�w�i
	hpBack_obj = new Image();
	hpBack_obj->Initialize("DATA/UI/main_UI/HP_UI.png", posx, posy, width, height, 0, HP_MAX::HEIGHT * 3, HP_MAX::WIDTH, HP_MAX::HEIGHT);

}

//	�f�X�g���N�^
HpUI::~HpUI(void)
{
	SafeDelete(hpFrame_obj);
	SafeDelete(hpDamage_obj);
	SafeDelete(hp_obj);
	SafeDelete(hpBack_obj);
}



//---------------------------------------------------------------------------------------
//	�X�V�E�`��
//---------------------------------------------------------------------------------------

//	�X�V
void	HpUI::Update(void)
{
	
}

//	�`��
void	HpUI::Render(void)
{
	//----------------------
	//	HP�o�[
	//----------------------
	hpBack_obj->Render(IMAGE_MODE::ADOPTPARAM);		//	�w�i
	hp_obj->Render(IMAGE_MODE::ADOPTPARAM);			//	HP�c��
	hpDamage_obj->Render(IMAGE_MODE::ADOPTPARAM);	//	HP�_���[�W
	hpFrame_obj->Render(IMAGE_MODE::ADOPTPARAM);	//	�t���[��
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

