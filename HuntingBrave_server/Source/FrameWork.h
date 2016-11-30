
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

public:
	//	�������E���
	FrameWork( void );
	~FrameWork( void );

	//	�X�V
	void	Update( void );

	//	����֐�
	void	ChangeScene( Scene* newScene );
};
