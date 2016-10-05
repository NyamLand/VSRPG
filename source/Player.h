
#pragma once

//***************************************************************
//
//	Player�N���X
//
//***************************************************************

//	include
#include	"BaseChara.h"

//	class
class Player : public BaseChara
{
private:
	enum MODE	//	��
	{
		MOVE,
		//POSTURE,
		MODE_MAX
	};

	//	���[�h�ʊ֐��|�C���^
	void( Player::*ModeFunction[MODE_MAX] )( void );

public:
	//	�������E���
	Player( void );
	~Player( void )override;
	bool	Initialize( void )override;
	
	//	�X�V�E�`��
	void	Update( void )override;

	//	�e���[�h����֐�
	void	MoveMode( void );
	//void	PostureMode( void );

	//	����֐�
	void	Move( void );

};
