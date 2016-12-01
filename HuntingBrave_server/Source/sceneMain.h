
#pragma once


#pragma once

//************************************************************************
//
//	sceneMainクラス
//
//************************************************************************

//	include
#include	"Scene.h"

//	class
class sceneMain : public Scene
{
private:
public:
	//	初期化・解放
	bool	Initialize( void )override;
	~sceneMain( void )override;

	//	更新
	void	Update( void )override;
};
