
#pragma once

//**********************************************************************
//
//	ShapeInfo
//
//**********************************************************************

//	���\����
struct Sphere
{
	Vector3	center;
	float			r;
	Sphere( void );
	Sphere( const Vector3& center, float r );
	~Sphere( void ){};
};

//	�����\����
struct Line
{
	Vector3	point;
	Vector3	vec;
	Line( void );
	Line( const Vector3& point, const Vector3& vec );

	//	����̓_���擾
	Vector3	GetPoint( float t )const;
};

//	�J�v�Z���\����
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

//	AABB�\����
struct AABB
{
	Vector3	pos;		//	���S
	Vector3	scale;	//	�X�P�[��

	//	���ŏ����擾
	Vector3	GetMin( void )
	{
		//	�ŏ��l�����߂�
		Vector3	out = Vector3(
			pos.x - scale.x * 0.5f,
			pos.y - scale.y * 0.5f,
			pos.z - scale.z * 0.5f );

		return	out;
	}

	//	���ő���擾
	Vector3	GetMax( void )
	{
		Vector3	out = Vector3(
			pos.x + scale.x * 0.5f,
			pos.y + scale.y * 0.5f,
			pos.z + scale.z * 0.5f );

		return	out;
	}
};
