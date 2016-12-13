
#pragma once

//***************************************************************
//
//	UpGradeUIクラス
//
//***************************************************************

//	include
#include	"Image.h"

//	class
class UpGradeUI
{
private:
	Image*	 back;
	Image*	*	typeIcon;
	Image**	levelIcon;

public:
	//	初期化・解放
	UpGradeUI( void );
	~UpGradeUI( void );
	
	//	更新・描画
	void	Update( void );
	void	Render( void );
};
