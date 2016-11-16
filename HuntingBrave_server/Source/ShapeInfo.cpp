
#include	"iextreme.h"
//#include	"GlobalFunction.h"
#include	"ShapeInfo.h"

//**********************************************************************
//
//	ShapeInfo
//
//**********************************************************************

#define	DEFAULT_RADIUS	0.5f

//---------------------------------------------------------------------------------------------
//	球構造体
//---------------------------------------------------------------------------------------------

	//	デフォルトコンストラクタ
	Sphere::Sphere( void ) : 
		center( 0.0f, 0.0f, 0.0f ), r( DEFAULT_RADIUS )
	{
	
	}

	//	コンストラクタ
	Sphere::Sphere( const Vector3& center, float r )
	{
		Set( center, r );
	}

	//	情報設定
	void	Sphere::Set( const Vector3& center, float r )
	{
		this->center = center;
		this->r = r;
	}

//---------------------------------------------------------------------------------------------
//	直線構造体
//---------------------------------------------------------------------------------------------

	//	デフォルトコンストラクタ
	Line::Line( void ) :
		point( 0.0f, 0.0f, 0.0f ), vec( 0.0f, 0.0f, 0.0f )
	{

	}

	//	コンストラクタ
	Line::Line( const Vector3& point, const Vector3& vec ) :
		point( point )
	{
		this->vec = vec;
		this->vec.Normalize();
	}

	//	線上の点を取得
	Vector3	Line::GetPoint( float t )const
	{
		Vector3	out = point + vec * t;
		return	out;
	}

//---------------------------------------------------------------------------------------------
//	線分構造体
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
//	カプセル構造体
//---------------------------------------------------------------------------------------------

	//	デフォルトコンストラクタ
	Capsule::Capsule( void ) :
		p1( 0.0f, 0.0f, 0.0f ), p2( 0.0f ,0.0f, 0.0f ), r( DEFAULT_RADIUS )
	{

	}

	//	コンストラクタ
	Capsule::Capsule( const Vector3& p1, const Vector3& p2, float r ) :
		p1( p1 ), p2( p2 ), r( r )
	{

	}

	//	情報設定
	void Capsule::Set( const Vector3& p1, const Vector3& p2, float r )
	{
		this->p1 = p1;
		this->p2 = p2;
		this->r = r;
	}

//---------------------------------------------------------------------------------------------
//	全形状まとめ
//---------------------------------------------------------------------------------------------

	//	カプセル設定
	void	CollisionShape::SetCapsule( const Capsule& capsule )
	{
		this->capsule = capsule;
		shapeType = SHAPE_TYPE::CAPSULE;
	}

	//	球設定
	void	CollisionShape::SetSphere( const Sphere& sphere )
	{
		this->sphere = sphere;
		shapeType = SHAPE_TYPE::SPHERE;
	}