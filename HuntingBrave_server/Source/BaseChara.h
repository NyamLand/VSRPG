
#pragma once

//*****************************************************************************************************************************
//
//	BaseCharaクラス
//
//*****************************************************************************************************************************

//	include
#include	"CharaInfo.h"

//	enum
namespace MODE
{
	//	モード番号
	enum 
	{
		MOVE,
		SWOADATTACK,
		MAGICATTACK,
		AVOID,
		DAMAGE,
		MODE_MAX
	};
}

//	class
class BaseChara
{
protected:
	AttackInfo	attackInfo;
	LifeInfo			lifeInfo;
	Vector3	pos;
	float			angle;
	int			mode;
	int			motion;

public:
	//	初期化・解放
	BaseChara( void );
	virtual ~BaseChara( void );

	//	情報設定
	bool	SetMode( int nextMode );
	void	SetAttackInfo( const AttackInfo& attackInfo );

	//	情報取得
	Vector3	GetPos( void )const;
	AttackInfo	GetAttackInfo( void )const;
	LifeInfo			GetLifeInfo( void )const ;
};
