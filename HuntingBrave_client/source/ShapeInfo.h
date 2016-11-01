
#pragma once

//**********************************************************************
//
//	ShapeInfo
//
//**********************************************************************

//	球構造体
struct Sphere
{
	Vector3	center;
	float			r;
	Sphere( void );
	Sphere( const Vector3& center, float r );
	~Sphere( void ){};
};

//	直線構造体
struct Line
{
	Vector3	point;
	Vector3	vec;
	Line( void );
	Line( const Vector3& point, const Vector3& vec );

	//	線上の点を取得
	Vector3	GetPoint( float t )const;
};

//	カプセル構造体
struct Capsule
{
	Vector3	p1, p2;
	float			r;
	Capsule( void );
	Capsule( const Vector3& p1, const Vector3& p2, float r );
	void	SetPos( const Vector3& P1, const Vector3& P2 );
	void	SetRadius( float r );
	~Capsule( void ){}
};

//	AABB構造体
struct AABB
{
	Vector3	pos;		//	中心
	Vector3	scale;	//	スケール

	//	軸最小を取得
	Vector3	GetMin( void )
	{
		//	最小値を求める
		Vector3	out = Vector3(
			pos.x - scale.x * 0.5f,
			pos.y - scale.y * 0.5f,
			pos.z - scale.z * 0.5f );

		return	out;
	}

	//	軸最大を取得
	Vector3	GetMax( void )
	{
		Vector3	out = Vector3(
			pos.x + scale.x * 0.5f,
			pos.y + scale.y * 0.5f,
			pos.z + scale.z * 0.5f );

		return	out;
	}
};
