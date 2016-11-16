
#pragma once

//*****************************************************************************************************************************
//
//	Playerクラス
//
//*****************************************************************************************************************************

//	include
#include	"GameData.h"
#include	"BaseChara.h"

//	class
class Player : public BaseChara
{
private:
	PlayerParam	pParam;
	int		index;

	//	モード別関数ポインタ
	void( Player::*ModeFunction[MODE::MODE_MAX] )( void );

public:
	//	初期化・解放
	Player( int id );
	~Player( void )override;

	//	更新
	bool Update( PlayerParam& param );

	//	モード別動作関数
	void	ModeMove( void );
	void	ModeSwordAttack( void );

	//	動作関数
	void	Move( void );
	void	SwordAttack( void );
	void	Damage( void );
	void	AngleAdjust( const Vector3& moveVec, float adjustSpeed );
	void	AngleAdjustParent( const Vector3& direction, float adjustSpeed );

	//	情報設定
	void	SetMotion( int motion );
};


