
#pragma once

//***************************************************************
//
//	Enemy�N���X
//
//***************************************************************

//	include
#include	"BaseChara.h"

//	class
class Enemy : public BaseChara
{
protected:
	//	�p�����[�^
	Vector3	targetPos;
	float		interpolationParam;
	float		searchDist;
	float		attackDist;

	//float		elife;			//�G�̗̑�
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

	//	�e���[�h����֐�
	virtual void	EntryMode( void ) = 0;
	virtual void	MoveMode( void ) = 0;
	virtual void	AttackMode( void ) = 0;
	void	DamageMode( void );
	

	//	����֐�
	void	Move( float speed ) ;
	void	FacingPlayer( void );
	void	Advance( float speed );
	bool	DistCheck( float& length );
	void	LifeCheck( void );
	//virtual bool	DamageFlgCheck( void )=0;

	//���[�h�֐�

	//	�U���֐�
	virtual void	Attack( void )=0;

	//	���擾
	void	SetTargetPos( const Vector3& pos );	
};
