
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

	enum MODE
	{
		ENTRY,
		MOVE,
		ATTACK,
		DEAD,
		MODE_MAX
	};

	//	パラメータ
	Vector3	target;
	float		searchDist;
	float		deltaTime;
	bool		alive;
	bool		atkFlag;
	bool		allState;
	char		index;

	AttackInfo		attackInfo;
	EnemyParam	enemyParam;
	CollisionInfo		collisionInfo;
	LifeInfo				lifeInfo;
	Timer*	timer;

	bool	clientState[PLAYER_MAX];

	//	モード別関数ポインタ
	void( Enemy::*ModeFunction[MODE_MAX] )( void );

public:
	//	初期化・解放
	Enemy( void );
	~Enemy( void )override;
	void	ClientStateInitialize( void );

	//	更新
	virtual void Update( char index, float deltaTime );

	//	通常移動
	void	Move( void ) ;
	void	Advance( void );
	bool	DistCheck( Vector3& target, bool& attackFlag );

	//	モード別動作関数
	void	EntryMode( void );
	void	MoveMode( void );
	void	AttackMode( void );

	//	動作関数
	void	AddMove( const Vector3& move );
	void	LifeCheck( void );
	void	AngleAdjust( const Vector3& moveVec, float adjustSpeed );
	void	AngleAdjustParent( const Vector3& direction, float adjustSpeed );

	//	クライアント情報
	bool	CheckState( void );
	void	ReceiveClientState( int client );
	void	SendMode( char nextMode );
	void	SendMotion( int motion );

	//	情報設定
	void	SetPos( const Vector3& pos );
	void	SetAngle( float angle );
	void	SetMotion( int motion );
	void	SendEnemyInfo( void );

	//	情報取得
	Vector3	GetPos( void )const;
	float		GetAngle( void )const;
	int		GetMotion( void )const;
	int		GetMode( void )const;
	bool		GetAlive( void )const;
	AttackInfo&	GetAttackInfo( void ){ return attackInfo; }
	EnemyParam&	GetEnemyParam( void ){ return	enemyParam; }
	CollisionInfo&	GetCollisionInfo( void ){ return collisionInfo; }
};
