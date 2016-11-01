
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
	enum MODE	//	仮
	{
		MOVE,
		//POSTURE,
		MODE_MAX
	};


public:
	//	初期化・解放
	SmallEnemy( void );
	~SmallEnemy( void )override;
	bool	Initialize( void )override;

	//	更新・描画

	//	各モード動作関数
	void	MoveMode( void );
	//void	PostureMode( void );

	//	動作関数

	//	攻撃関数
	void	Attack( void )override;


};