
#pragma once

//***************************************************************
//
//	sceneResultクラス
//
//***************************************************************

//	include
<<<<<<< HEAD
#include	"NameUI.h"
#include	"GameData.h"
=======
#include	"Result.h"

>>>>>>> c9bb391924d0e6fa19f2a0c2580d1846db27fbd8
//	class
class sceneResult : public Scene
{
private:
	iex2DObj*	back;
	iex2DObj*	lovelive;
	Result*		result;

	float	percentage;
	float	alpha;
	bool	pushState;

public:
	//	初期化・開放
	bool	Initialize( void );
	~sceneResult( void );

	//	更新・描画
	void	Update( void );
	void	Render( void );


};
