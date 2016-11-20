
#pragma once

//**************************************************************************
//
//	Magicクラス
//
//**************************************************************************

//	include
#include	"Timer.h"

//	class
class Magic
{
private:
	Vector3	pos;
	Vector3	vec;
	Timer*		timer;
	float			speed;
	int			mode;
	int			id;
	bool			isHit;

public:
	//	初期化・解放
	Magic( void );
	~Magic( void );
	bool	Initialize( int id, const Vector3& pos, const Vector3& vec );

	//	更新
	bool	Update( void );

	//	動作関数
	void	Move( void );
	void	Scaling( void );

	//	情報設定
	Vector3	GetPos( void )const;

	//	情報取得
};
