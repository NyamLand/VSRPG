
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
	bool	changeSceneFrag;

private:
	//	�������E���
	GameManager( void );
	~GameManager( void )override;

public:
	//	�������E���
	bool	Initialize( void );
	void	Release( void );
	void	InitializeClient( void );

	//	�X�V�E�`��
	void	Update( void );

	//	����֐�
	void	ChangeScene( char nextScene );

	//	���ݒ�
	void	SetTimer( float time ){ timer = time; }
	void	SetScene( char scene ){ this->scene = scene; }
	void	SetChangeSceneFrag( bool state ){ changeSceneFrag = state; }

	//	���擾
	float		GetTime( void ){ return timer; }
	bool		GetIsComplete( void ){ return isComplete; }
	bool		GetChangeSceneFrag( void ){ return	changeSceneFrag; }
	char		GetNextScene( void ){ return scene; }
};

#define	gameManager ( GameManager::GetInstance() )
