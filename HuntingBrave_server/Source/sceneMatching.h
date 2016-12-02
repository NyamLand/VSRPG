
#pragma once

//************************************************************************
//
//	sceneMatchingクラス
//
//************************************************************************

//	include
#include	"Scene.h"

//	class
class sceneMatching : public Scene
{
private:
public:
	//	初期化・解放
	bool	Initialize( void );
	~sceneMatching( void );

	//	更新
	void	Update( void );
};
