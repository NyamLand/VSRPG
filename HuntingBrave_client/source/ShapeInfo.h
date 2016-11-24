
#pragma once

//**********************************************************************
//
//	ShapeInfo
//
//**********************************************************************

//	�`����
enum SHAPE_TYPE
{
	SPHERE,
	CAPSULE,
};

//	���\����
struct Sphere
{
	//	�p�����[�^
	Vector3	center;
	float			r;

	//	�������E���
	Sphere( void );
	Sphere( const Vector3& center, float r );

	//	���ݒ�
	void	Set( const Vector3& center, float r );
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
	//	�p�����[�^
	Vector3	p1, p2;
	float			r;

	//	�������E���
	Capsule( void );
	Capsule( const Vector3& p1, const Vector3& p2, float r );
	
	//	���ݒ�
	void	Set( const Vector3& p1, const Vector3& p2, float r );
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


//	���ׂĂ̌`��܂Ƃ�
struct CollisionShape
{
	//	�p�����[�^
	char			shapeType;
	Sphere		sphere;
	Capsule	capsule;
};
