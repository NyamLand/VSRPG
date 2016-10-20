
#pragma once

//*****************************************************************************************************************************
//
//	Player�N���X
//
//*****************************************************************************************************************************

//	include
#include	"GameData.h"

//	class
class Player
{
private:
	//	�p�����[�^
	Vector3		pos;		//	���W
	float			angle;	//	����

public:
	//	�������E���
	Player( void );
	~Player( void );

	//	�X�V
	bool Update( PlayerParam& param );

	//	���擾
	Vector3 GetPos( void );
};


