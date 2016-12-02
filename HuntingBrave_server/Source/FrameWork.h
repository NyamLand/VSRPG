
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
	char		curScene;

public:
	//	初期化・解放
	FrameWork( void );
	~FrameWork( void );

	//	更新
	void	Update( int client );

	//	動作関数
	void	ChangeScene( Scene* newScene );
	void	SendChangeScene( char nextScene );

	//	情報取得
	char	GetScene( void )const;
};

extern	FrameWork*	mainFrame;
