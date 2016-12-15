
#pragma once

//***************************************************************
//
//	sceneResult�N���X
//
//***************************************************************

//	include
#include	"NameUI.h"
#include	"GameData.h"
//	class
class sceneResult : public Scene
{
private:
	iex2DObj*	back;
	iex2DObj*	lovelive;

	float	percentage;
	float	alpha;
	bool	pushState;

public:
	//	�������E�J��
	bool	Initialize( void );
	~sceneResult( void );

	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );


};
