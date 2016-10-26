
#pragma once

//*****************************************************************************************************************************
//
//	GameManager�N���X
//
//*****************************************************************************************************************************

//	include
#include	"GameData.h"

//	class
class GameManager
{
private:
	Vector3	initPos[PLAYER_MAX];

public:
	//	�������E���
	GameManager( void );
	~GameManager( void );

	//	�X�V
	void	Update( void );

	//	����֐�

	//	���ݒ�

	//	���擾
	Vector3	GetInitPos( int id )const;
};

extern	GameManager*	gameManager;