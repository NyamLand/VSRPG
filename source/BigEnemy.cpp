
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"DrawShape.h"
#include	"BigEnemy.h"

//***************************************************************
//
//	Enemy�N���X
//
//***************************************************************

//------------------------------------------------------------------------------------
//	�O���[�o��
//------------------------------------------------------------------------------------

//	���f�����
#define	Y2009_SCALE	0.02f

//	����X�s�[�h
#define	ANGLE_ADJUST_SPEED	0.3f
#define	MOVE_SPEED		0.5f

//	���͏��
#define	MIN_INPUT_STICK		0.3f


//------------------------------------------------------------------------------------
//	�������E���
//------------------------------------------------------------------------------------

//	�R���X�g���N�^
BigEnemy::BigEnemy(void)
{

}

//	�f�X�g���N�^
BigEnemy::~BigEnemy(void)
{

}

//	������
bool	BigEnemy::Initialize(void)
{
	//	�ǂݍ���
	Load("DATA/CHR/Y2009/Y2009.IEM");

	SetPos(Vector3(-10.0f, 0.0f, 0.0f));
	SetAngle(0.0f);
	SetScale(Y2009_SCALE);
	SetMotion(1);	//	���l��
	speed = MOVE_SPEED;

	//	�֐��|�C���^
	ModeFunction[MODE::MOVE] = &BigEnemy::MoveMode;
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
void	BigEnemy::Update(void)
{
	//	�e���[�h�ɉ���������֐�
	(this->*ModeFunction[MOVE/*��*/])();

	//	�X�V
	BaseChara::Update();
}

//	�`��
void	BigEnemy::Render(iexShader* shader, LPSTR technique)
{
	drawShape->DrawSphere(GetPos(), 5.0f, 0xFFFFFFFF);
}

//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------

//	�ړ����[�h����
void	BigEnemy::MoveMode(void)
{
	//	�X�e�B�b�N�ɂ��ړ�
	Move();
}

//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------

//	�ړ�
void	BigEnemy::Move(void)
{
	////	���X�e�B�b�N�̓��̓`�F�b�N
	//float	axisX = (float)input[0]->Get(KEY_AXISX);
	//float	axisY = -(float)input[0]->Get(KEY_AXISY);
	//float	length = sqrtf(axisX * axisX + axisY * axisY) * 0.001f;

	////	���͂�����Έړ�����
	//if (length >= MIN_INPUT_STICK)
	//{
	//	//	���[�V�����ݒ�
	//	SetMotion(4);	//	���胂�[�V����

	//	//	��������
	//	AngleAdjust(
	//		Vector3(axisX, 0.0f, axisY),
	//		ANGLE_ADJUST_SPEED);

	//	//	�ړ�
	//	SetMove(Vector3(sinf(angle), 0.0f, cosf(angle)) * speed);
	//}
	//else
	//{
	//	//	���[�V�����ݒ�
	//	SetMotion(1);	//	�ҋ@���[�V����
	//}
}

void	BigEnemy::Attack()
{

}
//------------------------------------------------------------------------------------
//	���ݒ�
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	���擾
//------------------------------------------------------------------------------------

