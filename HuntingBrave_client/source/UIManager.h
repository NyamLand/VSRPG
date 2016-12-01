
#pragma once

//***************************************************************
//
//	UIManager�N���X
//
//***************************************************************


//	include
#include	"Singleton.h"
#include	"GameManager.h"
#include	"Image.h"
#include	"NumberUI.h"
#include	"TimerUI.h"
#include	"HpUI.h"
#include	"ExpUI.h"
#include	"ItemUI.h"
#include	"MapUI.h"
#include	"ScoreUI.h"
#include	"ScoreBoardUI.h"

//	class
class UIManager : public Singleton<UIManager> 
{
	//	�R���X�g���N�^���ĂԂ��߂�friend�ݒ�
	friend Singleton<UIManager>;

private:
	//	�������E���
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

public:
	//	�������E���
	bool	Initialize(void)override;
	void	Release(void)override;

	//	�X�V�E�`��
	void	Update(void);
	void	Render(void);
};

#define	uiManager ( UIManager::GetInstance() )
