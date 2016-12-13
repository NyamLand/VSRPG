#pragma once

//***************************************************************
//
//	Enemyクラス
//
//***************************************************************

//	include
#include	"Enemy.h"

//	class
class BigEnemy : public Enemy
{

	

	//	モード別関数ポインタ
	void( BigEnemy::*ModeFunction[MODE_MAX] )( void );

public:
	//	初期化・解放
	BigEnemy( void );
	~BigEnemy( void )override;
	bool	Initialize( void )override;

	//	更新
	void	Update( void );

	//	各モード動作関数
	void	EntryMode( void )override;
	void	MoveMode( void )override;
	void	AttackMode( void )override;
	void	DeadMode(void)override;
	//void	DamageMode( void );
	//bool	DamageFlgCheck( void )override;
	//	動作関数

	//	攻撃関数
	void	Attack( void )override;


};