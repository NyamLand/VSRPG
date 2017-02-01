
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"DrawShape.h"
#include	"Interpolation.h"
#include	"Sound.h"
#include	"PlayerManager.h"
#include	"Random.h"

#include	"Moffu.h"

//***************************************************************
//
//	SmallEnemy�N���X
//
//***************************************************************

//------------------------------------------------------------------------------------
//	�O���[�o��
//------------------------------------------------------------------------------------

//	���b�t
#define	MOFFU_SCALE		0.1f
#define	MOFFU_HEIGHT	0.125f
#define	MOFFU_RADIUS	1.0f

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
		const int ATTACK_HIT_START = 138;
		const int ATTACK_HIT_END = 150;
		const int DEAD_START = 225;
		const int FALL_END = 493;
	}

	namespace MOFUMOFU
	{
		const LPSTR mofooTex0[] =
		{
			"DATA/CHR/Enemy/mofumofu/mofoo.png",
			"DATA/CHR/Enemy/mofumofu/ao_mofoo.png",
			"DATA/CHR/Enemy/mofumofu/metaru_mofoo.png",
			"DATA/CHR/Enemy/mofumofu/yuki_mofoo.png"
		};

		const LPSTR mofooTex1[] =
		{
			"DATA/CHR/Enemy/mofumofu/mofoo_trans.png",
			"DATA/CHR/Enemy/mofumofu/ao_mofoo_trans.png",
			"DATA/CHR/Enemy/mofumofu/metaru_mofoo_trans.png",
			"DATA/CHR/Enemy/mofumofu/yuki_mofoo_trans.png"
		};

		enum MOFU_TYPE
		{
			NORMAL_MOFU,
			AO_MOFU,
			METARU_MOFU,
			YUKI_MOFU,
			MOFU_MAX
		};
	}
}

//------------------------------------------------------------------------------------
//	�������E���
//------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	Moffu::Moffu( void ) 
	{
		ModeFunction[MODE::ENTRY] = &Moffu::EntryMode;
		ModeFunction[MODE::WAIT] = &Moffu::WaitMode;
		ModeFunction[MODE::MOVE] = &Moffu::MoveMode;
		ModeFunction[MODE::ATTACK] = &Moffu::AttackMode;
		ModeFunction[MODE::DAMAGE] = &Moffu::DamageMode;
		ModeFunction[MODE::DEAD] = &Moffu::DeadMode;

		//	�ϐ�������
		speed = MOVE_SPEED;
		searchDist = SEARCH_DIST;
		attackDist = ATTACK_DIST;
		lifeInfo.active = false;
		lifeInfo.isAlive = true;
		enemyType = ENEMY_TYPE::MOFFU;
	}

	//	�f�X�g���N�^
	Moffu::~Moffu(void)
	{

	}

	//	������
	bool	Moffu::Initialize( int life )
	{
		SetMode( MODE::ENTRY );
		SetAngle( 0.0f );
		SetScale( 0.0f );
		SetMotion( 1 );	//	���l��

		//	���C�t������
		lifeInfo.Initialize( life );

		//	�U����񏉊���
		ZeroMemory( &attackInfo, sizeof( AttackInfo ) );

		//	�����蔻���񏉊���
		collisionInfo.Set( SHAPE_TYPE::CAPSULE, MOFFU_HEIGHT, MOFFU_RADIUS );

		//	HP�o�[������
		bar = new EnemyHpUI();
		bar->Initilaize( HPUI_TYPE::ENEMY, GetLifeInfo().maxLife );
		
		//	�e�N�X�`�������ւ�
		texType = random->GetInt( 0, MOFUMOFU::MOFU_MAX - 1 );

		//	���X�V
		UpdateInfo();

		if ( obj == nullptr )	return	false;
		return	true;
	}

//------------------------------------------------------------------------------------
//	�X�V�E�`��
//-----------------------------------------------------------------------------------

	//	�X�V
	void	Moffu::Update(void)
	{
		//	�e���[�h�ɉ���������֐�
		( this->*ModeFunction[mode] )();

		BaseChara::Update();
	}

	//	�`��
	void	Moffu::Render(iexShader* shader, LPSTR technique)
	{
		//	���X�V
		obj->SetTexture( 0, MOFUMOFU::mofooTex0[texType] );
		obj->SetTexture( 1, MOFUMOFU::mofooTex1[texType] );

		//	�`��
		BaseChara::Render( shader, technique );
	}

//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------

	//	�o�������[�h����
	void	Moffu::EntryMode(void)
	{
		//	���
		bool	expantion = Interpolation::LinearInterpolation(
			scale, 0.0f, MOFFU_SCALE, interpolationParam );

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
	void	Moffu::MoveMode(void)
	{
		//	�ړ�
		Move( speed );
	}

	//	�U�����[�h����
	void	Moffu::AttackMode(void)
	{
		SetMotion( 2 );

		//	�t���[���擾
		int frame = obj->GetFrame();

		//	�t���[������
		if ( frame >= MOTION_FRAME::ATTACK_HIT_START 
			&& frame <= MOTION_FRAME::ATTACK_HIT_END )
		{
			//	�U����Ԃ�L���ɂ���
			attackInfo.Set(SHAPE_TYPE::SPHERE, MOFFU_RADIUS, pos + (GetFront() * MOFFU_RADIUS), Vector3(0, 0, 0));
			attackInfo.attackParam = ATTACK_PARAM::ATTACK1;
		}
		else
		{
			//	�U����Ԃ𖳌��ɂ���
			attackInfo.attackParam = ATTACK_PARAM::NO_ATTACK;

			//	�ʏ탂�[�h�ֈڍs
			if (frame >= 170)
				SetMode( MODE::WAIT );
		}
	}

	void	Moffu::DeadMode(void)
	{
		SetMotion(3);
		static float alpha = 1.0f;

		//	�t���[���擾
		int frame = obj->GetFrame();

		//	�t���[������
		if ( frame >= MOTION_FRAME::DEAD_START )
		{
			//	���ߊJ�n
			alpha -= 0.1f;
			if ( alpha <= 0.0f )
			{
				lifeInfo.isAlive = false;
				sound->PlaySE(SE::ENEMY_DEAD);
			}
		}
		
	}
//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------

	//	�U��
	void	Moffu::Attack(void)
	{

	}
	
//------------------------------------------------------------------------------------
//	���ݒ�
//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
//	���擾
//------------------------------------------------------------------------------------

