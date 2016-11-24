
#pragma once

//****************************************************************************************
//
//	Collisionクラス
//
//****************************************************************************************

//	include
//#include	"Singleton.h"
#include	"ShapeInfo.h"

//	class
class Collision
{
public:
	//	形状組み合わせ
	enum COLLISION_PAIR
	{
		SPHEREVSSPHERE,
		SPHEREVSCAPSULE,
		CAPSULEVSSPHERE,
		CAPSULEVSCAPSULE,
	};

	//	ゲーム情報
	GameParam*	gameParam;

public:
	//	初期化・解放
	Collision( GameParam* gameParam );
	~Collision( void );

	//	当たり判定
	void	AllCollision( void );
	void	PlayerAttackCollision( void );
	void	EnemyAttackCollision( void );
	void	MagicCollision( void );
	bool	CheckCollision( const CollisionShape& shape1, const CollisionShape& shape2 );
	COLLISION_PAIR	GetCollisionPair( SHAPE_TYPE type1, SHAPE_TYPE type2 );
	CollisionShape	SetCollisionShape( char shapeType, const Vector3& vec1, const Vector3& vec2, float radius );
	//	材質判定
	int		GetMaterial( iexMesh* obj, const Vector3& pos );

	//	当たり判定
	bool	DistCheck( const Vector3& p1, const Vector3& p2, float dist );
	float	DistancePointSegmentSq( const Vector3& p1, const Vector3& l1p1, const Vector3& l1p2 );
	float	DistanceSegmentSegmentSq( const Vector3& l1p1, const Vector3& l1p2, const Vector3& l2p1, const Vector3& l2p2 );
	bool	CapsuleVSCapsule( const Capsule& capsule1, const Capsule& capsule2 );
	bool	CapsuleVSSphere( const Capsule& capsule, const Sphere& sphere );
	bool	SphereVSSphere( const Sphere& sphere1, const Sphere& sphere2 );
};
extern	Collision*	collision;
//#define	collision ( Collision::GetInstance() )
