
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

//	class
class BaseChara
{
protected:
	AttackInfo	attackInfo;
	LifeInfo			lifeInfo;
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
	AttackInfo	GetAttackInfo( void )const;
	LifeInfo			GetLifeInfo( void )const ;
};
