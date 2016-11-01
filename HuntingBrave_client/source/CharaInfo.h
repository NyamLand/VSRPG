
#pragma once

//***************************************************************
//
//	Chara用構造体
//
//***************************************************************

//	include

//	攻撃情報構造体
struct AttackInfo
{
	//	定数
	enum ATTACK_PARAM
	{
		NO_ATTACK = -1,
		ATTACK1 = 1,
		ATTACK2,
	};

	//	パラメータ
	int		power;
	int		timer;
	int		step;
	bool	initFrag;
	ATTACK_PARAM	attackParam;

	//	初期化・解放
	AttackInfo( void );
	~AttackInfo( void );
};