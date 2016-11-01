
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
		targetPos( 0.0f, 0.0f, 0.0f ),
		interpolationParam( 0.0f ), searchDist( 0.0f ), attackDist( 0.0f )
	{
		
	}

	//	�f�X�g���N�^
	Enemy::~Enemy( void )
	{

	}

//------------------------------------------------------------------------------------
//	�X�V�E�`��
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------
	
	//	�ړ�
	void	Enemy::Move( float speed )
	{
		float	length = 0.0f;
		if ( DistCheck( length ) )	return;

		if ( length <= searchDist )
		{
			//	�v���C���[�̕�������
			FacingPlayer();

			//	�����Ă�����ɑO�i
			Advance( speed );
		}
		else
		{
			//	���[�V�����ݒ�
			SetMotion( 1 );	//	�ҋ@���[�V����
		}
	}

	//	�v���C���[�̕�������
	void	Enemy::FacingPlayer( void )
	{
		//	�v���C���[�ւ̃x�N�g�������߂�
		Vector3	targetVec = playerManager->GetPlayer( 0 )->GetPos() - pos;
		targetVec.Normalize();

		AngleAdjust( targetVec, ANGLEADJUST_SPEED );
	}

	//	�O�i
	void	Enemy::Advance( float speed )
	{
		SetMotion( 1 );
		Vector3	moveVec = Vector3( sinf( angle ), 0.0f, cosf( angle ) );
		SetMove( moveVec * speed );
	}

	//	�v���C���[�Ƃ̋����`�F�b�N
	bool	Enemy::DistCheck( float& length )
	{
		Vector3	vec = playerManager->GetPlayer( 0 )->GetPos() - pos;
		length = vec.Length();

		//	���̋����܂ŋ߂Â��ƍU��
		if ( length <= attackDist )
		{
			SetMode( MODE::ATTACK );
			return	true;
		}
		return false;
	}

	//	���C�t�`�F�b�N�i �O�ȉ��Ȃ玀�S���[�h�Ɉڍs �j
	void	Enemy::LifeCheck( void )
	{
		if ( !active )	return;

		if ( lifeInfo.life <= 0 )
		{
			active = false;
			SetMode( MODE::DEAD );
		}
	}

//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	���ݒ�
//------------------------------------------------------------------------------------
	
	//	�^�[�Q�b�g�̈ʒu��ݒ�
	void	Enemy::SetTargetPos( const Vector3& pos )
	{
		targetPos = pos;
	}

	//	�A�N�e�B�u��Ԏ擾
	bool	Enemy::GetActive( void )const
	{
		return	active;
	}

	//	�����\��Ԏ擾
	bool	Enemy::GetIsAlive( void )const
	{
		return	lifeInfo.isAlive;
	}

//------------------------------------------------------------------------------------
//	���擾
//------------------------------------------------------------------------------------
	
