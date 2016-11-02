
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
		//	マネージャー更新
		gameManager->Update();
		
		//	クライアントから受信
		int client = gameParam->Receive();
		if ( client != -1 )
		{
			//	プレイヤー更新
			playerManager->Update( client );

			//	クライアントへ送信
			gameParam->Send( client );
		}
	}

	//	解放
	delete	gameParam;
	delete	gameManager;
	delete	playerManager;
}
