
#define	_CRT_SECURE_NO_WARNINGS
#include	<stdio.h>
#include	<vector>
#include	<map>
#include	"iextreme.h"
#include	"GameData.h"
#include	"GameManager.h"
#include	"GameParam.h"
#include	"PlayerManager.h"
#include	"PointManager.h"
#include	"InputManager.h"
#include	"MagicManager.h"
#include	"LevelManager.h"
#include	"Collision.h"
#include	"sceneMain.h"

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
	magicManager = new MagicManager();
	levelManager = new LevelManager();
	playerManager = new PlayerManager( gameParam );
	collision = new Collision( gameParam );
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
			//	���@�X�V
			magicManager->Update();

			//	�����蔻��
			collision->AllCollision();

			//	�S�̍X�V
			playerManager->Update( client );

			//	�N���C�A���g�֑��M
			gameParam->Send( client );
		}
	}

	//	���
	delete	gameParam;		gameParam = nullptr;
	delete	gameManager;		gameManager = nullptr;
	delete	playerManager;	playerManager = nullptr;
	delete	inputManager;		inputManager = nullptr;
	delete	magicManager;	magicManager = nullptr;
}
