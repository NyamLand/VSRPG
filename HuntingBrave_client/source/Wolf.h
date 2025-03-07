#pragma once

//***************************************************************
//
//	Enemyクラス
//
//***************************************************************

//	include
#include	"Enemy.h"

//	class
class Wolf : public Enemy
{
private:
	//	モード別関数ポインタ
	void(Wolf::*ModeFunction[MODE_MAX])(void);

public:
	//	初期化・解放
	Wolf(void);
	~Wolf(void)override;
	bool	Initialize( int life );

	//	更新
	void	Update( void );

	//	各モード動作関数
	void	EntryMode( void )override;
	void	MoveMode( void )override;
	void	AttackMode( void )override;
	void	DeadMode( void )override;
	//	動作関数

	//	攻撃関数
	void	Attack( void )override;


};