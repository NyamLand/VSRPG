
#pragma once

//*****************************************************************************************************************************
//
//	Playerクラス
//
//*****************************************************************************************************************************

//	include
#include	"GameData.h"

//	class
class Player
{
private:
	//	パラメータ
	Vector3		pos;		//	座標
	float			angle;	//	方向

public:
	//	初期化・解放
	Player( void );
	~Player( void );

	//	更新
	bool Update( PlayerParam& param );

	//	情報取得
	Vector3 GetPos( void );
};


