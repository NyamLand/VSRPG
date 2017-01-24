
#pragma once

//*************************************************************************
//
//	KillLogUIクラス
//
//*************************************************************************

//	include
#include	"Image.h"

//	class
class KillLogUI
{
private:
	Image*		killLogImage;
	bool	killFrag;
	float	percentage;

public:
	//	初期化・解放
	KillLogUI( void );
	~KillLogUI( void );

	//	更新・描画
	void	Update( void );
	void	Render( void );
	
	//	情報設定
	void	SetKillLog( int killer, int dead );
};
