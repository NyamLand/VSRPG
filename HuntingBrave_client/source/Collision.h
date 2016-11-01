
#ifndef		__COLLISION_H__
#define		__COLLISION_H__

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

private:
	Collision( void );
	~Collision( void );

public:
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

//****************************************************************************************
#endif // !__COLLISION_H__
