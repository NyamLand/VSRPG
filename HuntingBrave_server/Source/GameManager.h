
#pragma once

//*****************************************************************************************************************************
//
//	GameManager�N���X
//
//*****************************************************************************************************************************

//	include
#include	"GameData.h"
#include	"Timer.h"

namespace UPGRADE_DATA
{
	enum
	{
		NAME,
		ATTACK,
		DEFENSE,
		MAGIC_ATTACK,
		MAGIC_DIFENSE,
		HP,
		SPEED,
		TEXT
	};
}

//	class
class GameManager
{
private:
	MatchingInfo	matchingInfo[PLAYER_MAX];
	PlayerParam		initPlayerParam[PLAYER_MAX];
	Timer*	timer;
	bool		timeUp;
	bool		gameState;

	std::vector<std::vector<std::string>>	playerData;

public:
	//	�������E���
	GameManager( void );
	~GameManager( void );
	bool	Initialize( void );
	void	Release( void );
	void	LoadData( void );
	void	MatchingInfoInitialize( void );
	void	InitializeStatus( PlayerStatus& playerStatus );

	//	�X�V
	void	Update( void );

	//	����֐�
	bool	PlayerCheck( void );
	void	ChangeScene( char& out, char nextScene );

	//	���ݒ�
	void	SetGameState( bool state );
	void	SetMatchingInfo( int id, bool state );

	//	���擾
	Timer*&	GetTimer( void );
	PlayerParam	GetInitInfo( int id )const;
	MatchingInfo&	GetMatchingInfo( int id );
	bool	GetTimeUp( void );
	bool	GetGameState( void );

	//	�A�b�v�O���[�h�f�[�^�擾
	int	GetInitStatus( char upGradeData );
	float	GetInitSpeed( void );
	int	GetUpGrade( char levelType, char upGradeData, char level );
	float GetUpGradeSpeed( char levelType, char level );
};

extern	GameManager*	gameManager;