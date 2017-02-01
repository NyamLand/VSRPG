
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"DrawShape.h"
#include	"Interpolation.h"
#include	"Sound.h"
#include	"PlayerManager.h"
#include	"Random.h"

#include	"Shadow.h"

//***************************************************************
//
//	SmallEnemy�N���X
//
//***************************************************************

//------------------------------------------------------------------------------------
//	�O���[�o��
//------------------------------------------------------------------------------------

//	�V���h�E
#define	Shadow_SCALE		0.1f
#define	Shadow_HEIGHT	0.125f
#define	Shadow_RADIUS	1.0f

//	����X�s�[�h
#define	ANGLE_ADJUST_SPEED	0.3f
#define	MOVE_SPEED		0.2f

//	���̑��p�����[�^
#define	ATTACK_DIST		5.0f
#define	SEARCH_DIST	10.0f



namespace
{
	namespace MOTION_FRAME
	{
		const int ATTACK_HIT_START = 140;
		const int ATTACK_HIT_END = 161;
		const int DEAD_START = 240;
		const int FALL_END = 291;
	}

}

//------------------------------------------------------------------------------------
//	�������E���
//------------------------------------------------------------------------------------

//	�R���X�g���N�^
Shadow::Shadow(void)
{
	ModeFunction[MODE::ENTRY] = &Shadow::EntryMode;
	ModeFunction[MODE::WAIT] = &Shadow::WaitMode;
	ModeFunction[MODE::MOVE] = &Shadow::MoveMode;
	ModeFunction[MODE::ATTACK] = &Shadow::AttackMode;
	ModeFunction[MODE::DAMAGE] = &Shadow::DamageMode;
	ModeFunction[MODE::DEAD] = &Shadow::DeadMode;

	//	�ϐ�������
	speed = MOVE_SPEED;
	searchDist = SEARCH_DIST;
	attackDist = ATTACK_DIST;
	lifeInfo.active = false;
	lifeInfo.isAlive = true;
	enemyType = ENEMY_TYPE::SHADOW;
}

//	�f�X�g���N�^
Shadow::~Shadow(void)
{

}

//	������
bool	Shadow::Initialize(int life)
{
	SetMode(MODE::ENTRY);
	SetAngle(0.0f);
	SetScale(0.0f);
	SetMotion(1);	//	���l��

	//	���C�t������
	lifeInfo.Initialize(life);

	//	�U����񏉊���
	ZeroMemory(&attackInfo, sizeof(AttackInfo));

	//	�����蔻���񏉊���
	collisionInfo.Set(SHAPE_TYPE::CAPSULE, Shadow_HEIGHT, Shadow_RADIUS);

	//	HP�o�[������
	bar = new EnemyHpUI();
	bar->Initilaize(HPUI_TYPE::ENEMY, GetLifeInfo().maxLife);

	//	���X�V
	UpdateInfo();

	if (obj == nullptr)	return	false;
	return	true;
}

//------------------------------------------------------------------------------------
//	�X�V�E�`��
//-----------------------------------------------------------------------------------

//	�X�V
void	Shadow::Update(void)
{
	//	�e���[�h�ɉ���������֐�
	(this->*ModeFunction[mode])();

	BaseChara::Update();
}


//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------

//	�o�������[�h����
void	Shadow::EntryMode(void)
{
	//	���
	bool	expantion = Interpolation::LinearInterpolation(
		scale, 0.0f, Shadow_SCALE, interpolationParam);

	//	��ԃp�����[�^�X�V
	Interpolation::PercentageUpdate(interpolationParam, 0.01f);

	//	��ԏI����ړ�
	if (expantion)
	{
		lifeInfo.active = true;
		SetMode(MODE::MOVE);
	}
}

//	�ړ����[�h����
void	Shadow::MoveMode(void)
{
	//	�ړ�
	Move(speed);
}

//	�U�����[�h����
void	Shadow::AttackMode(void)
{
	SetMotion(2);

	//	�t���[���擾
	int frame = obj->GetFrame();

	//	�t���[������
	if (frame >= MOTION_FRAME::ATTACK_HIT_START
		&& frame <= MOTION_FRAME::ATTACK_HIT_END)
	{
		//	�U����Ԃ�L���ɂ���
		attackInfo.Set(SHAPE_TYPE::SPHERE, Shadow_RADIUS, pos + (GetFront() * Shadow_RADIUS), Vector3(0, 0, 0));
		attackInfo.attackParam = ATTACK_PARAM::ATTACK1;
	}
	else
	{
		//	�U����Ԃ𖳌��ɂ���
		attackInfo.attackParam = ATTACK_PARAM::NO_ATTACK;

		//	�ʏ탂�[�h�ֈڍs
		if (frame >= 170)
			SetMode(MODE::WAIT);
	}
}

void	Shadow::DeadMode(void)
{
	SetMotion(4);
	static float alpha = 1.0f;

	//	�t���[���擾
	int frame = obj->GetFrame();

	//	�t���[������
	if (frame >= MOTION_FRAME::DEAD_START)
	{
		//	���ߊJ�n
		alpha -= 0.1f;
		if (frame>MOTION_FRAME::FALL_END)
		{
			alpha = 1.0f;
			lifeInfo.isAlive = false;
			sound->PlaySE(SE::ENEMY_DEAD);
		}
	}

}
//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------

//	�U��
void	Shadow::Attack(void)
{

}

//------------------------------------------------------------------------------------
//	���ݒ�
//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
//	���擾
//------------------------------------------------------------------------------------

