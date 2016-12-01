
#pragma once

//**********************************************************************
//
//	ShapeInfo
//
//**********************************************************************

//	形状種類
enum SHAPE_TYPE
{
	SPHERE,
	CAPSULE,
};

//	球構造体
struct Sphere
{
	//	パラメータ
	Vector3	center;
	float			r;

	//	初期化・解放
	Sphere( void );
	Sphere( const Vector3& center, float r );

	//	情報設定
	void	Set( const Vector3& center, float r );
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
	//	パラメータ
	Vector3	p1, p2;
	float			r;

	//	初期化・解放
	Capsule( void );
	Capsule( const Vector3& p1, const Vector3& p2, float r );
	
	//	情報設定
	void	Set( const Vector3& p1, const Vector3& p2, float r );
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


//	すべての形状まとめ
struct CollisionShape
{
	//	パラメータ
	char			shapeType;
	Sphere		sphere;
	Capsule	capsule;
};
