
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"DrawShape.h"
#include	"Sound.h"
#include	"Interpolation.h"
#include	"Wolf.h"

//***************************************************************
//
//	Enemy�N���X
//
//***************************************************************

//------------------------------------------------------------------------------------
//	�O���[�o��
//------------------------------------------------------------------------------------

//	���f�����
#define	WOLF_SCALE	0.1f
#define	WOLF_HEIGHT	2.0f
#define	WOLF_RADIUS	2.0f

//	����X�s�[�h
#define	ANGLE_ADJUST_SPEED	0.3f
#define	MOVE_SPEED		0.18f

//	���̑��p�����[�^
#define	ATTACK_DIST		5.0f
#define	SEARCH_DIST	10.0f

//���[�V�����t���[��
namespace
{
	namespace MOTION_FRAME
	{
		const int ATTACK_HIT_START = 195;
		const int ATTACK_HIT_END = 240;
		const int DEAD_START = 321;
		const int FALL_END = 335;
	}
}
//------------------------------------------------------------------------------------
//	�������E���
//------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	Wolf::Wolf(void)
	{
		ModeFunction[MODE::ENTRY] = &Wolf::EntryMode;
		ModeFunction[MODE::WAIT] = &Wolf::WaitMode;
		ModeFunction[MODE::MOVE] = &Wolf::MoveMode;
		ModeFunction[MODE::ATTACK] = &Wolf::AttackMode;
		ModeFunction[MODE::DAMAGE] = &Wolf::DamageMode;
		ModeFunction[MODE::DEAD] = &Wolf::DeadMode;
		
		//	�ϐ�������
		speed = MOVE_SPEED;
		searchDist = SEARCH_DIST;
		attackDist = ATTACK_DIST;
		lifeInfo.isAlive = true;
		lifeInfo.active = false;
		enemyType = ENEMY_TYPE::WOLF;
	}

	//	�f�X�g���N�^
	Wolf::~Wolf(void)
	{

	}

	//	������
	bool	Wolf::Initialize( int life )
	{
		SetMode( MODE::ENTRY );
		SetAngle( 0.0f );
		SetScale( 0.0f );
		SetMotion( 1 );	//	���l��
		
		lifeInfo.Initialize( life );
		ZeroMemory( &attackInfo, sizeof( AttackInfo ) );
		collisionInfo.Set(SHAPE_TYPE::CAPSULE, WOLF_HEIGHT, WOLF_RADIUS);

		bar = new EnemyHpUI();
		bar->Initilaize(HPUI_TYPE::ENEMY, GetLifeInfo().maxLife);
		//	���X�V
		UpdateInfo();

		if ( obj == nullptr )	return	false;
		return	true;
	}

	//	���

//------------------------------------------------------------------------------------
//	�X�V�E�`��
//------------------------------------------------------------------------------------

	//	�X�V
	void	Wolf::Update(void)
	{
		//	�e���[�h�ɉ���������֐�
		( this->*ModeFunction[mode] )();

		//	���X�V
		BaseChara::Update();
	}

//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------

	//	�o�������[�h����
	void	Wolf::EntryMode(void)
	{
		//	���
		bool	expantion = Interpolation::LinearInterpolation(
			scale, 0.0f, WOLF_SCALE, interpolationParam);

		//	��ԃp�����[�^�X�V
		Interpolation::PercentageUpdate( interpolationParam, 0.01f );

		//	��ԏI����ړ�
		if ( expantion )
		{
			lifeInfo.active = true;
			SetMode( MODE::MOVE );
		}
	}

	//	�ړ����[�h����
	void	Wolf::MoveMode(void)
	{
		//	�ړ�
		Move( speed );
	}

	//	�U�����[�h����
	void	Wolf::AttackMode(void)
	{
		SetMotion( 2 );

		//	�t���[���擾
		int frame = obj->GetFrame();

		//	�t���[������
		if ( frame >= MOTION_FRAME::ATTACK_HIT_START 
			&& frame <= MOTION_FRAME::ATTACK_HIT_END )
		{
			//	�U����Ԃ�L���ɂ���
			attackInfo.Set(SHAPE_TYPE::SPHERE, WOLF_RADIUS, pos + (GetFront() * WOLF_RADIUS), Vector3(0, 0, 0));
			attackInfo.attackParam = ATTACK_PARAM::ATTACK1;
		}
		else
		{
			//	�U����Ԃ𖳌��ɂ���
			attackInfo.attackParam = ATTACK_PARAM::NO_ATTACK;

			//	�ʏ탂�[�h�ֈڍs
			if (frame >= 245)
				
				SetMode( MODE::WAIT );
		}
	}


	void	Wolf::DeadMode(void)
	{
		SetMotion(3);
		static float alpha = 1.0f;

		//	�t���[���擾
		int frame = obj->GetFrame();

		//	�t���[������
		if (frame >= MOTION_FRAME::DEAD_START)
		{
			//	���ߊJ�n
			alpha -= 0.1f;
			if ( frame >= MOTION_FRAME::FALL_END )
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

	void	Wolf::Attack()
	{

	}

//------------------------------------------------------------------------------------
//	���ݒ�
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	���擾
//------------------------------------------------------------------------------------

