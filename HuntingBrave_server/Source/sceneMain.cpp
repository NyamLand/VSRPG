
#define	_CRT_SECURE_NO_WARNINGS
#include	<stdio.h>
#include	"iextreme.h"
#include	"GameData.h"
#include	"GameManager.h"
#include	"GameParam.h"
#include	"PlayerManager.h"
#include	"sceneMain.h"

GameParam*		gameParam;

//*****************************************************************************************************************************
//
//	main
//
//*****************************************************************************************************************************

//	main
void main( void )
{
	gameManager = new GameManager();
	gameParam = new GameParam();
	playerManager = new PlayerManager( gameParam );
	gameParam->InitializeServer();

	for (;;)
	{
		//	�}�l�[�W���[�X�V
		gameManager->Update();
		
		//	�N���C�A���g�����M
		int client = gameParam->Receive();
		if ( client != -1 )
		{
			//	�v���C���[�X�V
			playerManager->Update( client );

			//	�N���C�A���g�֑��M
			gameParam->Send( client );
		}
	}

	//	���
	delete	gameParam;
	delete	gameManager;
	delete	playerManager;
}
