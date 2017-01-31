
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"Interpolation.h"
#include	"Image.h"
#include	"NumberUI.h"
#include	"HpUI.h"

//***************************************************************
//
//	HpUI�N���X
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	�O���[�o��	
//---------------------------------------------------------------------------------------
//include
#define HP_DIGIT 3


//---------------------------------------------------------------------------------------
//	�������E���
//---------------------------------------------------------------------------------------

//	�R���X�g���N�^
HpUI::HpUI(int x, int y, int w, int h)
{
	//	���W�A�T�C�Y���i�[
	posx = x - w / 2;	posy = y - h / 2;	width = w;	height = h;

	//	HP�̃p�����[�^�e��
	hp = 0;		max_hp = 0;		damage = 0;
	
	//	HP�o�[�t���[��
	hpFrame_obj = new Image();
	hpFrame_obj->Initialize("DATA/UI/main_UI/HP_UI.png", x, y, width, height, 0, 0, HP_MAX::WIDTH, HP_MAX::HEIGHT);

	//	HP�_���[�W
	hpDamage_obj = new iex2DObj("DATA/UI/main_UI/HP_UI.png");
	//	HP�c��(�o�[)
	hp_obj = new iex2DObj("DATA/UI/main_UI/HP_UI.png");
	//	HP�w�i
	hpBack_obj = new Image();
	hpBack_obj->Initialize("DATA/UI/main_UI/HP_UI.png", x, y, width, height, 0, HP_MAX::HEIGHT * 3, HP_MAX::WIDTH, HP_MAX::HEIGHT);

	//	HP�c��(�����j
	nowHpUI = new NumberUI(x - (HP_MAX::SIZE * 2.0f), y, HP_MAX::SIZE, HP_MAX::SIZE, HP_DIGIT);
	maxHpUI = new NumberUI(x + (HP_MAX::SIZE * 2.0f), y, HP_MAX::SIZE, HP_MAX::SIZE, HP_DIGIT);
	period = new Image();
	period->Initialize("DATA/UI/main_UI/Number.png", x + (HP_MAX::SIZE * 1.5f), y, HP_MAX::SIZE, HP_MAX::SIZE, 64 * 11, 64 * NUM_COLOR::WHITE, 64, 64);

	hp_damage_sw = 0;		hp_w = width;
	hp_sw = HP_MAX::WIDTH;	damage_width = 0;	keep_width = 0;			damage_volume = 0.0f;


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
	if (damage != 0)
	{
		SetDamage();
		DamageManager();
	}

	nowHpUI->SetNum(this->hp);
	maxHpUI->SetNum(this->max_hp);

	nowHpUI->Update();
	maxHpUI->Update();
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

	//	�_���[�W����
	//damage_volume = (float)damage_width / 60.0f;

	damage_state = true;
	

}

//
void	HpUI::DamageManager(void)
{
	

	//	�_���[�W�̑S�̊���
	float d = (float)(damage_width + hp_w) / (float)width;
	

	hp_damage_sw = HP_MAX::WIDTH * d;

	Interpolation::LinearInterpolation(damage_width, keep_width - hp_w, 0, damage_volume);

	damage_volume += 0.02;

	if (damage_volume >= 1.0f)
	{
		damage = 0;
		damage_volume = 0.0f;
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
	hpDamage_obj->Render(posx, posy, hp_w + damage_width, height, 0, HP_MAX::HEIGHT * 1, hp_damage_sw, HP_MAX::HEIGHT);	//	HP�_���[�W
	hp_obj->Render(posx, posy, hp_w, height, 0, HP_MAX::HEIGHT * 2, hp_sw, HP_MAX::HEIGHT);	//	HP�c��
	hpFrame_obj->Render(IMAGE_MODE::ADOPTPARAM);	//	�t���[��

	//	hp���l
	period->Render(IMAGE_MODE::ADOPTPARAM);
	nowHpUI->Render();
	maxHpUI->Render();
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
	if (this->damage != 0 && this->hp == hp) return;

	this->damage = this->hp - hp;
	this->hp = hp;

	//	�����_���[�W�󂯂Ă����
	if (this->damage != 0)
	{
		keep_width = hp_w;
		damage_state = false;
		damage_volume = 0.0f;
	}
}

void	HpUI::SetMaxHp(int max_hp)
{
	this->max_hp = max_hp;
}

//---------------------------------------------------------------------------------------
//	���擾
//---------------------------------------------------------------------------------------

