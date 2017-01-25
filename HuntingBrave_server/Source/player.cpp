
#include	"iextreme.h"
#include	<vector>
#include	<map>
#include	"GameParam.h"
#include	"GameManager.h"
#include	"InputManager.h"
#include	"MagicManager.h"
#include	"Collision.h"
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
#define	CHANT_TIME	1.0f
#define	DEATH_TIME	3.0f
#define	STEP_DRAG		0.97f

//	���͏��
#define	MIN_INPUT_STICK		0.3f

//	����X�s�[�h
#define	ANGLE_ADJUST_MOVE_SPEED		0.3f
#define	MOVE_SPEED		0.2f
#define	STEP_SPEED		0.5f

namespace
{
	namespace SUPPIN_FRAME
	{
		const int SWORDATTACK_HIT_START = 140;
		const int SWORDATTACK_HIT_END = 150;
		const int SWORDATTACK1_END = 160;
		const int STEP_END = 260;
		const int MAGICCHANT_END = 290;
		const int MAGICACTIVATION = 340;
		const int MAGICATTACK_END = 370;
		const int KNOCKBACK1_END = 405;
		const int FALL_END = 493;
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
	namespace
	{
		namespace FRAME_TYPE
		{
			enum
			{
				ATTACK_HIT_START,
				ATTACK_HIT_END,
				ATTACK_END,
				STEP_END,
				MAGIC_CHANT_END,
				MAGIC_ATTACK_START,
				MAGIC_ATTACK_END,
				DAMAGE1_END,
				DAMAGE2_END,
				FALL_END,
				TYPE_MAX

			};
		}

		namespace  PLAYER_TYPE
		{
			enum
			{
				NORMAL,
				FIGHTER,	//	�t�@�C�^�[
				MAGICIAN,	//	�}�W�V����
				KNIGHT,		//	�i�C�g
				PRIEST,		//	�v���[�X�g
				ASSASSIN,	//	�A�T�V��
				MODEL_MAX
			};
		}

		const int motionFrame[][FRAME_TYPE::TYPE_MAX] =
		{
			//�����҂�
			{
				140,// �U������J�n
				150,// �U������I��
				160,// �U���I��
				260,// �X�e�b�v�I��
				290,// ���@�r���I��
				340,// ���@�U���J�n
				370,// ���@�U���I��
				409,// �m�b�N�o�b�N(�_���[�W)1
				438,// �m�b�N�o�b�N(�_���[�W)2
				494// ���Ƀ��[�V�����I��
			},
			//�t�@�C�^�[
			{
				107,// �U������J�n
				119,// �U������I��
				130,// �U���I��
				260,// �X�e�b�v�I��
				290,// ���@�r���I��
				340,// ���@�U���J�n
				370,// ���@�U���I��
				409,// �m�b�N�o�b�N(�_���[�W)1
				438,// �m�b�N�o�b�N(�_���[�W)2
				494// ���Ƀ��[�V�����I��
			},
			//�}�W�V����
			{
				108,// �U������J�n
				115,// �U������I��
				132,// �U���I��
				200,// �X�e�b�v�I��
				258,// ���@�r���I��
				275,// ���@�U���J�n
				287,// ���@�U���I��
				316,// �m�b�N�o�b�N(�_���[�W)1
				345,// �m�b�N�o�b�N(�_���[�W)2
				404// ���Ƀ��[�V�����I��
			},
			//�i�C�g
			{
				127,// �U������J�n
				140,// �U������I��
				152,// �U���I��
				220,// �X�e�b�v�I��
				278,// ���@�r���I��
				295,// ���@�U���J�n
				307,// ���@�U���I��
				336,// �m�b�N�o�b�N(�_���[�W)1
				365,// �m�b�N�o�b�N(�_���[�W)2
				424// ���Ƀ��[�V�����I��
			},
			//�v���[�X�g
			{
				126,// �U������J�n
				136,// �U������I��
				152,// �U���I��
				220,// �X�e�b�v�I��
				278,// ���@�r���I��
				295,// ���@�U���J�n
				307,// ���@�U���I��
				336,// �m�b�N�o�b�N(�_���[�W)1
				365,// �m�b�N�o�b�N(�_���[�W)2
				424// ���Ƀ��[�V�����I��
			},
			//�A�T�V��(��)
			{
				127,// �U������J�n
				140,// �U������I��
				155,// �U���I��
				260,// �X�e�b�v�I��
				281,// ���@�r���I��
				333,// ���@�U���J�n
				310,// ���@�U���I��
				339,// �m�b�N�o�b�N(�_���[�W)1
				368,// �m�b�N�o�b�N(�_���[�W)2
				1000// ���[�V�����I��
			},
		};
	}
}

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------
	
	//	�R���X�g���N�^
	Player::Player( int id ) : timer( nullptr ),
		stepSpeed(0.0f), charType(PLAYER_TYPE::NORMAL),
		index( id )
	{
		ZeroMemory( &pParam, sizeof( PlayerParam ) );

		//	�֐��|�C���^�ݒ�
		ModeFunction[MODE::MOVE] = &Player::ModeMove;
		ModeFunction[MODE::SWOADATTACK] = &Player::ModeSwordAttack;
		ModeFunction[MODE::DAMAGE] = &Player::ModeDamage;
		ModeFunction[MODE::MAGICATTACK] = &Player::ModeMagicAttack;
		ModeFunction[MODE::DEATH] = &Player::ModeDeath;
		ModeFunction[MODE::STEP] = &Player::ModeStep;
		ModeFunction[MODE::MENU] = &Player::ModeMenu;

		timer = new Timer();
	}

	//	�f�X�g���N�^
	Player::~Player( void )
	{
		if ( timer != nullptr )
		{
			delete timer;
			timer = nullptr;
		}
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

	//	���S
	void	Player::ModeDeath( void )
	{
		//	���ۑ�
		int motion = gameParam->GetPlayerParam( index ).motion;
		int frame = gameParam->GetPlayerParam( index ).frame;

		//	�|��郂�[�V������
		if ( motion == PLAYER_MOTION::FALL )
		{
			if ( frame >= motionFrame[charType][FRAME_TYPE::FALL_END] )
			{ 
				SetMotion( PLAYER_MOTION::DEAD );
				timer->Start( DEATH_TIME );
			}
		}
		else if ( motion == PLAYER_MOTION::DEAD )
		{
			if ( timer->Update() )
			{
				gameParam->InitializePlayer( index );
				SetMode( MODE::MOVE );
			}
		}
	}

	//	�X�e�b�v
	void	Player::ModeStep( void )
	{
		//	��A�N�e�B�u�ɂ���
		gameParam->GetLifeInfo( index ).active = false;

		//	�ړ��l���Z
		Vector3	move = Vector3( sinf( pParam.angle ), 0.0f, cosf( pParam.angle ) ) * stepSpeed;
		AddMove( move );

		//	���X�Ɍ���
		stepSpeed *= STEP_DRAG;

		//	���[�V�������I������Έړ��ɖ߂�
		if ( pParam.frame >= motionFrame[charType][FRAME_TYPE::STEP_END])
		{
			SetMode( MODE::MOVE );
			gameParam->GetLifeInfo( index ).active = true;
		}
	}

	//	���j���[���[�h
	void	Player::ModeMenu( void )
	{
		if ( inputManager->GetInputState( index, KEY_TYPE::START, KEY_STATE::ENTER ) ||
			inputManager->GetInputState( index, KEY_TYPE::A, KEY_STATE::ENTER ) )
		{
			SetMode( MODE::MOVE );
		}
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
			Vector3 move = Vector3( sinf( pParam.angle ), GRAVITY, cosf( pParam.angle ) ) * MOVE_SPEED;
			AddMove( move );

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
		if ( pParam.frame >= motionFrame[charType][FRAME_TYPE::ATTACK_HIT_START] &&
			pParam.frame <= motionFrame[charType][FRAME_TYPE::ATTACK_HIT_END])
		{
			gameParam->GetAttackInfo( index ).attackParam = AttackInfo::ATTACK1;
		}
		else
		{
			gameParam->GetAttackInfo( index ).attackParam = AttackInfo::NO_ATTACK;
		}

		// ���ȏ�̃t���[���ɒB����ƈړ��ɖ߂�
		if (pParam.frame >= motionFrame[charType][FRAME_TYPE::ATTACK_END])
		{
			SetMode( MODE::MOVE );
			gameParam->GetAttackInfo( index ).Reset();
		}
	}

	//	���@�U��
	void	Player::MagicAttack( void )
	{
		if (pParam.frame == motionFrame[charType][FRAME_TYPE::MAGIC_ATTACK_START])
		{
			magicManager->Append( index, 
				gameParam->GetAttackInfo( index ).vec1,
				gameParam->GetAttackInfo( index ).vec2 );
		}

		if (pParam.frame >= motionFrame[charType][FRAME_TYPE::MAGIC_ATTACK_END])
		{
			SetMode( MODE::MOVE );
			gameParam->GetAttackInfo( index ).Reset();
		}
	}

	//	���@�r��
	void	Player::MagicChant( void )
	{
		//	�������Ƃ������\��ԂȂ甭���A�����s�Ȃ�ړ��ɖ߂�
		if ( inputManager->GetInputState( index, KEY_TYPE::X, KEY_STATE::UP ) )
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

		//	�r������]
		MagicChantRoll();
	}

	//	�r������]
	void	Player::MagicChantRoll( void )
	{
		float axisX = inputManager->GetInput( index ).axisX;
		float axisZ = inputManager->GetInput( index ).axisY;
		float length = sqrtf( axisX * axisX + axisZ * axisZ );

		//	���͂�����Έړ�����
		if ( length < MIN_INPUT_STICK )		return;
		{
			//	��������
			AngleAdjust(
				Vector3( axisX, 0.0f, axisZ ),
				ANGLE_ADJUST_MOVE_SPEED );
		}
	}

	//	���@�r���J�n
	void	Player::MagicChantStart( void )
	{
		//	�����Ă���ԉr���A��莞�Ԍo�߂Ŕ����\
		if ( inputManager->GetInputState( index, KEY_TYPE::X, KEY_STATE::STAY ) )
		{
			if (pParam.frame >= motionFrame[charType][FRAME_TYPE::MAGIC_CHANT_END])
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

		if (pParam.frame >= motionFrame[charType][FRAME_TYPE::DAMAGE1_END])
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
		if ( inputManager->GetInputState( index, KEY_TYPE::X, KEY_STATE::ENTER ) )
		{
			if ( SetMode( MODE::MAGICATTACK ) )
			{
				SetMotion( PLAYER_MOTION::MAGIC_CHANT_START );
				return;
			}
		}

		//	�����͎�t
		if ( inputManager->GetInputState( index, KEY_TYPE::A, KEY_STATE::ENTER ) )
		{
			if ( SetMode( MODE::STEP ) )
			{
				SetMotion( PLAYER_MOTION::STEP );
				stepSpeed = STEP_SPEED;
				return;
			}
		}

		//	���j���[���͎�t
		if ( inputManager->GetInputState( index, KEY_TYPE::START, KEY_STATE::ENTER ) )
		{
			if ( SetMode( MODE::MENU ) )
			{
				SetMotion( PLAYER_MOTION::MENU );
				return;
			}
		}
	}

	//	�ړ��l���Z
	void	Player::AddMove( Vector3& move )
	{
		collision->CheckWall( pParam.pos, move, 100.0f );
		collision->CheckDown( pParam.pos, move );
		pParam.pos += move;
	}

	//	��������
	void	Player::AngleAdjust( const Vector3& targetVec, float adjustSpeed )
	{
		//	�ړ����������߂�
		float	moveAngle = atan2f( targetVec.x, targetVec.z );

		//	�J�����̑O�����������߂�
		float	cameraAngle = gameParam->GetPlayerParam( index ).cameraAngle;

		//	���͕��������߂�
		float inputAngle = atan2f( targetVec.x, targetVec.z );

		//	�ڕW�̊p�x�����߂�
		float	targetAngle = cameraAngle + inputAngle;

		//	�e�ɓ�����
		AngleAdjustParent(
			Vector3( sinf( targetAngle ), 0.0f, cosf( targetAngle ) ),
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

	//	���W�ݒ�
	void	Player::SetPos( const Vector3& pos )
	{
		pParam.pos = pos;
	}

	//	���S�ݒ�
	void	Player::SetDeath( void )
	{
		SetMode( MODE::DEATH );
		gameParam->GetPlayerParam( index ).motion = PLAYER_MOTION::FALL;
		gameParam->GetLifeInfo( index ).active = false;
	}
