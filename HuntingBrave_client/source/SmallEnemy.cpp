
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"DrawShape.h"
#include	"Interpolation.h"
#include	"PlayerManager.h"

#include	"SmallEnemy.h"

//***************************************************************
//
//	SmallEnemy�N���X
//
//***************************************************************

//------------------------------------------------------------------------------------
//	�O���[�o��
//------------------------------------------------------------------------------------

//	�~�m�^�E���X
#define	MINOTAURUS_SCALE	0.01f
#define	MINOTAURUS_HEIGHT	0.125f
#define	MINOTAURUS_RADIUS	1.0f

#define	INIT_LIFE	100

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
	SmallEnemy::SmallEnemy( void )
	{
		ModeFunction[MODE::ENTRY] = &SmallEnemy::EntryMode;
		ModeFunction[MODE::MOVE] = &SmallEnemy::MoveMode;
		ModeFunction[MODE::ATTACK] = &SmallEnemy::AttackMode;

		//	�ϐ�������
		speed = MOVE_SPEED;
		searchDist = SEARCH_DIST;
		attackDist = ATTACK_DIST;
		lifeInfo.active = false;
		lifeInfo.isAlive = true;
	}

	//	�f�X�g���N�^
	SmallEnemy::~SmallEnemy( void )
	{

	}

	//	������
	bool	SmallEnemy::Initialize( void )
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

//------------------------------------------------------------------------------------
//	�X�V�E�`��
//-----------------------------------------------------------------------------------

	//	�X�V
	void	SmallEnemy::Update( void )
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
	void	SmallEnemy::EntryMode( void )
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
	void	SmallEnemy::MoveMode( void )
	{
		//	�ړ�
		Move( speed );
	}

	//	�U�����[�h����
	void	SmallEnemy::AttackMode( void )
	{
		SetMotion( 2 );

		//	�t���[���擾
		int frame = obj->GetFrame();

		//	�t���[������
		if ( frame >= 138 && frame <= 150 )
		{
			//	�U����Ԃ�L���ɂ���
			attackInfo.attackParam = AttackInfo::ATTACK1;
		}
		else
		{
			//	�U����Ԃ𖳌��ɂ���
			attackInfo.attackParam = AttackInfo::NO_ATTACK;

			//	�ʏ탂�[�h�ֈڍs
			if ( frame >= 170 )
				SetMode( MODE::MOVE );
		}
	}

//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------

	//	�U��
	void	SmallEnemy::Attack( void )
	{

	}
	
//------------------------------------------------------------------------------------
//	���ݒ�
//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
//	���擾
//------------------------------------------------------------------------------------

