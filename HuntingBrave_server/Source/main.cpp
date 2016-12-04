
#define	_CRT_SECURE_NO_WARNINGS
#include	<stdio.h>
#include	<vector>
#include	<thread>
#include	<map>
#include	"iextreme.h"
#include	"FrameWork.h"
#include	"GameParam.h"
#include	"GameManager.h"
#include	"MagicManager.h"
#include	"LevelManager.h"
#include	"PointManager.h"
#include	"PlayerManager.h"
#include	"InputManager.h"
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
	collision = new Collision( gameParam );
	gameParam->InitializeServer();

	//	�������[�v
	for (;;)
	{
		gameManager->Update();
		
		//	����M
		int client = gameParam->Receive( scene );
		magicManager->Update();

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
	delete collision;				collision = nullptr;
}

void	MatchingUpdate( int client )
{
	bool	check = gameManager->PlayerCheck();
	if ( check )
	{
		gameManager->ChangeScene( scene, SCENE::MAIN );
		playerManager->Initialize();
		gameManager->MatchingInfoInitialize();
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
		playerManager->Release();
	}
}

void	ResultUpdate( int client )
{
	if ( client == -1 )	return;
}