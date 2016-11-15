
#define	_CRT_SECURE_NO_WARNINGS
#include	<stdio.h>
#include	"iextreme.h"
#include	"GameData.h"
#include	"GameManager.h"
#include	"GameParam.h"
#include	"PlayerManager.h"
#include	"PointManager.h"
#include	"InputManager.h"
#include	"sceneMain.h"

GameParam*		gameParam = nullptr;

//*****************************************************************************************************************************
//
//	main
//
//*****************************************************************************************************************************

//	main
void main( void )
{
	//	������
	gameManager = new GameManager();
	gameParam = new GameParam();
	inputManager = new InputManager();
	playerManager = new PlayerManager( gameParam );
	pointManager = new PointManager( gameParam );
	gameParam->InitializeServer();

	//	�������[�v
	for (;;)
	{
		//	�}�l�[�W���[�X�V
		gameManager->Update();
		
		//	�N���C�A���g�����M
		int client = gameParam->Receive();
		if ( client != -1 )
		{
			//	�S�̍X�V
			pointManager->Update( client );
			playerManager->Update( client );

			//	�N���C�A���g�֑��M
			gameParam->Send( client );
		}
	}

	//	���
	delete	gameParam;		gameParam = nullptr;
	delete	gameManager;	gameManager = nullptr;
	delete	playerManager;	playerManager = nullptr;
	delete	pointManager;	pointManager = nullptr;
	delete	inputManager;	inputManager = nullptr;
}
