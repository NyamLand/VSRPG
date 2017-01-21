
#define	_CRT_SECURE_NO_WARNINGS
#include	<stdio.h>
#include	<vector>
#include	<thread>
#include	<map>
#include	"iextreme.h"
#include	"GameParam.h"
#include	"GameManager.h"
#include	"MagicManager.h"
#include	"LevelManager.h"
#include	"PointManager.h"
#include	"PlayerManager.h"
#include	"InputManager.h"
#include	"ItemManager.h"
#include	"EnemyManager.h"
#include	"Collision.h"


//*****************************************************************************************************************************
//
//	main
//
//*****************************************************************************************************************************

//	�ϐ��錾
char	scene = SCENE::MATCHING;

//	�v���g�^�C�v�錾
void	MatchingUpdate( int client );
void	MainUpdate( int client );
void	ResultUpdate( int client );
void	AlwaysUpdate( void );
void	Update( void );

//	main
void main( void )
{
	//	������
	gameManager = new GameManager();
	gameParam = new GameParam();
	inputManager = new InputManager();
	magicManager = new MagicManager();
	levelManager = new LevelManager();
	pointManager = new PointManager();
	playerManager = new PlayerManager( gameParam );
	itemManager = new ItemManager();
	enemyManager = new EnemyManager();
	collision = new Collision( gameParam );
	gameParam->InitializeServer();
	gameManager->Initialize();

	//	�������[�v
	for (;;)
	{
		gameManager->Update();
		
		//	����M
		std::thread	ThreadUpdate( AlwaysUpdate );
		int client = gameParam->Receive( scene );
		ThreadUpdate.join();

		switch ( scene )
		{
		case SCENE::MATCHING:
			MatchingUpdate( client );
			break;

		case SCENE::MAIN:
			MainUpdate( client );
			break;

		case SCENE::RESULT:
			ResultUpdate( client );
			break;
		}

		//	���M
		gameParam->Send( client );
	}

	//	���
	delete gameManager;		gameManager = nullptr;
	delete gameParam;			gameParam = nullptr;
	delete inputManager;		inputManager = nullptr;
	delete magicManager;		magicManager = nullptr;
	delete levelManager;		levelManager = nullptr;
	delete pointManager;		pointManager = nullptr;
	delete playerManager;		playerManager = nullptr;
	delete enemyManager;		enemyManager = nullptr;
	delete collision;				collision = nullptr;
}

void	MatchingUpdate( int client )
{
	bool	check = gameManager->PlayerCheck();
	if ( check )
	{
		gameManager->ChangeScene( scene, SCENE::MAIN );
		playerManager->Initialize();
		enemyManager->Initialize();
		gameManager->Initialize();	
	}
}

void	MainUpdate( int client )
{
	if ( client == -1 )	return;
	playerManager->Update( client );
	collision->AllCollision();
	if ( gameManager->GetTimeUp() )
	{
		gameManager->ChangeScene( scene, SCENE::RESULT );
		itemManager->Release();
		playerManager->Release();
		enemyManager->Release();
	}
}

void	ResultUpdate( int client )
{
	gameManager->ChangeScene( scene, SCENE::MATCHING );
	gameParam->InitializeGame();
	gameManager->Initialize();
	itemManager->Initialize();
}

//	thread
void	AlwaysUpdate( void )
{
	magicManager->Update();
	enemyManager->Update();
	itemManager->Update();
}