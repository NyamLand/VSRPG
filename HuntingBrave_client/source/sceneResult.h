
#pragma once

//***************************************************************
//
//	sceneResultクラス
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
	//	初期化・開放
	bool	Initialize( void );
	~sceneResult( void );

	//	更新・描画
	void	Update( void );
	void	Render( void );


};
