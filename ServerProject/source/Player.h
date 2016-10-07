
#pragma once

//***************************************************************
//
//	PlayerManager�N���X
//
//***************************************************************

//	include
#include	"GameData.h"

//	class
class Player
{
private:
	//	�p�����[�^
	int		type;			//	�^�C�v
	Vector3	pos;		//	���W
	float		angle;	//	����
	int			motion;	//	���[�V����

public:
	//	�������E���
	Player( void );
	~Player( void );

	//	�X�V�E�`��
	bool	Update( PlayerParam& param );

	//	����֐�

	//	���ݒ�

	//	���擾
	Vector3	GetPos( void )const;


};