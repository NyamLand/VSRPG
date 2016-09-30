
#pragma once

//**********************************************************************
//
//	Interpolationクラス
//
//**********************************************************************

//	include
#include	"iextreme.h"

//	class
class Interpolation
{
public:
	enum EASE_MODE
	{
		EASE_IN,		//	最初ゆったり
		EASE_OUT,	//	後ゆったり
	};
	
private:
	//	初期化・開放
	Interpolation( void ){};
	~Interpolation( void ){};

public:
	//	パラメータ更新
	static bool PercentageUpdate( float& percentage, float addParam )
	{
		//	最大値定数
		static const float PERCENTAGE_MAX = 1.0f;

		//	パラメータ加算
		percentage += addParam;

		if ( percentage >= PERCENTAGE_MAX )
		{
			percentage = PERCENTAGE_MAX;
			return	true;
		}

		return	false;
	}

	//	線形補間( 出力、初期値、最終値、割合 )
	template<typename T>
	static bool LinearInterpolation( T& out, T start, T end, float percentage )
	{
		out = ( T )( start * ( 1.0f - percentage ) + end * percentage );

		if ( percentage >= 1.0f )	return	true;
		return	false;
	}

	//	二次関数補間( 出力、初期値、最終値、割合 )
	template<typename T>
	static bool QuadraticFunctionInterpolation( T& out, T start, T end, float percentage, EASE_MODE easeMode )
	{
		float rate = 0.0f;

		//	二次関数補間
		switch ( easeMode )
		{
		case EASE_MODE::EASE_IN:
			rate = percentage * percentage;
			break;

		case EASE_MODE::EASE_OUT:
			rate = percentage * ( 2.0f - percentage );
			break;
		}

		//	補間
		return	LinearInterpolation( out, start, end, rate );
	}

	//	三次関数補間( 出力、初期値、最終値、割合 )
	template<typename T>
	static bool CubicFunctionInterpolation( T& out, T start, T end, float percentage )
	{
		//	三次関数補間
		float rate = ( percentage * percentage ) * ( 3.0f - 2.0f * percentage );

		return LinearInterpolation( out, start, end, rate );
	}

	//	cos補間( 出力、初期値、最終値、割合 )
	template<typename T>
	static bool CosineInterpolation( T& out, T start, T end, float percentage )
	{
		float rate = ( 1.0f - cosf( percentage * PI ) ) * 0.5f;
		return	LinearInterpolation( out, start, end, rate );
	}

	//	球面線形補間( 出力、初期値、最終値、割合 )
	static bool SphereInterpolation( Vector3& out, const Vector3& start, const Vector3& end, float percentage )
	{
		Vector3 s = start;
		Vector3 e = end;
		s.Normalize();
		e.Normalize();

		//	2ベクトル間の角度(鋭角側)
		float angle = acosf( Vector3Dot( s, e ) );

		//	sinθ
		float sinTh = sinf( angle );

		//	補間計数
		float ps = sinf( angle * ( 1.0f - percentage ) );
		float pe = sinf( angle * percentage );

		//	球面線形補間
		out = ( s * ps + e * pe ) / sinTh;

		//	正規化
		out.Normalize();

		//	終了していたらtrueをかえす
		if ( percentage >= 1.0f )	return	true;
	}
};
