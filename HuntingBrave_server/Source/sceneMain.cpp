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
//	sceneMain�N���X
//
//************************************************************************
//
//--------------------------------------------------------------------------------------------
//	�O���[�o��
//--------------------------------------------------------------------------------------------
//
//
//--------------------------------------------------------------------------------------------
//	�������E���
//--------------------------------------------------------------------------------------------
//
//		������
//	bool	sceneMain::Initialize( void )
//	{
//		scene = SCENE::MAIN;
//
//			������
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
//		���
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
//	�X�V
//--------------------------------------------------------------------------------------------
//
//		�X�V
//	void	sceneMain::Update( int client )
//	{
//			�}�l�[�W���[�X�V
//		gameManager->Update();
//
//			���@�X�V
//		magicManager->Update();
//
//		if ( client != -1 )
//		{
//				�S�̍X�V
//			playerManager->Update( client );
//
//				�����蔻��
//			collision->AllCollision();
//
//				�N���C�A���g�֑��M
//			gameParam->Send( client );
//		}
//	}
//
