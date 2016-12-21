//
//#include	<stdio.h>
//#include	<vector>
//#include	<map>
//#include	"iextreme.h"
//#include	"GameManager.h"
//#include	"PlayerManager.h"
//#include	"PointManager.h"
//#include	"MagicManager.h"
//#include	"LevelManager.h"
//#include	"Collision.h"
//#include	"sceneMain.h"
//
//************************************************************************
//
//	sceneMainクラス
//
//************************************************************************
//
//--------------------------------------------------------------------------------------------
//	グローバル
//--------------------------------------------------------------------------------------------
//
//
//--------------------------------------------------------------------------------------------
//	初期化・解放
//--------------------------------------------------------------------------------------------
//
//		初期化
//	bool	sceneMain::Initialize( void )
//	{
//		scene = SCENE::MAIN;
//
//			初期化
//		gameManager = new GameManager();
//		magicManager = new MagicManager();
//		levelManager = new LevelManager();
//		pointManager = new PointManager();
//		playerManager = new PlayerManager( gameParam );
//		playerManager->Initialize();
//		collision = new Collision( gameParam );
//
//		return	true;
//	}
//
//		解放
//	sceneMain::~sceneMain( void )
//	{
//		delete	gameManager;			gameManager = nullptr;
//		delete	magicManager;		magicManager = nullptr;
//		delete	levelManager;			levelManager = nullptr;
//		delete	pointManager;			pointManager = nullptr;
//		delete	playerManager;		playerManager = nullptr;
//		delete	collision;					collision = nullptr;
//	}
//
//--------------------------------------------------------------------------------------------
//	更新
//--------------------------------------------------------------------------------------------
//
//		更新
//	void	sceneMain::Update( int client )
//	{
//			マネージャー更新
//		gameManager->Update();
//
//			魔法更新
//		magicManager->Update();
//
//		if ( client != -1 )
//		{
//				全体更新
//			playerManager->Update( client );
//
//				当たり判定
//			collision->AllCollision();
//
//				クライアントへ送信
//			gameParam->Send( client );
//		}
//	}
//
