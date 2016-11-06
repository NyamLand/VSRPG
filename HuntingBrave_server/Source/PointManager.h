
#pragma once

//****************************************************************
//
//	PointManagerクラス
//
//****************************************************************

//	include
#include	"GameParam.h"

//	class
class PointManager
{
private:
	GameParam*	gameParam;
	int		point[PLAYER_MAX];

public:
	//	初期化・解放
	PointManager( GameParam* gameParam );
	~PointManager( void );

	//	更新
	void	Update( int client );
};

extern	PointManager*	pointManager;