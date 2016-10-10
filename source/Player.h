
#pragma once

//***************************************************************
//
//	Player�N���X
//
//***************************************************************

//	include
#include	"BaseChara.h"

namespace MODE
{
	enum	//	��
	{
		MOVE,
		//POSTURE,
		SWOADATTACK,
		MAGICATTACK,
		MODE_MAX
	};
}

//*�����f���ɑ΂���
namespace MOTION
{
	enum
	{
		HOPPING,
		RIGOR,
		WAIT,
		HOPPING2,
		MOVE,
		ATTACK,
		ATTACK2 = 7,
	};
}
//	class
class Player : public BaseChara
{
private:

	//	���[�h�ʊ֐��|�C���^
	void( Player::*ModeFunction[MODE::MODE_MAX] )( void );

	iex2DObj*	texture;


public:
	//	�������E���
	Player( void );
	~Player( void )override;
	bool	Initialize( void )override;
	
	//	�X�V�E�`��
	void	Update( void )override;
	void	Render( iexShader* shader = nullptr, LPSTR technique = nullptr )override;

	//	�e���[�h����֐�
	void	MoveMode( void );
	//void	PostureMode( void );
	void	ModeSwordAttack(void);
	void	ModeMagicAttack( void );


	//	����֐�
	int		Move( void );
	int		SwordAttack(void);		//�s�����I�������1��Ԃ��A���f������2��Ԃ�
	int		MagicAttack( void );


	//���ݒ�
	void	SetMode(int mode);
};
