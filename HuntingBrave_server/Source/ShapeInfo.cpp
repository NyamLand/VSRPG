
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
//	���\����
//---------------------------------------------------------------------------------------------

	//	�f�t�H���g�R���X�g���N�^
	Sphere::Sphere( void ) : 
		center( 0.0f, 0.0f, 0.0f ), r( DEFAULT_RADIUS )
	{
	
	}

	//	�R���X�g���N�^
	Sphere::Sphere( const Vector3& center, float r )
	{
		Set( center, r );
	}

	//	���ݒ�
	void	Sphere::Set( const Vector3& center, float r )
	{
		this->center = center;
		this->r = r;
	}

//---------------------------------------------------------------------------------------------
//	�����\����
//---------------------------------------------------------------------------------------------

	//	�f�t�H���g�R���X�g���N�^
	Line::Line( void ) :
		point( 0.0f, 0.0f, 0.0f ), vec( 0.0f, 0.0f, 0.0f )
	{

	}

	//	�R���X�g���N�^
	Line::Line( const Vector3& point, const Vector3& vec ) :
		point( point )
	{
		this->vec = vec;
		this->vec.Normalize();
	}

	//	����̓_���擾
	Vector3	Line::GetPoint( float t )const
	{
		Vector3	out = point + vec * t;
		return	out;
	}

//---------------------------------------------------------------------------------------------
//	�����\����
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
//	�J�v�Z���\����
//---------------------------------------------------------------------------------------------

	//	�f�t�H���g�R���X�g���N�^
	Capsule::Capsule( void ) :
		p1( 0.0f, 0.0f, 0.0f ), p2( 0.0f ,0.0f, 0.0f ), r( DEFAULT_RADIUS )
	{

	}

	//	�R���X�g���N�^
	Capsule::Capsule( const Vector3& p1, const Vector3& p2, float r ) :
		p1( p1 ), p2( p2 ), r( r )
	{

	}

	//	���ݒ�
	void Capsule::Set( const Vector3& p1, const Vector3& p2, float r )
	{
		this->p1 = p1;
		this->p2 = p2;
		this->r = r;
	}

//---------------------------------------------------------------------------------------------
//	�S�`��܂Ƃ�
//---------------------------------------------------------------------------------------------

	//	�J�v�Z���ݒ�
	void	CollisionShape::SetCapsule( const Capsule& capsule )
	{
		this->capsule = capsule;
		shapeType = SHAPE_TYPE::CAPSULE;
	}

	//	���ݒ�
	void	CollisionShape::SetSphere( const Sphere& sphere )
	{
		this->sphere = sphere;
		shapeType = SHAPE_TYPE::SPHERE;
	}