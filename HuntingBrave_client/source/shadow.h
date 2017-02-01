
#pragma once

//***************************************************************
//
//	Enemy�N���X
//
//***************************************************************

//	include
#include	"Enemy.h"

//	class
class Shadow : public Enemy
{
private:
	int texType;

	//	���[�h�ʊ֐��|�C���^
	void(Shadow::*ModeFunction[MODE_MAX])(void);

public:
	//	�������E���
	Shadow(void);
	~Shadow(void)override;
	bool	Initialize(int life);

	//	�X�V
	void	Update(void)override;

	//	�e���[�h����֐�
	void	EntryMode(void)override;
	void	MoveMode(void)override;
	void	AttackMode(void)override;
	void	DeadMode(void)override;

	//	����֐�

	//	�U���֐�
	void	Attack(void)override;


};