
#pragma once

//***************************************************************
//
//	sceneResult�N���X
//
//***************************************************************

//	include
#include	"NameUI.h"
#include	"GameData.h"
#include	"TestResult.h"
#include	"Result.h"


//	class
class sceneResult : public Scene
{
private:
	iex2DObj*	back;
	TestResult*	testResult;
	Vector3	viewPos;
	Vector3	playerPos[PLAYER_MAX];
	int	index;
	iex3DObj*	obj[PLAYER_MAX];

public:
	//	�������E�J��
	bool	Initialize( void );
	~sceneResult( void );

	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );
};
