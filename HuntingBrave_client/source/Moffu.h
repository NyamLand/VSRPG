
#pragma once

//***************************************************************
//
//	Enemyクラス
//
//***************************************************************

//	include
#include	"Enemy.h"

//	class
class Moffu : public Enemy
{
private:
	int texType;

	//	モード別関数ポインタ
	void(Moffu::*ModeFunction[MODE_MAX])(void);

public:
	//	初期化・解放
	Moffu(void);
	~Moffu(void)override;
	bool	Initialize( int life );

	//	更新
	void	Update( void )override;
	void	Render( iexShader* shader = nullptr, LPSTR technique = nullptr )override;

	//	各モード動作関数
	void	EntryMode( void )override;
	void	MoveMode( void )override;
	void	AttackMode( void )override;
	void	DeadMode( void )override;
	
	//	動作関数

	//	攻撃関数
	void	Attack( void )override;


};