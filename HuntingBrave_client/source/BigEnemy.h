#pragma once

//***************************************************************
//
//	Enemy�N���X
//
//***************************************************************

//	include
#include	"Enemy.h"

//	class
class BigEnemy : public Enemy
{
private:
	enum MODE	//	��
	{
		ENTRY,
		MOVE,
		ATTACK,
		DAMAGE,
		DEAD,
		MODE_MAX
	};

	//	���[�h�ʊ֐��|�C���^
	void( BigEnemy::*ModeFunction[MODE_MAX] )( void );

public:
	//	�������E���
	BigEnemy( void );
	~BigEnemy( void )override;
	bool	Initialize( void )override;

	//	�X�V
	void	Update( void );

	//	�e���[�h����֐�
	void	EntryMode( void );
	void	MoveMode( void );
	void	AttackMode( void );
	void	DamageMode( void );
	//bool	DamageFlgCheck( void )override;
	//	����֐�

	//	�U���֐�
	void	Attack( void )override;


};