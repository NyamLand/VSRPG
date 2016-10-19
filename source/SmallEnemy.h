
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

	//	���[�h�ʊ֐��|�C���^
	void(SmallEnemy::*ModeFunction[MODE_MAX])(void);

public:
	//	�������E���
	SmallEnemy(void);
	~SmallEnemy(void)override;
	bool	Initialize(void)override;

	//	�X�V�E�`��
	void	Update(void)override;
	void	Render(iexShader* shader = nullptr, LPSTR technique = nullptr)override;
	//	�e���[�h����֐�
	void	MoveMode(void);
	//void	PostureMode( void );

	//	����֐�
	void	Move(void)override;

	//	�U���֐�
	void	Attack(void)override;


};