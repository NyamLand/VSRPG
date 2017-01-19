
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
	UpGradeUI*	upGradeUI;

	//	�v���C���[�ԍ�
	int				p_num;

	//	neta
	Image*			yaju;
	bool			check;

	//	test
	int				hp;

public:
	//	�������E���
	bool	Initialize( void );
	void	Release( void );

	//	�X�V�E�`��
	void	Update(void);
	void	Render(void);
};

#define	uiManager ( UIManager::GetInstance() )
