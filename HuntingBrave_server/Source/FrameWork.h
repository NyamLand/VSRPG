
#pragma once

//*****************************************************************************************************************************
//
//	FrameWork�N���X
//
//*****************************************************************************************************************************

//	include
#include	"Scene.h"

//	class
class FrameWork
{
private:
	Scene*	scene;
	char		curScene;

public:
	//	�������E���
	FrameWork( void );
	~FrameWork( void );

	//	�X�V
	void	Update( int client );

	//	����֐�
	void	ChangeScene( Scene* newScene );
	void	SendChangeScene( char nextScene );

	//	���擾
	char	GetScene( void )const;
};

extern	FrameWork*	mainFrame;
