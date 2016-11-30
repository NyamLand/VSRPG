
#pragma once

//*****************************************************************************************************************************
//
//	GameManager�N���X
//
//*****************************************************************************************************************************

//	include
#include	"GameData.h"
#include	"Timer.h"

//	define
namespace
{
	namespace SCENE
	{
		enum
		{
			MATCHING,
			MAIN,
			RESULT
		};
	}
}

//	class
class GameManager
{
private:
	PlayerParam	initPlayerParam[PLAYER_MAX];
	Timer*	timer;
	char	scene;

public:
	//	�������E���
	GameManager( void );
	~GameManager( void );

	//	�X�V
	void	Update( void );

	//	����֐�
	void	TimerUpdate( void );

	//	���擾
	Timer*	GetTimer( void )const;
	PlayerParam	GetInitInfo( int id )const;
};

extern	GameManager*	gameManager;