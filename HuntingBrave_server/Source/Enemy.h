
#pragma once

//***************************************************************
//
//	Enemy�N���X
//
//***************************************************************

//	include
#include	"BaseChara.h"
#include	"CharaInfo.h"

//	�G���\����
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

	//	�p�����[�^
	float		searchDist;
	float		deltaTime;
	bool		alive;
	AttackInfo		attackInfo;
	EnemyParam	enemyParam;
	CollisionInfo		collisionInfo;
	LifeInfo				lifeInfo;
	Timer*	timer;

	//	���[�h�ʊ֐��|�C���^
	void( Enemy::*ModeFunction[MODE_MAX] )( void );

public:
	//	�������E���
	Enemy( void );
	~Enemy( void )override;

	//	�X�V
	virtual void Update( float deltaTime );

	//	�ʏ�ړ�
	void	Move( void ) ;
	void	Advance( void );
	bool	DistCheck( Vector3& target, bool& attackFlag );

	//	����֐�
	void	AddMove( const Vector3& move );
	void	LifeCheck( void );
	void	AngleAdjust( const Vector3& moveVec, float adjustSpeed );
	void	AngleAdjustParent( const Vector3& direction, float adjustSpeed );

	//	���ݒ�
	void	SetPos( const Vector3& pos );
	void	SetAngle( float angle );
	void	SetMotion( int motion );

	//	���擾
	Vector3	GetPos( void )const;
	float		GetAngle( void )const;
	int		GetMotion( void )const;
	int		GetMode( void )const;
	bool		GetAlive( void )const;
	AttackInfo&	GetAttackInfo( void ){ return attackInfo; }
	EnemyParam&	GetEnemyParam( void ){ return	enemyParam; }
	CollisionInfo&	GetCollisionInfo( void ){ return collisionInfo; }
};
