
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

	//	���[�h�ʊ֐��|�C���^
	void( SmallEnemy::*ModeFunction[MODE_MAX] )( void );

public:
	//	�������E���
	SmallEnemy( void );
	~SmallEnemy( void )override;
	bool	Initialize( void )override;

	//	�X�V
	void	Update( void )override;

	//	�e���[�h����֐�
	void	EntryMode( void )override;
	void	MoveMode( void )override;
	void	AttackMode( void )override;
	void	DeadMode( void )override;
	
	//	����֐�

	//	�U���֐�
	void	Attack( void )override;


};