
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
	virtual void	Move( void ) = 0;

	//	�U���֐�
	virtual void	Attack( void ) = 0;
};
