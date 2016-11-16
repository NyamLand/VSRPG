
#include	"iextreme.h"
#include	"InputManager.h"
#include	"Player.h"

//*****************************************************************************************************************************
//
//	Player�N���X
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

//	�����p�����[�^
#define	INIT_LIFE		5

//	���͏��
#define	MIN_INPUT_STICK		0.3f

//	����X�s�[�h
#define	ANGLE_ADJUST_MOVE_SPEED		0.3f
#define	MOVE_SPEED		0.2f

//	�萔�֘A
namespace
{
	//	���[�V�����ԍ�
	enum MOTION_NUM
	{
		POSUTURE,						//	�ҋ@
		RUN_START,						//	����o��
		RUN,									//	����
		ATTACK1,							//	�U���P
		ATTACK2,							//	�U���Q
		STEP,								//	�X�e�b�v
		MAGIC_CHANT_START,		//	�r���J�n
		MAGIC_CHANT,					//	�r����
		MAGIC_ACTUATION,			//	���@����
		KNOCKBACK1,					//	������P
		KNOCKBACK2,					//	������Q
		FALL,									//	�|���
		DEAD,								//	���S
		EAT,									//	�H�ׂ�
		MENU_OPEN,						//	���j���[���J��
		MENU,								//	���j���[���쒆
		LEVEL_UP,							//	���x���A�b�v
		MENU_CLOSE,					//	���j���[�����
		WIN,									//	����
		WIN_KEEP,						//	�����L�[�v
		CRY									//	����
	};
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

		//	�̗͏�����
		lifeInfo.Initialize( INIT_LIFE );
		lifeInfo.active = true;
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
		lifeInfo.life = pParam.life;

		//	���[�h�ʓ���֐�
		( this->*ModeFunction[mode] )();

		//	�v�Z���񔽉f
		pParam.life = lifeInfo.life;
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

		//	���͎�t
		if ( inputManager->GetInput( index ).inputType == InputManager::ENTER )
		{
			if( SetMode( MODE::SWOADATTACK ) ) SetMotion( MOTION_NUM::ATTACK1 );
			inputManager->GetInput( index ).inputType = InputManager::NO_INPUT;
		}
	}

	//	���U��
	void	Player::ModeSwordAttack( void )
	{
		SwordAttack();
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

			SetMotion( MOTION_NUM::RUN );
		}
		else
		{
			SetMotion( MOTION_NUM::POSUTURE );
		}
	}

	//	���U��
	void	Player::SwordAttack( void )
	{
		// ���ȏ�̃t���[���ɒB����ƈړ��ɖ߂�
		if ( pParam.frame >= 190 )
		{
			SetMode( MODE::MOVE );
		}
	}

	//	�_���[�W
	void	Player::Damage( void )
	{
		SetMotion( MOTION_NUM::KNOCKBACK1 );
		lifeInfo.active = false;
		if ( pParam.frame >= 465 )
		{
			SetMode( MODE::MOVE );
			lifeInfo.active = true;
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

