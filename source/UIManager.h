
#pragma once

//***************************************************************
//
//	UIManager�N���X
//
//***************************************************************

//	include
#include	"Singleton.h"
#include	"GameManager.h"
#include	"TimerUI.h"

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
	TimerUI* timerUI;

public:
	//	�������E���
	bool	Initialize(void)override;
	void	Release(void)override;

	//	�X�V�E�`��
	void	Update(void);
	void	Render(void);
};

#define	uiManager ( UIManager::GetInstance() )
