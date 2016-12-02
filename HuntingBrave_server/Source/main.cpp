
#define	_CRT_SECURE_NO_WARNINGS
#include	<stdio.h>
#include	<vector>
#include	<map>
#include	"iextreme.h"
#include	"FrameWork.h"
#include	"GameParam.h"
#include	"GameManager.h"
#include	"sceneMatching.h"
#include	"InputManager.h"
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
	mainFrame = new FrameWork();
	gameManager = new GameManager();
	gameParam = new GameParam();
	inputManager = new InputManager();
	gameParam->InitializeServer();

	mainFrame->ChangeScene( new sceneMatching() );

	//	�������[�v
	for (;;)
	{
		//	����M
		int client = gameParam->Receive( mainFrame->GetScene() );

		mainFrame->Update( client );
	}

	//	���
	delete	gameParam; gameParam = nullptr;
	delete	mainFrame;	mainFrame = nullptr;
	delete	gameManager;	gameManager = nullptr;
	delete	inputManager;	inputManager = nullptr;
}