
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"DrawShape.h"
#include	"Interpolation.h"
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
#define	MINOTAURUS_SCALE	0.02f
#define	MINOTAURUS_HEIGHT	2.0f
#define	MINOTAURUS_RADIUS	1.5f
#define	INIT_LIFE	 5

//	����X�s�[�h
#define	ANGLE_ADJUST_SPEED	0.3f
#define	MOVE_SPEED		0.1f

//	���̑��p�����[�^
#define	ATTACK_DIST		5.0f
#define	SEARCH_DIST	10.0f

//------------------------------------------------------------------------------------
//	�������E���
//------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	BigEnemy::BigEnemy( void )
	{
		ModeFunction[MODE::ENTRY] = &BigEnemy::EntryMode;
		ModeFunction[MODE::MOVE] = &BigEnemy::MoveMode;
		ModeFunction[MODE::ATTACK] = &BigEnemy::AttackMode;
		ModeFunction[MODE::DAMAGE] = &BigEnemy::DamageMode;
		
		//	�ϐ�������
		speed = MOVE_SPEED;
		searchDist = SEARCH_DIST;
		attackDist = ATTACK_DIST;
		lifeInfo.isAlive = true;
		lifeInfo.active = false;

		

	}

	//	�f�X�g���N�^
	BigEnemy::~BigEnemy( void )
	{

	}

	//	������
	bool	BigEnemy::Initialize( void )
	{
		SetMode( MODE::ENTRY );
		SetAngle( 0.0f );
		SetScale( 0.0f );
		SetMotion( 1 );	//	���l��
		
		lifeInfo.Initialize( INIT_LIFE );
		collisionInfo.Set( SHAPE_TYPE::CAPSULE, MINOTAURUS_HEIGHT, MINOTAURUS_RADIUS );

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
	void	BigEnemy::Update( void )
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
	void	BigEnemy::EntryMode( void )
	{
		//	���
		bool	expantion = Interpolation::LinearInterpolation(
			scale, 0.0f, MINOTAURUS_SCALE, interpolationParam );

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
	void	BigEnemy::MoveMode( void )
	{
		//	�ړ�
		Move( speed );
	}

	//	�U�����[�h����
	void	BigEnemy::AttackMode( void )
	{
		SetMotion( 2 );

		//	�t���[���擾
		int frame = obj->GetFrame();

		//	�t���[������
		if ( frame >= 138 && frame <= 150 )
		{
			//	�U����Ԃ�L���ɂ���
			attackInfo.attackParam = ATTACK_PARAM::ATTACK1;
		}
		else
		{
			//	�U����Ԃ𖳌��ɂ���
			attackInfo.attackParam = ATTACK_PARAM::NO_ATTACK;

			//	�ʏ탂�[�h�ֈڍs
			if ( frame >= 170 )
				SetMode( MODE::MOVE );
		}
	}


	
//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------

	void	BigEnemy::Attack()
	{

	}

//------------------------------------------------------------------------------------
//	���ݒ�
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	���擾
//------------------------------------------------------------------------------------

