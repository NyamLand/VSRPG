
#pragma once

//***************************************************************
//
//	UIManagerクラス
//
//***************************************************************


//	include
#include	"Singleton.h"
#include	"GameManager.h"
#include	"Image.h"
#include	<vector>
#include	"NumberUI.h"
#include	"TimerUI.h"
#include	"HpUI.h"
#include	"ExpUI.h"
#include	"ItemUI.h"
#include	"MapUI.h"
#include	"ScoreUI.h"
#include	"UpGradeUI.h"
#include	"ScoreBoardUI.h"

//	class
class UIManager : public Singleton<UIManager> 
{
	//	コンストラクタを呼ぶためにfriend設定
	friend Singleton<UIManager>;

private:
	//	初期化・解放
	UIManager(void);
	~UIManager(void)override;

private:
	TimerUI*		timerUI;
	HpUI*			hpUI;
	ExpUI*			expUI;
	ItemUI*			itemUI;
	MapUI*			mapUI;
	ScoreUI*		scoreUI;
	ScoreBoardUI*	boardUI;
	UpGradeUI*	upGradeUI;

	//	プレイヤー番号
	int				p_num;

	//	neta
	Image*			yaju;
	bool			check;

	//	test
	int				hp;

public:
	//	初期化・解放
	bool	Initialize( void );
	void	Release( void );

	//	更新・描画
	void	Update(void);
	void	Render(void);
};

#define	uiManager ( UIManager::GetInstance() )
