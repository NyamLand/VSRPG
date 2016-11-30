
#pragma once

//***************************************************************
//
//	Chara�p�\����
//
//***************************************************************

//	include
#include	"ShapeInfo.h"

namespace
{
	//	�萔
	enum ATTACK_PARAM
	{
		NO_ATTACK,
		ATTACK1,
		ATTACK2,
	};

	//	�����蔻��`��
	enum COLLISION_SHAPE
	{
		CAPSULE,
		SPHERE,
	};
}


//	�U�����\����
struct AttackInfo
{
	//	�p�����[�^
	char			attackParam;
	char			shape;
	float			radius;
	Vector3	vec1;
	Vector3	vec2;
	void	Set( char shape, float radius, const Vector3& vec1, const Vector3& vec2 )
	{
		this->shape = shape;
		this->radius = radius;
		this->vec1 = vec1;
		this->vec2 = vec2;
	}
};

//	���C�t���\����
struct LifeInfo
{
	bool		isAlive;
	bool		active;
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