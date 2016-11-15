
#pragma once

//***************************************************************
//
//	Chara�p�\����
//
//***************************************************************

//	include
#include	"ShapeInfo.h"

//----------------------------------------------------------------------------------------------
//	�\����
//----------------------------------------------------------------------------------------------

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
		bool	active;
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

	//	�����蔻��`��\����
	struct CollisionInfo
	{
		CollisionShape		collisionShape;
		float					height;
		float					radius;

		//	������
		CollisionInfo( void );
		CollisionInfo( const CollisionShape& collisionShape, float hitHeight, float hitRadius );

		//	���ݒ�
		void	SetCollisionShape( const CollisionShape& colShape );
		void	Set( SHAPE_TYPE shapeType, float hitHeight, float hitRadius );
	};