
#pragma once

//*****************************************************************************************************************************
//
//	PlayerManagerクラス
//
//*****************************************************************************************************************************

//	include
#include	"GameParam.h"
#include	"Player.h"

//	class
class PlayerManager
{
private:
	Player*	player[PLAYER_MAX];
	GameParam*	gameParam;

public:
	//	初期化・解放
	PlayerManager( GameParam* gameParam );
	~PlayerManager( void );

	//	更新・描画
	void	Update( int id );

	//	情報設定
	void	SetPlayer( int id );

	//	座標取得
	Vector3	GetPos( int id );
};
