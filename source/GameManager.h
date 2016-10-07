
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

private:
	float timer;

private:
	//	�������E���
	GameManager( void );
	~GameManager( void )override;

public:
	//enum TIMER
	//{
	//	TIME_MAX = 120
	//};
	static const int TIME_MAX = 120;

public:
	//	�������E���
	bool	Initialize( void )override;
	void	Release( void )override;

	//	�X�V�E�`��
	void	Update( void );

	//	����֐�
	void	TimerCount( int );

	//	�Q�b�^�[�E�Z�b�^�[
	float	GetTimer( void ){ return timer; }
};

#define	gameManager ( GameManager::GetInstance() )
