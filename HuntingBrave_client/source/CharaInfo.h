
#pragma once

//***************************************************************
//
//	Chara用構造体
//
//***************************************************************

//	include
#include	"ShapeInfo.h"

namespace
{
	//	定数
	enum ATTACK_PARAM
	{
		NO_ATTACK,
		ATTACK1,
		ATTACK2,
	};

	//	当たり判定形状
	enum COLLISION_SHAPE
	{
		CAPSULE,
		SPHERE,
	};
}


//	攻撃情報構造体
struct AttackInfo
{
	//	パラメータ
	char			shape;
	float			radius;
	Vector3	pos1;
	Vector3	pos2;
	void	Set( char shape, float radius, const Vector3& pos1, const Vector3& pos2 )
	{
		this->shape = shape;
		this->radius = radius;
		this->pos1 = pos1;
		this->pos2 = pos2;
	}
};

//	ライフ情報構造体
struct LifeInfo
{
	bool		isAlive;
	bool		active;
	int		maxLife;
	int		life;

	//	初期化・解放
	LifeInfo( void );

	//	動作関数
	void	CulcLife( int param );
	void	Reset( void );
	
	//	情報設定
	void	Initialize( int initLife );
};

//	当たり判定形状構造体
struct CollisionInfo
{
	CollisionShape		collisionShape;
	float					height;
	float					radius;

	//	初期化
	CollisionInfo( void );
	CollisionInfo( const CollisionShape& collisionShape, float hitHeight, float hitRadius );

	//	情報設定
	void	SetCollisionShape( const CollisionShape& colShape );
	void	Set( SHAPE_TYPE shapeType, float hitHeight, float hitRadius );
};