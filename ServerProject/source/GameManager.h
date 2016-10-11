
#pragma once

//***************************************************************
//
//	GameManagerクラス
//
//***************************************************************

//	include
#include	"GameData.h"
#include	"Singleton.h"
//	class
class GameManager : public Singleton<GameManager>
{
	friend	Singleton<GameManager>;

private:
	Vector3	initPos[PLAYER_MAX];

	//	初期化・解放
	GameManager( void );
	~GameManager( void );

public:
	//	初期化・解放
	bool	Initialize( void );
	void	Release( void );

	//	情報取得
	Vector3	GetInitPos( int id )const;
};

#define	gameManager ( GameManager::GetInstance() )

