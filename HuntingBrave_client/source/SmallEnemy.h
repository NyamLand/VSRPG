
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
		ENTRY,
		MOVE,
		ATTACK,
		DEAD,
		MODE_MAX
	};

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
	void	EntryMode( void );
	void	MoveMode( void );
	void	AttackMode( void );

	//	����֐�

	//	�U���֐�
	void	Attack( void )override;


};