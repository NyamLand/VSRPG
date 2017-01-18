
#pragma once

//***************************************************************
//
//	LightSphereEffectクラス
//
//***************************************************************

//	include
#include	"Effect.h"

//	class
class LightSphereEffect : public Effect
{
private:
	DWORD	color;
	float			speed;
	float			percentage;

public:
	//	初期化・解放
	LightSphereEffect( void );
	~LightSphereEffect( void )override;

	//	更新・描画
	void	Update( void )override;
	void	Render( void )override;

	//	情報取得
	
};