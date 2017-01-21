
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
	//	�p�����[�^
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

	int	count;		//�����i�q�b�g�p

public:

	enum MODE	//	��
	{
		ENTRY,
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

	//	�X�V
	virtual void Update( void );

	//	�ʏ�ړ�
	void	Move( void ) ;
	void	Advance( void );
	bool	DistCheck( Vector3& target );

	//	����֐�
	void	AddMove( void );
	void	LifeCheck( void );
	void	AngleAdjust( const Vector3& moveVec, float adjustSpeed );
	void	AngleAdjustParent( const Vector3& direction, float adjustSpeed );

	//	���W�ݒ�
	void	SetPos( const Vector3& pos );
	void	SetAngle( float angle );
	
	//	���擾
	int		GetMode( void )const;
	bool		GetAlive( void )const;
	AttackInfo&	GetAttackInfo( void ){ return attackInfo; }
	EnemyParam&	GetEnemyParam( void ){ return	enemyParam; }
};
