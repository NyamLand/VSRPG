
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"DrawShape.h"
#include	"PlayerManager.h"


#include	"SmallEnemy.h"

//***************************************************************
//
//	SmallEnemy�N���X
//
//***************************************************************

//------------------------------------------------------------------------------------
//	�O���[�o��
//------------------------------------------------------------------------------------

//	���f�����
#define	Y2009_SCALE	0.2f

//	����X�s�[�h
#define	ANGLE_ADJUST_SPEED	0.3f
#define	MOVE_SPEED		0.5f

//	���͏��
#define	MIN_INPUT_STICK		0.3f


//------------------------------------------------------------------------------------
//	�������E���
//------------------------------------------------------------------------------------

//	�R���X�g���N�^
SmallEnemy::SmallEnemy(void)
{

}

//	�f�X�g���N�^
SmallEnemy::~SmallEnemy(void)
{

}

//	������
bool	SmallEnemy::Initialize(void)
{
	//	�ǂݍ���
	Load("DATA/CHR/ENEMY/zako.IEM");

	SetPos(Vector3(10.0f, 0.0f, 0.0f));
	SetAngle(0.0f);
	SetScale(Y2009_SCALE);
	SetMotion(1);	//	���l��
	speed = MOVE_SPEED;

	//	�֐��|�C���^
	ModeFunction[MODE::MOVE] = &SmallEnemy::MoveMode;
	//ModeFunction[MODE::MOVE] = &Player::PostureMode;
	//ModeFunction[MODE::MOVE] = &Player::MoveMode;

	//	���X�V
	UpdateInfo();

	if (obj == nullptr)	return	false;
	return	true;
}

//	���

//------------------------------------------------------------------------------------
//	�X�V�E�`��
//------------------------------------------------------------------------------------

//	�X�V
void	SmallEnemy::Update(void)
{
	//	�e���[�h�ɉ���������֐�
	(this->*ModeFunction[MOVE/*��*/])();

	//	�X�V
	BaseChara::Update();
}

//	�`��
//void	SmallEnemy::Render(iexShader* shader, LPSTR technique)
//{
//	
//}

//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------

//	�ړ����[�h����
void	SmallEnemy::MoveMode(void)
{
	//	�X�e�B�b�N�ɂ��ړ�
	Move();
}

//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------

//	�ړ�
void	SmallEnemy::Move(void)
{
	//
	Vector3	vec = playerManager->GetPlayer()->GetPos() - pos;
	float	length = vec.Length();
	vec.Normalize();
	
	if (length <= 5.0f)
	{
		//	���[�V�����ݒ�

		//	���胂�[�V����

		//	��������
		AngleAdjust(vec, speed);
		SetMove(Vector3(sinf(angle), 0.0f, cosf(angle)) * speed);
		
	}
	else
	{
		//	���[�V�����ݒ�
		SetMotion(1);	//	�ҋ@���[�V����
	}
}

void	SmallEnemy::Attack()
{

}
//------------------------------------------------------------------------------------
//	���ݒ�
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	���擾
//------------------------------------------------------------------------------------

