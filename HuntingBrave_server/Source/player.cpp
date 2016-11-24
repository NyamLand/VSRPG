
#include	"iextreme.h"
#include	<vector>
#include	"GameParam.h"
#include	"InputManager.h"
#include	"MagicManager.h"
#include	"Player.h"

//*****************************************************************************************************************************
//
//	Player�N���X
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

//	�萔
#define	CHANT_TIME	2

//	���͏��
#define	MIN_INPUT_STICK		0.3f

//	����X�s�[�h
#define	ANGLE_ADJUST_MOVE_SPEED		0.3f
#define	MOVE_SPEED		0.2f

namespace
{
	namespace MOTION_FRAME
	{
		const int SWORDATTACK_HIT_START = 140;
		const int SWORDATTACK_HIT_END = 150;
		const int SWORDATTACK1_END = 160;
		const int MAGICCHANT_END = 290;
		const int MAGICACTIVATION = 340;
		const int MAGICATTACK_END = 370;
		const int KNOCKBACK1_END = 405;
	}

	namespace ATTACK_STEP
	{
		enum
		{
			CHANT_START,
			CHANT,
			ACTIVATION,
		};
	}
}

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------
	
	//	�R���X�g���N�^
	Player::Player( int id ) : 
		index( id )
	{
		ZeroMemory( &pParam, sizeof( PlayerParam ) );

		//	�֐��|�C���^�ݒ�
		ModeFunction[MODE::MOVE] = &Player::ModeMove;
		ModeFunction[MODE::SWOADATTACK] = &Player::ModeSwordAttack;
		ModeFunction[MODE::DAMAGE] = &Player::ModeDamage;
		ModeFunction[MODE::MAGICATTACK] = &Player::ModeMagicAttack;
	}

	//	�f�X�g���N�^
	Player::~Player( void )
	{
		
	}

//----------------------------------------------------------------------------------------------
//	�X�V
//----------------------------------------------------------------------------------------------

	//	�X�V
	bool	Player::Update( PlayerParam& param )
	{
		//	���󂯎��
		pParam = param;

		//	���[�h�ʓ���֐�
		( this->*ModeFunction[mode] )();

		//	�v�Z���񔽉f
		param = pParam;

		return true;
	}

//----------------------------------------------------------------------------------------------
//	���[�h�ʓ���֐�
//----------------------------------------------------------------------------------------------

	//	�ʏ�ړ�
	void	Player::ModeMove( void )
	{
		//	�ړ�
		Move();

		//	���̓`�F�b�N
		CheckInput();
	}

	//	���U��
	void	Player::ModeSwordAttack( void )
	{
		SwordAttack();
	}

	//	���@�U��
	void	Player::ModeMagicAttack( void )
	{
		switch ( gameParam->GetAttackInfo( index ).step )
		{
		case ATTACK_STEP::CHANT_START:
			MagicChantStart();
			break;

		case ATTACK_STEP::CHANT:
			MagicChant();
			break;

		case ATTACK_STEP::ACTIVATION:
			MagicAttack();
			break;
		}
	}

	//	�_���[�W
	void	Player::ModeDamage( void )
	{
		Damage();
	}
	
//----------------------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------------------

	//	�ړ�
	void	Player::Move( void )
	{
		float moveX = inputManager->GetInput( index ).axisX;
		float moveZ = inputManager->GetInput( index ).axisY;
		float length = sqrtf( moveX * moveX + moveZ * moveZ );

		//	���͂�����Έړ�����
		if ( length >= MIN_INPUT_STICK )
		{
			//	��������
			AngleAdjust(
				Vector3( moveX, 0.0f, moveZ ),
				ANGLE_ADJUST_MOVE_SPEED );

			//	�ړ�
			pParam.pos += 
				Vector3( sinf( pParam.angle ), 0.0f, cosf( pParam.angle ) ) * MOVE_SPEED;

			SetMotion( PLAYER_MOTION::RUN );
		}
		else
		{
			SetMotion( PLAYER_MOTION::POSUTURE );
		}
	}

	//	���U��
	void	Player::SwordAttack( void )
	{
		//	�t���[���Ǘ�
		if ( pParam.frame >= MOTION_FRAME::SWORDATTACK_HIT_START &&
			pParam.frame <= MOTION_FRAME::SWORDATTACK_HIT_END )
		{
			gameParam->GetAttackInfo( index ).attackParam = AttackInfo::ATTACK1;
		}
		else
		{
			gameParam->GetAttackInfo( index ).attackParam = AttackInfo::NO_ATTACK;
		}

		// ���ȏ�̃t���[���ɒB����ƈړ��ɖ߂�
		if ( pParam.frame >= MOTION_FRAME::SWORDATTACK1_END )
		{
			SetMode( MODE::MOVE );
			gameParam->GetAttackInfo( index ).Reset();
		}
	}

	//	���@�U��
	void	Player::MagicAttack( void )
	{
		if ( pParam.frame == MOTION_FRAME::MAGICACTIVATION )
		{
			magicManager->Append( index, 
				gameParam->GetAttackInfo( index ).collisionShape.sphere.center,
				Vector3( 0.0f, 0.0f, 0.0f ) );
		}

		if ( pParam.frame >= MOTION_FRAME::MAGICATTACK_END )
		{
			SetMode( MODE::MOVE );
			gameParam->GetAttackInfo( index ).Reset();
		}
	}

	//	���@�r��
	void	Player::MagicChant( void )
	{
		//	�������Ƃ������\��ԂȂ甭���A�����s�Ȃ�ړ��ɖ߂�
		if ( inputManager->GetInputState( index, KEY_TYPE::A, KEY_STATE::UP ) )
		{
			//	�^�C�}�[�X�V
			bool	chantState = gameParam->GetAttackInfo( index ).timer.Update();

			if ( chantState )
			{
				SetMotion( PLAYER_MOTION::MAGIC_ACTIVATION );
				gameParam->GetAttackInfo( index ).step = ATTACK_STEP::ACTIVATION;
			}
			else
			{
				//	�ړ��ɖ߂�i�p�����[�^���Z�b�g�j
				SetMode( MODE::MOVE );
				gameParam->GetAttackInfo( index ).Reset();
			}
		}
	}

	//	���@�r���J�n
	void	Player::MagicChantStart( void )
	{
		//	�����Ă���ԉr���A��莞�Ԍo�߂Ŕ����\
		if ( inputManager->GetInputState( index, KEY_TYPE::A, KEY_STATE::STAY ) )
		{
			if ( pParam.frame >= MOTION_FRAME::MAGICCHANT_END )
			{
				SetMotion( PLAYER_MOTION::MAGIC_CHANT );
				gameParam->GetAttackInfo( index ).timer.Start( CHANT_TIME );
				gameParam->GetAttackInfo( index ).step = ATTACK_STEP::CHANT;
			}
		}
		else
		{
			//	�ړ��ɖ߂�i �p�����[�^���Z�b�g �j
			SetMode( MODE::MOVE );
			gameParam->GetAttackInfo( index ).Reset();
		}
	}

	//	�_���[�W
	void	Player::Damage( void )
	{
		gameParam->GetLifeInfo( index ).active = false;
		SetMotion( PLAYER_MOTION::KNOCKBACK1 );

		if ( pParam.frame >= MOTION_FRAME::KNOCKBACK1_END )
		{
			gameParam->GetLifeInfo( index ).active = true;
			SetMode( MODE::MOVE );
		}
	}

	//	���̓`�F�b�N
	void	Player::CheckInput( void )
	{
		//	���U�����͎�t
		if ( inputManager->GetInputState( index, KEY_TYPE::B, KEY_STATE::ENTER ) )
		{
			if ( SetMode( MODE::SWOADATTACK ) )
			{
				SetMotion( PLAYER_MOTION::ATTACK1 );
				return;
			}
		}

		//	���@�U�����͎�t
		if ( inputManager->GetInputState( index, KEY_TYPE::A, KEY_STATE::ENTER ) )
		{
			if ( SetMode( MODE::MAGICATTACK ) )
			{
				SetMotion( PLAYER_MOTION::MAGIC_CHANT_START );
				return;
			}
		}
	}

	//	��������
	void	Player::AngleAdjust( const Vector3& targetVec, float adjustSpeed )
	{
		//	�ړ����������߂�
		float	moveAngle = atan2f( targetVec.x, targetVec.z );

		//	�e�ɓ�����
		AngleAdjustParent(
			Vector3( sinf( moveAngle ), 0.0f, cosf( moveAngle ) ),
			adjustSpeed );
	}

	//	���������i�e�j
	void	Player::AngleAdjustParent( const Vector3& direction, float adjustSpeed )
	{
		//	���݂̌����ƖڕW�̌����̍������߂�
		float	targetAngle( atan2f( direction.x, direction.z ) );

		//	�p�x�������߂�
		float	dAngle( targetAngle - pParam.angle );

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

		pParam.angle = targetAngle - dAngle;

		//	�L�����N�^�[�̌�����PI�ȏ�ɂȂ�Ȃ��悤�ɂ���
		if ( pParam.angle >= 1.0f * D3DX_PI )		pParam.angle -= 2.0f * D3DX_PI;
		if ( pParam.angle <= -1.0f * D3DX_PI )		pParam.angle += 2.0f * D3DX_PI;
	}

//----------------------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------------------

	//	���[�V�����ݒ�
	void	Player::SetMotion( int motion )
	{
		if ( pParam.motion != motion )
		{
			pParam.motion = motion;
		}
	}

