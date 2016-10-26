
#pragma once

//*****************************************************************************************************************************
//
//	GameManagerクラス
//
//*****************************************************************************************************************************

//	include
#include	"GameData.h"

//	class
class GameManager
{
private:
	Vector3	initPos[PLAYER_MAX];

public:
	//	初期化・解放
	GameManager( void );
	~GameManager( void );

	//	更新
	void	Update( void );

	//	動作関数

	//	情報設定

	//	情報取得
	Vector3	GetInitPos( int id )const;
};

extern	GameManager*	gameManager;