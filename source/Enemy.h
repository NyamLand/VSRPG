
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
		//POSTURE,
		MODE_MAX
	};

	//	���[�h�ʊ֐��|�C���^
	void(Enemy::*ModeFunction[MODE_MAX])(void);

public:
	//	�������E���
	Enemy(void);
	~Enemy(void)override;
	bool	Initialize(void)override;

	//	�X�V�E�`��
	void	Update(void)override;

	//	�e���[�h����֐�
	void	MoveMode(void);
	//void	PostureMode( void );

	//	����֐�
	void	Move(void);

	//	�U���֐�
	void	Attack(void);




};
