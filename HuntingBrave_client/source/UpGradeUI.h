
#pragma once

//***************************************************************
//
//	UpGradeUIクラス
//
//***************************************************************

//	include
#include	"Image.h"
#include	"ExpUI.h"
#include	"Font.h"

//	class
class UpGradeUI
{
private:
	Image*	 back;
	Image*	*	typeIcon;
	Image**	levelIcon;
	Image*		curLevelIcon;
	ExpUI*		expUI;
	Font*		flavorText;

	float		percentage;
	float		percentage2;

	char		select;
	char		beforeSelect;
	LPSTR	text;

	int id;

public:
	//	初期化・解放
	UpGradeUI( void );
	~UpGradeUI( void );
	
	//	更新・描画
	void	Update( void );
	void	Render( void );

	//	動作関数
	void	Dicision( void );

	//	情報設定
	void	SetBigIconSrcPos( void );
};
