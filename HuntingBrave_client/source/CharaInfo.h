
#pragma once

//***************************************************************
//
//	Chara�p�\����
//
//***************************************************************

//	include
#include	"ShapeInfo.h"

//	�U�����\����
struct AttackInfo
{
	//	�萔
	enum ATTACK_PARAM
	{
		NO_ATTACK,
		ATTACK1,
		ATTACK2,
	};

	//	�p�����[�^
	int		power;
	int		timer;
	int		step;
	bool	initFlag;
	ATTACK_PARAM	attackParam;
	CollisionShape		collisionShape;

	//	�������E���
	AttackInfo( void );
	void Reset( void );
};

//	���C�t���\����
struct LifeInfo
{
	bool	isAlive;
	int		maxLife;
	int		life;

	//	�������E���
	LifeInfo( void );

	//	����֐�
	void	CulcLife( int param );
	void	Reset( void );
	
	//	���ݒ�
	void	Initialize( int initLife );
};