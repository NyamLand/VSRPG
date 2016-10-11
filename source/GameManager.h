
#pragma once

//***************************************************************
//
//	GameManager�N���X
//
//***************************************************************

//	include
#include	"Singleton.h"

//	class
class GameManager : public Singleton<GameManager>
{
	//	�R���X�g���N�^���ĂԂ��߂�friend�ݒ�
	friend Singleton<GameManager>;
public:
	//	�萔
	static const int TIME_MAX = 120;

private:
	float timer;

private:
	//	�������E���
	GameManager( void );
	~GameManager( void )override;

public:
	//	�������E���
	bool	Initialize( void )override;
	void	Release( void )override;
	void	InitializeClient( void );

	//	�X�V�E�`��
	void	Update( void );

	//	����֐�
	void	TimerCount();

	//	�Q�b�^�[�E�Z�b�^�[
	float	GetTimer( void ){ return timer; }
};

#define	gameManager ( GameManager::GetInstance() )
