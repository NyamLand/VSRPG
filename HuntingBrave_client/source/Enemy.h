
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
	virtual bool	Initialize(void)=0;

	//	更新・描画
	virtual void	Update(void) = 0;
	virtual void	Render(iexShader* shader = nullptr, LPSTR technique = nullptr)=0;
	//	各モード動作関数
	void	MoveMode(void);
	//void	PostureMode( void );

	//	動作関数
	virtual void	Move(void)=0;

	//	攻撃関数
	virtual void	Attack(void)=0;




};
