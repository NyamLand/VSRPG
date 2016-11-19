
#define	_CRT_SECURE_NO_WARNINGS
#include	<stdio.h>
#include	"iextreme.h"
#include	"GameData.h"
#include	"GameManager.h"
#include	"GameParam.h"
#include	"PlayerManager.h"
#include	"PointManager.h"
#include	"InputManager.h"
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
}
