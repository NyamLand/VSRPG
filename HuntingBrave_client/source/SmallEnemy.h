
#pragma once

//***************************************************************
//
//	Enemy�N���X
//
//***************************************************************

//	include
#include	"Enemy.h"

//	class
class SmallEnemy : public Enemy
{
private:
	enum MODE	//	��
	{
		MOVE,
		//POSTURE,
		MODE_MAX
	};


public:
	//	�������E���
	SmallEnemy( void );
	~SmallEnemy( void )override;
	bool	Initialize( void )override;

	//	�X�V�E�`��

	//	�e���[�h����֐�
	void	MoveMode( void );
	//void	PostureMode( void );

	//	����֐�

	//	�U���֐�
	void	Attack( void )override;


};