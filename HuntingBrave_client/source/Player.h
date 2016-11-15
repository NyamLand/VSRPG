
#pragma once

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
#include	"BaseEquipment.h"
#include	"GameData.h"

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


//	class
class Player : public BaseChara
{
private:
	//	���[�h�ʊ֐��|�C���^
	void( Player::*ModeFunction[MODE::MODE_MAX] )( void );
	PlayerParam	playerParam;

public:
	//	�������E���
	Player( void );
	~Player( void )override;
	bool	Initialize( int id );
	
	//	�X�V�E�`��
	void	Update( PlayerParam& playerParam );
	void	Render( iexShader* shader = nullptr, LPSTR technique = nullptr )override;

	//	�e���[�h����֐�
	void	MoveMode( void );
	//void	PostureMode( void );
	void	ModeSwordAttack( void );
	void	ModeMagicAttack( void );
	void	ModeAvoid( void );			//���

	//	����֐�
	bool		Move( void );
	bool		SwordAttack( void );		//�s�����I�������1��Ԃ��A���f������2��Ԃ�
	bool		MagicAttack( void );
	bool		Avoid( void );

	//	���ݒ�
	void	SetPlayerParam( const PlayerParam& playerParam );
};
