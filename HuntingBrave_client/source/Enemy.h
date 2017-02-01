
#pragma once

//***************************************************************
//
//	Enemy�N���X
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
	//	�p�����[�^
	Vector3		targetPos;
	float		interpolationParam;
	float		searchDist;
	float		attackDist;
	char		enemyType;
	int			cooltime;
	AttackInfo	attackInfo;

	int	count;		//�����i�q�b�g�p

	enum ENEMY_TYPE
	{
		WOLF,
		MOFFU,
		SHADOW,
		ENEMY_MAX
	};

public:

	enum MODE	//	��
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
	//	�������E���
	Enemy( void );
	~Enemy( void )override;
	virtual bool	Initialize( int life ) = 0;

	//	�e���[�h����֐�
	virtual void	EntryMode( void ) = 0;
	virtual void	MoveMode( void ) = 0;
	virtual void	AttackMode( void ) = 0;
	virtual	void	DeadMode( void ) = 0;

	void	WaitMode(void);
	void	DamageMode( void );
	

	//	����֐�
	virtual void Update( void );
	void	Move( float speed ) ;
	void	FacingPlayer( void );
	void	Advance( float speed );
	bool	DistCheck( float& length );
	void	LifeCheck( void );
	void	StageCheck( void );
	void	AngleAdjust( const Vector3& moveVec, float adjustSpeed )override;

	//	���M
	void	SendHuntInfo( void );

	//	�U���֐�
	virtual void	Attack( void )=0;

	//	���ݒ�
	void	SetTargetPos( const Vector3& pos );
	void	SetEnemyType( char enemyType );
	
	//	���擾
	char	GetEnemyType( void )const;
	int		GetMode( void )const;
	AttackInfo&	GetAttackInfo( void ){ return attackInfo; }
};
