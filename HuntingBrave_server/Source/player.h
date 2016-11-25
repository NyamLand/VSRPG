
#pragma once

//*****************************************************************************************************************************
//
//	Player�N���X
//
//*****************************************************************************************************************************

//	include
#include	"GameData.h"
#include	"BaseChara.h"
#include	"CharaInfo.h"

//	class
class Player : public BaseChara
{
private:
	PlayerParam		pParam;
	Timer*				timer;
	int		index;

	//	���[�h�ʊ֐��|�C���^
	void( Player::*ModeFunction[MODE::MODE_MAX] )( void );

public:
	//	�������E���
	Player( int id );
	~Player( void )override;
	bool	Initialize( void );

	//	�X�V
	bool Update( PlayerParam& param );

	//	���[�h�ʓ���֐�
	void	ModeMove( void );
	void	ModeSwordAttack( void );
	void	ModeMagicAttack( void );
	void	ModeDamage( void );
	void	ModeDeath( void );

	//	����֐�
	void	Move( void );
	void	SwordAttack( void );
	void	MagicAttack( void );
	void	MagicChant( void );
	void	MagicChantStart( void );
	void	Damage( void );
	void	CheckInput( void );

	//	��������
	void	AngleAdjust( const Vector3& moveVec, float adjustSpeed );
	void	AngleAdjustParent( const Vector3& direction, float adjustSpeed );

	//	���ݒ�
	void	SetMotion( int motion );
	void	SetPos( const Vector3& pos );
	void	SetDeath( void );
};


