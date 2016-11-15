
#pragma once

//*****************************************************************************************************************************
//
//	Player�N���X
//
//*****************************************************************************************************************************

//	include
#include	"GameData.h"
#include	"BaseChara.h"

//	class
class Player : public BaseChara
{
private:
	PlayerParam	pParam;
	int		index;

	//	���[�h�ʊ֐��|�C���^
	void( Player::*ModeFunction[MODE::MODE_MAX] )( void );

public:
	//	�������E���
	Player( int id );
	~Player( void )override;

	//	�X�V
	bool Update( PlayerParam& param );

	//	���[�h�ʓ���֐�
	void	ModeMove( void );
	void	ModeSwordAttack( void );

	//	����֐�
	void	Move( void );
	void	SwordAttack( void );
	void	Damage( void );
	void	AngleAdjust( const Vector3& moveVec, float adjustSpeed );
	void	AngleAdjustParent( const Vector3& direction, float adjustSpeed );

	//	���ݒ�
	void	SetMotion( int motion );
};


