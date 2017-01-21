
#pragma once

//***************************************************************
//
//	Enemyクラス
//
//***************************************************************

//	include
#include	"BaseChara.h"
#include	"CharaInfo.h"

//	敵情報構造体
struct EnemyParam
{
	Vector3	pos;
	float			angle;
	int			motion;
};

//	class
class Enemy : public BaseChara
{
protected:
	//	パラメータ
	LifeInfo	lifeInfo;
	Vector3		targetPos;
	float		interpolationParam;
	float		searchDist;
	float		attackDist;
	char		enemyType;
	float		angle;
	bool		alive;
	AttackInfo	attackInfo;
	EnemyParam	enemyParam;
	Vector3	move;
	Timer*	timer;

	int	count;		//仮多段ヒット用

public:

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

	//	更新
	virtual void Update( void );

	//	通常移動
	void	Move( void ) ;
	void	Advance( void );
	bool	DistCheck( Vector3& target );

	//	動作関数
	void	AddMove( void );
	void	LifeCheck( void );
	void	AngleAdjust( const Vector3& moveVec, float adjustSpeed );
	void	AngleAdjustParent( const Vector3& direction, float adjustSpeed );

	//	座標設定
	void	SetPos( const Vector3& pos );
	void	SetAngle( float angle );
	
	//	情報取得
	int		GetMode( void )const;
	bool		GetAlive( void )const;
	AttackInfo&	GetAttackInfo( void ){ return attackInfo; }
	EnemyParam&	GetEnemyParam( void ){ return	enemyParam; }
};
