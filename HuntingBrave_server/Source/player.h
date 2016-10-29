
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

public:
	//	�������E���
	Player( void );
	~Player( void )override;

	//	�X�V
	bool Update( PlayerParam& param );

	//	����֐�
	void	Move( void );
	void	AngleAdjust( const Vector3& moveVec, float adjustSpeed );
	void	AngleAdjustParent( const Vector3& direction, float adjustSpeed );

	//	���ݒ�
	void	SetMotion( int motion );
};


