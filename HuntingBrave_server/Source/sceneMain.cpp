
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
	//	初期化
	gameManager = new GameManager();
	gameParam = new GameParam();
	inputManager = new InputManager();
	playerManager = new PlayerManager( gameParam );
	collision = new Collision( gameParam );
	gameParam->InitializeServer();

	//	無限ループ
	for (;;)
	{
		//	マネージャー更新
		gameManager->Update();
		
		//	クライアントから受信
		int client = gameParam->Receive();
		if ( client != -1 )
		{
			//	当たり判定
			collision->AllCollision();

			//	全体更新
			playerManager->Update( client );

			//	クライアントへ送信
			gameParam->Send( client );
		}
	}

	//	解放
	delete	gameParam;		gameParam = nullptr;
	delete	gameManager;		gameManager = nullptr;
	delete	playerManager;	playerManager = nullptr;
	delete	inputManager;		inputManager = nullptr;
}
