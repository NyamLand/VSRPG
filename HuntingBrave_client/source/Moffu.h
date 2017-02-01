
#pragma once

//***************************************************************
//
//	Enemy�N���X
//
//***************************************************************

//	include
#include	"Enemy.h"

//	class
class Moffu : public Enemy
{
private:
	int texType;

	//	���[�h�ʊ֐��|�C���^
	void(Moffu::*ModeFunction[MODE_MAX])(void);

public:
	//	�������E���
	Moffu(void);
	~Moffu(void)override;
	bool	Initialize( int life );

	//	�X�V
	void	Update( void )override;
	void	Render( iexShader* shader = nullptr, LPSTR technique = nullptr )override;

	//	�e���[�h����֐�
	void	EntryMode( void )override;
	void	MoveMode( void )override;
	void	AttackMode( void )override;
	void	DeadMode( void )override;
	
	//	����֐�

	//	�U���֐�
	void	Attack( void )override;


};