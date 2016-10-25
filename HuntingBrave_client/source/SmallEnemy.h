
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

	//	モード別関数ポインタ
	void(SmallEnemy::*ModeFunction[MODE_MAX])(void);

public:
	//	初期化・解放
	SmallEnemy(void);
	~SmallEnemy(void)override;
	bool	Initialize(void)override;

	//	更新・描画
	void	Update(void)override;
	//void	Render(iexShader* shader = nullptr, LPSTR technique = nullptr)override;
	//	各モード動作関数
	void	MoveMode(void);
	//void	PostureMode( void );

	//	動作関数
	void	Move(void)override;

	//	攻撃関数
	void	Attack(void)override;


};