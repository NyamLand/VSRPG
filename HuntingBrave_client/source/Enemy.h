
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
private:
	enum MODE	//	��
	{
		MOVE,
		MODE_MAX
	};

	//	�p�����[�^
	Vector3	targetPos;
	float		interpolationParam;
	bool		active;
	bool		eraseOK;

	//	���[�h�ʊ֐��|�C���^
	void( Enemy::*ModeFunction[MODE_MAX] )( void );

public:
	//	�������E���
	Enemy( void );
	~Enemy( void )override;

	//	�X�V�E�`��
	virtual void	Update( void ) = 0;

	//	�e���[�h����֐�
	void	MoveMode( void );

	//	����֐�
	void	Move( float speed, float length ) ;
	void	FacingPlayer( void );
	void	Advance( float speed );
	bool	DistCheck( float length );

	//	�U���֐�
	virtual void	Attack( void )=0;

	//	���擾
	void	SetTargetPos( const Vector3& pos );
	bool	GetActive( void )const;
	bool	GetEraseOK( void )const;
};
