
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
	virtual bool	Initialize(void)=0;

	//	�X�V�E�`��
	virtual void	Update(void) = 0;
	virtual void	Render(iexShader* shader = nullptr, LPSTR technique = nullptr)=0;
	//	�e���[�h����֐�
	void	MoveMode(void);
	//void	PostureMode( void );

	//	����֐�
	virtual void	Move(void)=0;

	//	�U���֐�
	virtual void	Attack(void)=0;




};
