
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"DrawShape.h"
#include	"PlayerManager.h"
#include	"Enemy.h"

//***************************************************************
//
//	Enemy�N���X
//
//***************************************************************

//------------------------------------------------------------------------------------
//	�O���[�o��
//------------------------------------------------------------------------------------
#define	ANGLEADJUST_SPEED 1.0f


//------------------------------------------------------------------------------------
//	�������E���
//------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	Enemy::Enemy( void ):
		targetPos(0.0f, 0.0f, 0.0f), active(false), eraseOK(false),
		interpolationParam(0.0f)
	{

	}

	//	�f�X�g���N�^
	Enemy::~Enemy( void )
	{

	}


//	���

//------------------------------------------------------------------------------------
//	�X�V�E�`��
//------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------
	//	�ړ�
	void	Enemy::Move(float speed,float length)
	{
		if (DistCheck(length)){
			//	�v���C���[�̕�������
			FacingPlayer();

			//	�����Ă�����ɑO�i
			Advance(speed);
		}
		else{
			//	���[�V�����ݒ�
			SetMotion(1);	//	�ҋ@���[�V����
		}
	}

	//	�v���C���[�̕�������
	void	Enemy::FacingPlayer(void)
	{
		//	�v���C���[�ւ̃x�N�g�������߂�
		Vector3	targetVec = playerManager->GetPlayer()->GetPos() - pos;
		targetVec.Normalize();

		AngleAdjust(targetVec, ANGLEADJUST_SPEED);
	}

	//	�O�i
	void	Enemy::Advance(float	speed)
	{
		//SetMove(Vector3(sinf(angle), 0.0f, cosf(angle)) * speed);
		SetMotion(1);
		Vector3	moveVec = Vector3(sinf(angle), 0.0f, cosf(angle));
		SetMove(moveVec * speed);
	}

	//	�v���C���[�Ƃ̋����`�F�b�N
	bool	Enemy::DistCheck(float	length)
	{
		Vector3	vec = playerManager->GetPlayer()->GetPos() - pos;
		float	len = vec.Length();

		//	���̋����܂ŋ߂Â��ƍU��
		if (len <= length)
		{
			return true;
		}
		return false;
	}

	//	���C�t�`�F�b�N�i �O�ȉ��Ȃ玀�S���[�h�Ɉڍs �j
	/*void	Enemy::LifeCheck(void)
	{
		if (!active)	return;

		if (charaLife->GetLife() <= 0)
		{
			active = false;
			charaMode->SetMode(charaMode->DEATH);
		}
	}*/
//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
//	���ݒ�
//------------------------------------------------------------------------------------
	//	�^�[�Q�b�g�̈ʒu��ݒ�
	void	Enemy::SetTargetPos(const Vector3& pos)
	{
		targetPos = pos;
	}

	//	�A�N�e�B�u��Ԏ擾
	bool	Enemy::GetActive(void)const
	{
		return	active;
	}

	//	�����\��Ԏ擾
	bool	Enemy::GetEraseOK(void)const
	{
		return	eraseOK;
	}

//------------------------------------------------------------------------------------
//	���擾
//------------------------------------------------------------------------------------
	
