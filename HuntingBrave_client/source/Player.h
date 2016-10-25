
#pragma once
#include	"BaseEquipment.h"
//***************************************************************
//
//	Player�N���X
//
//***************************************************************

struct Status
{
	float	hp;
	float	atk;
	float	dif;
	float	mat;
	float	mdf;
	float	speed;
};

//struct Equipments
//{
//	BaseEquipment*	atk;
//	BaseEquipment*	mat;
//	BaseEquipment*
//
//};


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
		AVOID,
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
		AVOID,
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
	void	ModeAvoid( void );			//���


	//	����֐�
	bool		Move( void );
	bool		SwordAttack(void);		//�s�����I�������1��Ԃ��A���f������2��Ԃ�
	bool		MagicAttack( void );
	bool		Avoid( void );



	//���ݒ�
	void	SetMode(int mode);
};
