
#pragma once

//***************************************************************
//
//	Enemyクラス
//
//***************************************************************

//	include
#include	"BaseChara.h"
#include	"EnemyHp.h"
#include	"CharaInfo.h"

//	class
class Enemy : public BaseChara
{
protected:
	//	パラメータ
	Vector3		targetPos;
	float		interpolationParam;
	float		searchDist;
	float		attackDist;
	char		enemyType;
	int			cooltime;
	AttackInfo	attackInfo;

	int	count;		//仮多段ヒット用

	enum ENEMY_TYPE
	{
		WOLF,
		MOFFU,
		SHADOW,
		ENEMY_MAX
	};

public:

	enum MODE	//	仮
	{
		ENTRY,
		WAIT,
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
	virtual bool	Initialize( int life ) = 0;

	//	各モード動作関数
	virtual void	EntryMode( void ) = 0;
	virtual void	MoveMode( void ) = 0;
	virtual void	AttackMode( void ) = 0;
	virtual	void	DeadMode( void ) = 0;

	void	WaitMode(void);
	void	DamageMode( void );
	

	//	動作関数
	virtual void Update( void );
	void	Move( float speed ) ;
	void	FacingPlayer( void );
	void	Advance( float speed );
	bool	DistCheck( float& length );
	void	LifeCheck( void );
	void	StageCheck( void );
	void	AngleAdjust( const Vector3& moveVec, float adjustSpeed )override;

	//	送信
	void	SendHuntInfo( void );

	//	攻撃関数
	virtual void	Attack( void )=0;

	//	情報設定
	void	SetTargetPos( const Vector3& pos );
	void	SetEnemyType( char enemyType );
	
	//	情報取得
	char	GetEnemyType( void )const;
	int		GetMode( void )const;
	AttackInfo&	GetAttackInfo( void ){ return attackInfo; }
};
