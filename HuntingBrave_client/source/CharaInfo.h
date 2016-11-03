
#pragma once

//***************************************************************
//
//	Chara用構造体
//
//***************************************************************

//	include
#include	"ShapeInfo.h"

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
	int		power;
	int		timer;
	int		step;
	bool	initFlag;
	ATTACK_PARAM	attackParam;
	CollisionShape		collisionShape;

	//	初期化・解放
	AttackInfo( void );
	void Reset( void );
};

//	ライフ情報構造体
struct LifeInfo
{
	bool	isAlive;
	int		maxLife;
	int		life;

	//	初期化・解放
	LifeInfo( void );

	//	動作関数
	void	CulcLife( int param );
	void	Reset( void );
	
	//	情報設定
	void	Initialize( int initLife );
};