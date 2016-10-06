
#pragma once

//***************************************************************
//
//	Enemyクラス
//
//***************************************************************

//	include
#include	"BaseChara.h"

//	class
class Enemy : public BaseChara
{
private:
	enum MODE	//	仮
	{
		MOVE,
		//POSTURE,
		MODE_MAX
	};

	//	モード別関数ポインタ
	void(Enemy::*ModeFunction[MODE_MAX])(void);

public:
	//	初期化・解放
	Enemy(void);
	~Enemy(void)override;
	bool	Initialize(void)override;

	//	更新・描画
	void	Update(void)override;

	//	各モード動作関数
	void	MoveMode(void);
	//void	PostureMode( void );

	//	動作関数
	void	Move(void);

	//	攻撃関数
	void	Attack(void);




};
