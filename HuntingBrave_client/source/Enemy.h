
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
protected:
	//	パラメータ
	Vector3	targetPos;
	float		interpolationParam;
	float		searchDist;
	float		attackDist;

	float		elife;			//敵の体力

	enum MODE	//	仮
	{
		ENTRY,
		MOVE,
		ATTACK,
		DAMAGE,
		DEAD,
		MODE_MAX
	};

public:
	//	初期化・解放
	Enemy( void );
	~Enemy( void )override;

	//	各モード動作関数
	void	MoveMode( void );

	//	動作関数
	void	Move( float speed ) ;
	void	FacingPlayer( void );
	void	Advance( float speed );
	bool	DistCheck( float& length );
	void	LifeCheck( void );

	//	攻撃関数
	virtual void	Attack( void )=0;

	//	情報取得
	void	SetTargetPos( const Vector3& pos );	
};
