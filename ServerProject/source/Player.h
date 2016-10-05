
#pragma once

//***************************************************************
//
//	PlayerManagerクラス
//
//***************************************************************

//	include
#include	"GameData.h"

//	class
class Player
{
private:
	//	パラメータ
	int		type;			//	タイプ
	Vector3	pos;		//	座標
	float		angle;	//	方向
	int			motion;	//	モーション

public:
	//	初期化・解放
	Player( void );
	~Player( void );

	//	更新・描画
	bool	Update( PlayerParam& param );

	//	動作関数

	//	情報設定

	//	情報取得
	Vector3	GetPos( void )const;


};