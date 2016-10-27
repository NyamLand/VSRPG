
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
		MODE_MAX
	};

	//	パラメータ
	Vector3	targetPos;
	float		interpolationParam;
	bool		active;
	bool		eraseOK;

	//	モード別関数ポインタ
	void( Enemy::*ModeFunction[MODE_MAX] )( void );

public:
	//	初期化・解放
	Enemy( void );
	~Enemy( void )override;

	//	更新・描画
	virtual void	Update( void ) = 0;

	//	各モード動作関数
	void	MoveMode( void );

	//	動作関数
	void	Move( float speed, float length ) ;
	void	FacingPlayer( void );
	void	Advance( float speed );
	bool	DistCheck( float length );

	//	攻撃関数
	virtual void	Attack( void )=0;

	//	情報取得
	void	SetTargetPos( const Vector3& pos );
	bool	GetActive( void )const;
	bool	GetEraseOK( void )const;
};
