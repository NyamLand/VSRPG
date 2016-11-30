
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


//	プロトタイプ宣言
void	sceneTitleUpdate( void );
void	sceneMatchingUpdate( void );
void	sceneMainUpdate( void );
void	sceneResultUpdate( void );

//	main
void main( void )
{
	//	初期化
	GameState	gameState;
	gameManager = new GameManager();
	gameParam = new GameParam();
	inputManager = new InputManager();
	magicManager = new MagicManager();
	levelManager = new LevelManager();
	pointManager = new PointManager();
	collision = new Collision( gameParam );
	playerManager = new PlayerManager( gameParam );
	gameParam->InitializeServer();

	//	無限ループ
	for (;;)
	{
		//	マネージャー更新
		gameManager->Update();
		
		//	クライアントから受信
		int client = gameParam->Receive( gameState.scene );

		//	魔法更新
		magicManager->Update();

		if ( client != -1 )
		{
			//	全体更新
			playerManager->Update( client );

			//	当たり判定
			collision->AllCollision();

			//	クライアントへ送信
			gameParam->Send( client );
		}
	}

	//	解放
	delete	gameParam;		gameParam = nullptr;
	delete	gameManager;		gameManager = nullptr;
	delete	playerManager;	playerManager = nullptr;
	delete	inputManager;		inputManager = nullptr;
	delete	magicManager;	magicManager = nullptr;
	delete	pointManager;		pointManager = nullptr;
}


//	タイトル更新
void	sceneTitleUpdate( void )
{

}

//	マッチング更新
void	sceneMatchingUpdate( void )
{

}

//	メイン更新
void	sceneMainUpdate( void )
{

}

//	リザルト更新
void	sceneResultUpdate( void )
{

}