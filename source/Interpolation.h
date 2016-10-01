
#pragma once

//**********************************************************************
//
//	Interpolation�N���X
//
//**********************************************************************

//	include
#include	"iextreme.h"
#include	"Singleton.h"

//	class
class Interpolation
{
public:
	enum EASE_MODE
	{
		EASE_IN,		//	�ŏ��������
		EASE_OUT,	//	��������
	};
	
public:
	//	�p�����[�^�X�V
	static bool PercentageUpdate( float& percentage, float addParam )
	{
		//	�ő�l�萔
		static const float PERCENTAGE_MAX = 1.0f;

		//	�p�����[�^���Z
		percentage += addParam;

		if ( percentage >= PERCENTAGE_MAX )
		{
			percentage = PERCENTAGE_MAX;
			return	true;
		}

		return	false;
	}

	//	���`���( �o�́A�����l�A�ŏI�l�A���� )
	template<typename T>
	static bool LinearInterpolation( T& out, T start, T end, float percentage )
	{
		out = ( T )( start * ( 1.0f - percentage ) + end * percentage );

		if ( percentage >= 1.0f )	return	true;
		return	false;
	}

	//	�񎟊֐����( �o�́A�����l�A�ŏI�l�A���� )
	template<typename T>
	static bool QuadraticFunctionInterpolation( T& out, T start, T end, float percentage, EASE_MODE easeMode )
	{
		float rate = 0.0f;

		//	�񎟊֐����
		switch ( easeMode )
		{
		case EASE_MODE::EASE_IN:
			rate = percentage * percentage;
			break;

		case EASE_MODE::EASE_OUT:
			rate = percentage * ( 2.0f - percentage );
			break;
		}

		//	���
		return	LinearInterpolation( out, start, end, rate );
	}

	//	�O���֐����( �o�́A�����l�A�ŏI�l�A���� )
	template<typename T>
	static bool CubicFunctionInterpolation( T& out, T start, T end, float percentage )
	{
		//	�O���֐����
		float rate = ( percentage * percentage ) * ( 3.0f - 2.0f * percentage );

		return LinearInterpolation( out, start, end, rate );
	}

	//	cos���( �o�́A�����l�A�ŏI�l�A���� )
	template<typename T>
	static bool CosineInterpolation( T& out, T start, T end, float percentage )
	{
		float rate = ( 1.0f - cosf( percentage * PI ) ) * 0.5f;
		return	LinearInterpolation( out, start, end, rate );
	}

	//	���ʐ��`���( �o�́A�����l�A�ŏI�l�A���� )
	static bool SphereInterpolation( Vector3& out, const Vector3& start, const Vector3& end, float percentage )
	{
		Vector3 s = start;
		Vector3 e = end;
		s.Normalize();
		e.Normalize();

		//	2�x�N�g���Ԃ̊p�x(�s�p��)
		float angle = acosf( Vector3Dot( s, e ) );

		//	sin��
		float sinTh = sinf( angle );

		//	��Ԍv��
		float ps = sinf( angle * ( 1.0f - percentage ) );
		float pe = sinf( angle * percentage );

		//	���ʐ��`���
		out = ( s * ps + e * pe ) / sinTh;

		//	���K��
		out.Normalize();

		//	�I�����Ă�����true��������
		if ( percentage >= 1.0f )	return	true;
	}
};
