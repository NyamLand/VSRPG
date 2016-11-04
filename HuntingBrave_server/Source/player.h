
#pragma once

//*****************************************************************************************************************************
//
//	Playerクラス
//
//*****************************************************************************************************************************

//	include
#include	"GameData.h"
#include	"BaseChara.h"

//	class
class Player : public BaseChara
{
private:
	PlayerParam	pParam;

public:
	//	初期化・解放
	Player( void );
	~Player( void )override;

	//	更新
	bool Update( PlayerParam& param );

	//	動作関数
	void	Move( void );
	void	AngleAdjust( const Vector3& moveVec, float adjustSpeed );
	void	AngleAdjustParent( const Vector3& direction, float adjustSpeed );

	//	情報設定
	void	SetMotion( int motion );
};


