
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

	enum MODE	//	��
	{
		ENTRY,
		MOVE,
		ATTACK,
		DEAD,
		MODE_MAX
	};

public:
	//	�������E���
	Enemy( void );
	~Enemy( void )override;

	//	�e���[�h����֐�
	void	MoveMode( void );

	//	����֐�
	void	Move( float speed ) ;
	void	FacingPlayer( void );
	void	Advance( float speed );
	bool	DistCheck( float& length );
	void	LifeCheck( void );

	//	�U���֐�
	virtual void	Attack( void )=0;

	//	���擾
	void	SetTargetPos( const Vector3& pos );
	bool	GetActive( void )const;
	bool	GetIsAlive( void )const;
};
