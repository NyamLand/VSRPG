
#pragma once

//***************************************************************
//
//	GameManager�N���X
//
//***************************************************************

//	include
#include	"Singleton.h"
#include	"CSVReader.h"


namespace
{
	//	�V�[��
	namespace SCENE
	{
		enum
		{
			TITLE,
			MATCHING,
			MAIN,
			RESULT,
			END
		};
	}

	//	�A�b�v�O���[�h�f�[�^
	namespace UPGRADE_DATA
	{
		enum
		{
			NAME,
			ATTACK,
			DIFENSE,
			MAGIC_ATTACK,
			MAGIC_DIFENSE,
			HP,
			SPEED,
			TEXT
		};
	}
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
	bool	gameState; 
	std::vector<std::vector<string>>		playerData;
	std::vector<std::vector<string>>		enemyData;

private:
	//	�������E���
	GameManager( void );
	~GameManager( void )override;
	bool	LoadData( void );

public:
	//	�������E���
	bool	Initialize( void );
	void	Release( void );

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
	bool		GetGameState( void ){ return	gameState; }

	//	�A�b�v�O���[�h�f�[�^�擾
	int		GetUpGrade( char type, char upGradeData, char level );
	char*	GetFlavorText( char type, char level );
};

#define	gameManager ( GameManager::GetInstance() )
