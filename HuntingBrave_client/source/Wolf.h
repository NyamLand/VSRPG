#pragma once

//***************************************************************
//
//	Enemy�N���X
//
//***************************************************************

//	include
#include	"Enemy.h"

//	class
class Wolf : public Enemy
{

	

	//	���[�h�ʊ֐��|�C���^
	void(Wolf::*ModeFunction[MODE_MAX])(void);

public:
	//	�������E���
	Wolf(void);
	~Wolf(void)override;
	bool	Initialize( void )override;

	//	�X�V
	void	Update( void );

	//	�e���[�h����֐�
	void	EntryMode( void )override;
	void	MoveMode( void )override;
	void	AttackMode( void )override;
	void	DeadMode(void)override;
	//void	DamageMode( void );
	//bool	DamageFlgCheck( void )override;
	//	����֐�

	//	�U���֐�
	void	Attack( void )override;


};