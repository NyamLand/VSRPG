
#pragma once

//*****************************************************************************************************************************
//
//	GameManagerクラス
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
	//	初期化・解放
	GameManager( void );
	~GameManager( void );
	bool	Initialize( void );
	void	Release( void );
	void	LoadData( void );
	void	MatchingInfoInitialize( void );
	void	InitializeStatus( PlayerStatus& playerStatus );

	//	更新
	void	Update( void );

	//	動作関数
	bool	PlayerCheck( void );
	void	ChangeScene( char& out, char nextScene );

	//	情報設定
	void	SetGameState( bool state );
	void	SetMatchingInfo( int id, bool state );

	//	情報取得
	Timer*&	GetTimer( void );
	PlayerParam	GetInitInfo( int id )const;
	MatchingInfo&	GetMatchingInfo( int id );
	bool	GetTimeUp( void );
	bool	GetGameState( void );

	//	アップグレードデータ取得
	int	GetInitStatus( char upGradeData );
	float	GetInitSpeed( void );
	int	GetUpGrade( char levelType, char upGradeData, char level );
	float GetUpGradeSpeed( char levelType, char level );
};

extern	GameManager*	gameManager;