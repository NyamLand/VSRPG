
#pragma once

//***************************************************************
//
//	Enemyクラス
//
//***************************************************************

//	include
#include	"Enemy.h"

//	class
class SmallEnemy : public Enemy
{
private:

	//	モード別関数ポインタ
	void( SmallEnemy::*ModeFunction[MODE_MAX] )( void );

public:
	//	初期化・解放
	SmallEnemy( void );
	~SmallEnemy( void )override;
	bool	Initialize( void )override;

	//	更新
	void	Update( void )override;

	//	各モード動作関数
	void	EntryMode( void )override;
	void	MoveMode( void )override;
	void	AttackMode( void )override;
	void	DeadMode( void )override;
	
	//	動作関数

	//	攻撃関数
	void	Attack( void )override;


};