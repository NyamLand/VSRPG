
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
	posx = x - w / 2;	posy = y - h / 2;	width = w;	height = h;

	//	HP�̃p�����[�^�e��
	hp = 0;		damage = 0;
	
	//	HP�o�[�t���[��
	hpFrame_obj = new Image();
	hpFrame_obj->Initialize("DATA/UI/main_UI/HP_UI.png", x, y, width, height, 0, 0, HP_MAX::WIDTH, HP_MAX::HEIGHT);

	//	HP�_���[�W
	hpDamage_obj = new iex2DObj("DATA/UI/main_UI/HP_UI.png");
	//hpDamage_obj = new Image();
	//hpDamage_obj->Initialize("DATA/UI/main_UI/HP_UI.png", posx, posy, 0, height, 0, HP_MAX::HEIGHT * 1, HP_MAX::WIDTH, HP_MAX::HEIGHT);

	//	HP�c��
	hp_obj = new iex2DObj("DATA/UI/main_UI/HP_UI.png");
	//hp_obj = new Image();				
	//hp_obj->Initialize("DATA/UI/main_UI/HP_UI.png", posx, posy, width, height, 0, HP_MAX::HEIGHT * 2, HP_MAX::WIDTH, HP_MAX::HEIGHT);


	//	HP�w�i
	hpBack_obj = new Image();
	hpBack_obj->Initialize("DATA/UI/main_UI/HP_UI.png", x, y, width, height, 0, HP_MAX::HEIGHT * 3, HP_MAX::WIDTH, HP_MAX::HEIGHT);


	hp_damage_x = width;		hp_damage_sx = 0;	hp_damage_sw = 0;		hp_w = width;
	hp_sw = HP_MAX::WIDTH;	damage_width = 0;	keep_width = 0;			damage_volume = 0;


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
	if (damage > 0)
	{
		SetDamage();
		DamageManager();
	}
}

//
void	HpUI::SetDamage(void)
{
	if (damage_state == true) return;

	//	hp�̊���
	float p = (float)((float)hp / (float)max_hp);

	//	hp�c�ʂ̌v�Z
	hp_w = width * p;
	hp_sw = HP_MAX::WIDTH * p;
	
	//	�_���[�W�ʂ̕�
	damage_width = keep_width - hp_w;

	//	60�t���[���Ń_���[�W�����I��
	damage_volume = (float)damage_width / 60.0f;

	damage_state = true;
	

}

//
void	HpUI::DamageManager(void)
{
	

	//	�_���[�W�̑S�̊���
	float d = (float)damage_width / (float)width;

	hp_damage_x = posx + hp_w;
	hp_damage_sx = hp_sw;
	hp_damage_sw = HP_MAX::WIDTH * d;

	damage_width -= damage_volume;

	if (damage_width <= 0)
	{
		damage = 0;
		keep_width = 0;
		damage_state = false;
	}
}

//	�`��
void	HpUI::Render(void)
{
	//----------------------
	//	HP�o�[
	//----------------------
	hpBack_obj->Render(IMAGE_MODE::ADOPTPARAM);		//	�w�i
	hp_obj->Render(posx, posy, hp_w, height, 0, HP_MAX::HEIGHT * 2, hp_sw, HP_MAX::HEIGHT);	//	HP�c��
	hpDamage_obj->Render(hp_damage_x, posy, damage_width, height, hp_damage_sx, HP_MAX::HEIGHT * 1, hp_damage_sw, HP_MAX::HEIGHT);	//	HP�_���[�W
	hpFrame_obj->Render(IMAGE_MODE::ADOPTPARAM);	//	�t���[��
}

//---------------------------------------------------------------------------------------
//	����֐�
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	���ݒ�
//---------------------------------------------------------------------------------------

void	HpUI::SetHp(int hp)
{
	//	�_���[�W���������AHP�_���[�W���󂯂ĂȂ���΃X���[
	if (this->damage > 0 && this->hp == hp) return;

	this->damage = this->hp - hp;
	this->hp = hp;

	//	�����_���[�W�󂯂Ă����
	if (this->damage > 0)
	{
		keep_width = hp_w;
	}
}

void	HpUI::SetMaxHp(int max_hp)
{
	this->max_hp = max_hp;
}

//---------------------------------------------------------------------------------------
//	���擾
//---------------------------------------------------------------------------------------

