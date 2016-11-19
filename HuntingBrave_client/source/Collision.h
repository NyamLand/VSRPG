
#pragma once

//****************************************************************************************
//
//	CollisionÉNÉâÉX
//
//****************************************************************************************

//	include
#include	"Singleton.h"
#include	"ShapeInfo.h"

//	class
class Collision : public Singleton<Collision>
{
	friend Singleton<Collision>;

public:
	enum COLLISION_PAIR
	{
		SPHEREVSSPHERE,
		SPHEREVSCAPSULE,
		CAPSULEVSSPHERE,
		CAPSULEVSCAPSULE,
	};

private:
	Collision( void );
	~Collision( void );

public:
	//	ìñÇΩÇËîªíË
	void	AllCollision( void );
	void	PlayerAttackCollision( void );
	void	EnemyAttackCollision( void );
	bool	CheckCollision( const CollisionShape& shape1, const CollisionShape& shape2 );
	COLLISION_PAIR	GetCollisionPair( char type1, char type2 );

	//	çﬁéøîªíË
	int		GetMaterial( iexMesh* obj, const Vector3& pos );

	//	ìñÇΩÇËîªíË
	bool	DistCheck( const Vector3& p1, const Vector3& p2, float dist );
	float	DistancePointSegmentSq( const Vector3& p1, const Vector3& l1p1, const Vector3& l1p2 );
	float	DistanceSegmentSegmentSq( const Vector3& l1p1, const Vector3& l1p2, const Vector3& l2p1, const Vector3& l2p2 );
	bool	CapsuleVSCapsule( const Capsule& capsule1, const Capsule& capsule2 );
	bool	CapsuleVSSphere( const Capsule& capsule, const Sphere& sphere );
	bool	SphereVSSphere( const Sphere& sphere1, const Sphere& sphere2 );
};

#define	collision ( Collision::GetInstance() )
