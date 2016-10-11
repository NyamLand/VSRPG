
#pragma once

//***************************************************************
//
//	GameManager�N���X
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

	//	�������E���
	GameManager( void );
	~GameManager( void );

public:
	//	�������E���
	bool	Initialize( void );
	void	Release( void );

	//	���擾
	Vector3	GetInitPos( int id )const;
};

#define	gameManager ( GameManager::GetInstance() )

