
#pragma once

//*****************************************************************************************************************************
//
//	Playerクラス
//
//*****************************************************************************************************************************

//	include
#include	"GameData.h"
#include	"BaseChara.h"
#include	"CharaInfo.h"

//	class
class Player : public BaseChara
{
private:
	PlayerParam		pParam;
	float					stepSpeed;
	Timer*				timer;
	int					index;
	char					charType;

	//	モード別関数ポインタ
	void( Player::*ModeFunction[MODE::MODE_MAX] )( void );

public:
	//	初期化・解放
	Player( int id );
	~Player( void )override;
	bool	Initialize( void );

	//	更新
	bool Update( PlayerParam& param );

	//	モード別動作関数
	void	ModeMove( void );
	void	ModeSwordAttackFirst(void);
	void	ModeSwordAttackSecond(void);
	void	ModeMagicAttack( void );
	void	ModeDamage( void );
	void	ModeDeath( void );
	void	ModeStep( void );
	void	ModeMenu( void );

	//	動作関数
	void	Move( void );
	void	SwordAttackFirst(void);
	void	SwordAttackSecond(void);
	void	CheckAttackParam( void );
	void	Damage( void );
	void	CheckInput( void );
	void	AddMove( Vector3& move );
	void	MagicAttack( void );
	void	MagicChant( void );
	void	MagicChantRoll( void );
	void	MagicChantStart( void );
	void	EffectUpdate( void );
	void	CheckUnrivaled( void );

	//	向き調整
	void	AngleAdjust( const Vector3& moveVec, float adjustSpeed );
	void	AngleAdjustParent( const Vector3& direction, float adjustSpeed );

	//	情報設定
	void	SetMotion( int motion );
	void	SetPos( const Vector3& pos );
	void	SetDeath( void );
};


