
#pragma once

//***************************************************************
//
//	Chara�p�\����
//
//***************************************************************

//	include

//	�U�����\����
struct AttackInfo
{
	//	�萔
	enum ATTACK_PARAM
	{
		NO_ATTACK = -1,
		ATTACK1 = 1,
		ATTACK2,
	};

	//	�p�����[�^
	int		power;
	int		timer;
	int		step;
	bool	initFrag;
	ATTACK_PARAM	attackParam;

	//	�������E���
	AttackInfo( void );
	~AttackInfo( void );
};