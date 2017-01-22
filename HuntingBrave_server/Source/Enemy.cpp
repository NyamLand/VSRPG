
#include	"iextreme.h"
#include	"GameParam.h"
#include	"GlobalFunction.h"

#include	"Enemy.h"

//***************************************************************
//
//	Enemy�N���X
//
//***************************************************************

//------------------------------------------------------------------------------------
//	�O���[�o��
//------------------------------------------------------------------------------------

#define	MINOTAURUS_HEIGHT	2.0f
#define	MINOTAURUS_RADIUS	1.5f

#define	ANGLEADJUST_SPEED 1.0f
#define	MOVE_SPEED	10.0f
#define	SEARCH_DIST	10.0f
#define	ATTACK_DIST	5.0f

namespace
{
	namespace MOTION_NUM
	{
		enum
		{
			POSTURE,	//	�ҋ@���[�V����
			MOVE,			//	�ړ����[�V����
			ATTACK,		//	�U�����[�V����
		};
	}
}

//------------------------------------------------------------------------------------
//	�������E���
//------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	Enemy::Enemy( void ): timer( nullptr ),
		deltaTime( 0.0f ),
		searchDist( SEARCH_DIST ), alive( true )
	{
		//	�\���̏�����
		ZeroMemory( &lifeInfo, sizeof( lifeInfo ) );
		ZeroMemory( &enemyParam, sizeof( enemyParam ) );

		//	�R���W�������ݒ�
		collisionInfo.Set( SHAPE_TYPE::CAPSULE, MINOTAURUS_HEIGHT, MINOTAURUS_RADIUS );
		
		//	�^�C�}�[������
		timer = new Timer();
	}

	//	�f�X�g���N�^
	Enemy::~Enemy( void )
	{
		if ( timer != nullptr )
		{
			delete timer;
			timer = nullptr;
		}
	}

//------------------------------------------------------------------------------------
//	�X�V�E�`��
//------------------------------------------------------------------------------------

	//	�X�V
	void	Enemy::Update( float deltaTime )
	{
		this->deltaTime = deltaTime;

		//	�ʏ�ړ�
		Move();
	}

//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------
	
	//	�ړ�
	void	Enemy::Move( void )
	{
		Vector3	target = Vector3( 0.0f, 0.0f, 0.0f );
		bool	atkFlag = false;

		//	�v���C���[�����m�͈͂ɂ���΍s���J�n
		if ( DistCheck( target, atkFlag ) )
		{
			if ( !atkFlag )
			{
				//	�v���C���[�̕�������
				target.Normalize();
				AngleAdjust( target, ANGLEADJUST_SPEED );

				//	�����Ă�����ɑO�i
				Advance();
			}
			else
			{
				//	�U����
				SetMotion( MOTION_NUM::ATTACK );
			}
		}
		else
		{
			//	�ҋ@���[�V����
			SetMotion( MOTION_NUM::POSTURE );
		}
	}

	//	�O�i
	void	Enemy::Advance( void )
	{
		SetMotion( MOTION_NUM::MOVE );
		Vector3	moveVec = Vector3( sinf( enemyParam.angle ), 0.0f, cosf( enemyParam.angle ) );
		AddMove( moveVec * MOVE_SPEED );
	}

	//	�v���C���[�Ƃ̋����`�F�b�N
	bool	Enemy::DistCheck( Vector3& target, bool& attackFlag )
	{
		float length = 500.0f;
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			//	��A�N�e�B�u�̃v���C���[�̓X�L�b�v
			if ( gameParam->GetPlayerActive( i ) == false )	continue;
			target = gameParam->GetPlayerParam( i ).pos - enemyParam.pos;

			//	�Ƃ肠������ԋ߂��l�̒�����ۑ�
			if ( target.Length() < length )
			{
				length = target.Length();
			}
		}
		target.Normalize();

		//	�U���t���O�ݒ�
		if ( length <= ATTACK_DIST )	attackFlag = true;
		else attackFlag = false;

		//	���̋����܂ŋ߂Â��Ɗ��m
		if ( length <= searchDist )	return	true;
		return false;
	}

	//	���C�t�`�F�b�N�i �O�ȉ��Ȃ玀�S���[�h�Ɉڍs �j
	void	Enemy::LifeCheck( void )
	{
		if ( !lifeInfo.active )	return;

		if ( lifeInfo.life <= 0 )
		{
			lifeInfo.active = false;
			SetMode( MODE::DEAD );
		}
	}
	
	//	�ړ��l���Z
	void	Enemy::AddMove( const Vector3& move )
	{
		enemyParam.pos += move * deltaTime;
	}

	//	���������i �J�����e���Ȃ� �j
	void	Enemy::AngleAdjust( const Vector3& moveVec, float adjustSpeed )
	{
		//	�ړ����������߂�
		float	moveAngle = atan2f( moveVec.x, moveVec.z );

		//	�e�ɓ�����
		AngleAdjustParent(
			Vector3( sinf( moveAngle ), 0.0f, cosf( moveAngle ) ),
			adjustSpeed );
	}

	//	���������i�e�j
	void	Enemy::AngleAdjustParent( const Vector3& direction, float adjustSpeed )
	{
		//	���݂̌����ƖڕW�̌����̍������߂�
		float	targetAngle( atan2f( direction.x, direction.z ) );

		//	�p�x�������߂�
		float	dAngle( targetAngle - enemyParam.angle );

		//	���̐��K��
		if ( dAngle > 1.0f * D3DX_PI )		dAngle -= 2.0f * D3DX_PI;
		if ( dAngle < -1.0f * D3DX_PI )	dAngle += 2.0f * D3DX_PI;

		//	����speed���k�߂�
		if ( dAngle > 0.0f )
		{
			dAngle -= adjustSpeed;
			if ( dAngle < 0.0f )	dAngle = 0.0f;
		}
		else
		{
			dAngle += adjustSpeed;
			if ( dAngle > 0.0f )	dAngle = 0.0f;
		}

		enemyParam.angle = targetAngle - dAngle;

		//	�L�����N�^�[�̌�����PI�ȏ�ɂȂ�Ȃ��悤�ɂ���
		if ( enemyParam.angle >= 1.0f * D3DX_PI )  		enemyParam.angle -= 2.0f * D3DX_PI;
		if ( enemyParam.angle <= -1.0f * D3DX_PI )		enemyParam.angle += 2.0f * D3DX_PI;
	}

//------------------------------------------------------------------------------------
//	���ݒ�
//------------------------------------------------------------------------------------

	//	���W�ݒ�
	void	Enemy::SetPos( const Vector3& pos )
	{
		enemyParam.pos = pos;
	}

	//	�����ݒ�
	void	Enemy::SetAngle( float angle )
	{
		enemyParam.angle = angle;
	}

	//	���[�V�����ݒ�
	void	Enemy::SetMotion( int motion )
	{
		if ( enemyParam.motion != motion )
		{
			enemyParam.motion = motion;
		}
	}

//------------------------------------------------------------------------------------
//	���擾
//------------------------------------------------------------------------------------

	//	���W�擾
	Vector3	Enemy::GetPos( void )const
	{
		return	enemyParam.pos;
	}

	//	�����擾
	float			Enemy::GetAngle( void )const
	{
		return	enemyParam.angle;
	}

	//	���[�V�����擾
	int			Enemy::GetMotion( void )const
	{
		return	enemyParam.motion;
	}

	int	Enemy::GetMode( void )const
	{
		return mode;
	}

	bool	Enemy::GetAlive( void )const
	{
		return	alive;
	}