
#pragma once

//*****************************************************************************************************************************
//
//	FrameWorkクラス
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
	//	初期化・解放
	FrameWork( void );
	~FrameWork( void );

	//	更新
	void	Update( void );

	//	動作関数
	void	ChangeScene( Scene* newScene );
};
