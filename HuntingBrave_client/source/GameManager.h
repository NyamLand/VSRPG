
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
		MAIN,
		RESULT,
		END
	};
}

//	class
class GameManager : public Singleton<GameManager>
{
	//	�R���X�g���N�^���ĂԂ��߂�friend�ݒ�
	friend Singleton<GameManager>;

public:
	float	timer;
	bool	isComplete;		//�ڑ����ɏ��������������ǂ���
	char	scene;

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
	void	SetTimer( float time ){ timer = time; }
	void	SetScene( char scene ){ this->scene = scene; }

	//	���擾
	float		GetTime( void ){ return timer; }
	bool		GetIsComplete( void ){ return isComplete; }
	char		GetNextScene( void ){ return scene; }
};

#define	gameManager ( GameManager::GetInstance() )
