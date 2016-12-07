
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"GameParam.h"

#include	"EnemyHp.h"

//***************************************************************
//
//	EnemyHpUI�N���X
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	�O���[�o��	
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	�������E���
//---------------------------------------------------------------------------------------

//	�R���X�g���N�^
EnemyHpUI::EnemyHpUI()
{
	//	���W�A�T�C�Y���i�[
	width = 100.0f;	height = 25.0f;
	id = -1;

}

//	�f�X�g���N�^
EnemyHpUI::~EnemyHpUI(void)
{
	SafeDelete(hpFrame_obj);
	SafeDelete(hp_obj);
}


void	EnemyHpUI::Initilaize(int type, float maxhp)
{
	
	hp = 0;
	//	HP�o�[�t���[��
	hpFrame_obj = new iex2DObj("DATA/UI/main_UI/Enemy_HP.png");

	//	HP�c��
	hp_obj = new iex2DObj("DATA/UI/main_UI/Enemy_HP.png");

	mode_type = type;
	maxHp = maxhp;
}

//---------------------------------------------------------------------------------------
//	�X�V�E�`��
//---------------------------------------------------------------------------------------

//	�X�V
void	EnemyHpUI::Update( void )
{
	
	
}

//	�`��
void	EnemyHpUI::Render(float hp,const Vector3& pos,const Vector3& up)
{
	
	Vector3	BarPos;
	Vector3	out;
	BarPos = pos + up * 5.0f;
	WorldToClient(BarPos, out, matView * matProjection);
	out.x -= 60;

	float	parsent = (float)hp / (float)maxHp;
	//----------------------
	//	HP�o�[
	//----------------------
	switch (mode_type)
	{
	case HPUI_TYPE::ENEMY:

		hpFrame_obj->Render(out.x, out.y, (int)width, (int)height, 0, 0, HP_MAX::WIDTH, HP_MAX::HEIGHT);	//	�t���[��
		hp_obj->Render(out.x, out.y, (int)(width*parsent), (int)height, 0, HP_MAX::HEIGHT * 1,(int)( (float)HP_MAX::WIDTH*parsent), HP_MAX::HEIGHT);		//	HP�c��
		break;

	case HPUI_TYPE::PLAYER:

		if (gameParam->GetMyIndex() == id)break;
		hpFrame_obj->Render(out.x, out.y, (int)width, (int)height, 0, HP_MAX::HEIGHT * 3, HP_MAX::WIDTH, HP_MAX::HEIGHT);	//	�t���[��
		hp_obj->Render(out.x, out.y, (int)(width*parsent), (int)height, 0, HP_MAX::HEIGHT * 4, (int)((float)HP_MAX::WIDTH*parsent), HP_MAX::HEIGHT);		//	HP�c��
		break;

	default:

		return;
		break;
	}
}

//---------------------------------------------------------------------------------------
//	����֐�
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	���ݒ�
//---------------------------------------------------------------------------------------
void	EnemyHpUI::SetId(int id)
{
	this->id = id;
}
//---------------------------------------------------------------------------------------
//	���擾
//---------------------------------------------------------------------------------------

