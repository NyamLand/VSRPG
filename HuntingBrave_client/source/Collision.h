
#pragma once

//****************************************************************************************
//
//	Collisionクラス
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

	enum HIT_INFO
	{
		ENEMY_HIT,
		HIT_TO_PLAYER_S,
		HIT_TO_PLAYER_L,
		HIT_TO_ENEMY
	};

	int myIndex;
	
	iexMesh*	collisionMesh;

private:
	Collision( void );
	~Collision( void );

public:
	void Initialize( int myIndex, LPSTR fileName );
	void	Release( void );
	//	当たり判定
	void	AllCollision( void );
	void	PlayerAttackCollision( int player );
	void	EnemyAttackCollision( int player );
	void	BigEnemyAttackCollision( int player );
	void	MagicCollision( void );
	bool	CheckCollision( const CollisionShape& shape1, const CollisionShape& shape2 );
	COLLISION_PAIR	GetCollisionPair( char type1, char type2 );
	CollisionShape	SetCollisionShape( char shapeType, const Vector3& vec1, const Vector3& vec2, float radius );
	
	//	ステージモデルとの当たり判定
	bool	CheckDown(Vector3& pos, Vector3& move);
	bool	CheckWall(Vector3& pos, Vector3& move, float dist);
	float	CheckDown(Vector3& pos);

	//	材質判定
	int		GetMaterial( iexMesh* obj, const Vector3& pos );

	//	ヒット情報送信
	void		SendBigHuntInfo( char enemyType );
	void		SendSmallHuntInfo( char enemyType );
	void		SendSmallEnemyAttackHit( char enemyType );

	//	当たり判定
	bool	DistCheck( const Vector3& p1, const Vector3& p2, float dist );
	float	DistancePointSegmentSq( const Vector3& p1, const Vector3& l1p1, const Vector3& l1p2 );
	float	DistanceSegmentSegmentSq( const Vector3& l1p1, const Vector3& l1p2, const Vector3& l2p1, const Vector3& l2p2 );
	bool	CapsuleVSCapsule( const Capsule& capsule1, const Capsule& capsule2 );
	bool	CapsuleVSSphere( const Capsule& capsule, const Sphere& sphere );
	bool	SphereVSSphere( const Sphere& sphere1, const Sphere& sphere2 );
};

#define	collision ( Collision::GetInstance() )
