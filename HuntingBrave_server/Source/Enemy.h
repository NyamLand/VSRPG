
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
	Vector3	target;
	float		searchDist;
	float		deltaTime;
	float		effPercentage;
	bool		hitEff[PLAYER_MAX];
	bool		alive;
	bool		atkFlag;
	bool		allState;
	int		index;

	AttackInfo		attackInfo;
	EnemyParam	enemyParam;
	CollisionInfo		collisionInfo;
	LifeInfo				lifeInfo;
	Timer*				timer[PLAYER_MAX];

	bool	clientState[PLAYER_MAX];

	//	���[�h�ʊ֐��|�C���^
	void( Enemy::*ModeFunction[MODE_MAX] )( void );

public:
	//	�������E���
	Enemy( void );
	~Enemy( void )override;
	void	ClientStateInitialize( void );

	//	�X�V
	virtual void Update( int index, float deltaTime );

	//	�ʏ�ړ�
	void	Move( void ) ;
	void	Advance( void );
	bool	DistCheck( Vector3& target, bool& attackFlag );

	//	���[�h�ʓ���֐�
	void	EntryMode( void );
	void	MoveMode( void );
	void	AttackMode( void );
	void	DeadMode( void );

	//	����֐�
	void	AddMove( const Vector3& move );
	void	LifeCheck( void );
	void	AngleAdjust( const Vector3& moveVec, float adjustSpeed );
	void	AngleAdjustParent( const Vector3& direction, float adjustSpeed );
	void	CalcLife( int player );
	void	CalcLifeMagic( int player );

	//	�N���C�A���g���
	bool	CheckState( void );
	void	ReceiveClientState( int client );
	void	SendMode( char nextMode );
	void	SendMotion( int motion );
	void	SendHit( void );
	void	SendEnemyInfo( void );

	//	���ݒ�
	void	SetPos( const Vector3& pos );
	void	SetAngle( float angle );
	void	SetMotion( int motion );
	void	SetHit( int player );

	//	���擾
	Vector3	GetPos( void )const;
	float		GetAngle( void )const;
	int		GetMotion( void )const;
	int		GetMode( void )const;
	bool		GetAlive( void )const;
	bool		GetHitEff( int player )const{ return hitEff[player]; }
	AttackInfo&	GetAttackInfo( void ){ return attackInfo; }
	EnemyParam&	GetEnemyParam( void ){ return	enemyParam; }
	CollisionInfo&	GetCollisionInfo( void ){ return collisionInfo; }
	LifeInfo& GetLifeInfo( void ){ return lifeInfo; }
};
