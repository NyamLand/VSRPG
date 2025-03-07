
#pragma once

//***************************************************************
//
//	Chara用構造体
//
//***************************************************************

//	include
#include	"ShapeInfo.h"
#include	"Timer.h"

//----------------------------------------------------------------------------------------------
//	構造体
//----------------------------------------------------------------------------------------------

	//	攻撃情報構造体
	struct AttackInfo
	{
		//	定数
		enum ATTACK_PARAM
		{
			NO_ATTACK,
			ATTACK1,
			ATTACK2,
		};

		//	パラメータ
		int	step;
		Timer	timer;

		char	shapeType;
		Vector3	vec1, vec2;
		float			radius;
		ATTACK_PARAM	attackParam;

		//	初期化・解放
		AttackInfo( void );
		void Reset( void );
	};

	//	ライフ情報構造体
	struct LifeInfo
	{
		bool		isAlive;
		bool		active;
		int		maxLife;
		int		life;

		//	初期化・解放
		LifeInfo( void );

		//	動作関数
		bool	CulcLife( int param );
		void	AddMaxLife( int param );
		void	Reset( void );

		//	情報設定
		void	Initialize( int initLife );
	};

	//	当たり判定形状構造体
	struct CollisionInfo
	{
		CollisionShape		collisionShape;
		float					height;
		float					radius;

		//	初期化
		CollisionInfo( void );
		CollisionInfo( const CollisionShape& collisionShape, float hitHeight, float hitRadius );

		//	情報設定
		void	SetCollisionShape( const CollisionShape& colShape );
		void	Set( SHAPE_TYPE shapeType, float hitHeight, float hitRadius );
	};