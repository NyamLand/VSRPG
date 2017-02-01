
#pragma once

//***************************************************************
//
//	sceneResultクラス
//
//***************************************************************

//	include
#include	<vector>
#include	"NameUI.h"
#include	"GameData.h"
#include	"TestResult.h"
#include	"NumberUI.h"
#include	"ScoreUI.h"
#include	"RankUI.h"
#include	"Result.h"


//	class
class sceneResult : public Scene
{
private:
	iex2DObj*	back;
	TestResult*	testResult;
	Vector3	viewPos;
	Vector3	playerPos[PLAYER_MAX];
	int	index;
	iex3DObj*	obj[PLAYER_MAX];
	ScoreUI*	scoreUI[PLAYER_MAX];
	RankUI*	rankUI[PLAYER_MAX];

public:
	//	初期化・開放
	bool	Initialize( void );
	~sceneResult( void );

	//	更新・描画
	void	Update( void );
	void	Render( void );
};
