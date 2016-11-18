
#pragma once

//***************************************************************
//
//	GameManager�N���X
//
//***************************************************************

//	include
#include	"Singleton.h"

namespace SCENE
{
	enum
	{
		MATCHING,
		MAIN
	};
}

//	class
class GameManager : public Singleton<GameManager>
{
	//	�R���X�g���N�^���ĂԂ��߂�friend�ݒ�
	friend Singleton<GameManager>;

public:
	int		timer;
	bool	isComplete;		//�ڑ����ɏ��������������ǂ���


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

	//	���ݒ�
	void	SetTimer( int time ){ timer = time; }

	//	���擾
	int		GetTime( void ){ return timer; }
	bool		GetIsComplete(void){ return isComplete; }
};

#define	gameManager ( GameManager::GetInstance() )
