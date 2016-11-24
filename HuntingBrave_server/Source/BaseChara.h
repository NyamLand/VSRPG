
#pragma once

//*****************************************************************************************************************************
//
//	BaseChara�N���X
//
//*****************************************************************************************************************************

//	include
#include	"CharaInfo.h"

//	enum
namespace MODE
{
	//	���[�h�ԍ�
	enum 
	{
		MOVE,
		SWOADATTACK,
		MAGICATTACK,
		AVOID,
		DAMAGE,
		MODE_MAX
	};
}

//	�萔�֘A
namespace
{
	//	���[�V�����ԍ�
	enum PLAYER_MOTION
	{
		POSUTURE,						//	�ҋ@
		RUN_START,						//	����o��
		RUN,									//	����
		ATTACK1,							//	�U���P
		ATTACK2,							//	�U���Q
		STEP,								//	�X�e�b�v
		MAGIC_CHANT_START,		//	�r���J�n
		MAGIC_CHANT,					//	�r����
		MAGIC_ACTIVATION,			//	���@����
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

//	class
class BaseChara
{
protected:
	Vector3	pos;
	float			angle;
	int			mode;
	int			motion;

public:
	//	�������E���
	BaseChara( void );
	virtual ~BaseChara( void );

	//	���ݒ�
	bool	SetMode( int nextMode );
	void	SetAttackInfo( const AttackInfo& attackInfo );

	//	���擾
	Vector3	GetPos( void )const;
};
