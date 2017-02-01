
#pragma once

//***************************************************************
//
//	Resultクラス
//
//***************************************************************

//	include
#include	"NameUI.h"
#include	"PlayerTitleUI.h"
#include	"GameData.h"
#include	"Stage.h"

//	class
class TestResult
{
private:
	Stage*	stage;

public:
	//	初期化・解放
	TestResult( void );
	~TestResult( void );

	//	更新・描画
	void	Update( void );
	void	Render( void );
};
