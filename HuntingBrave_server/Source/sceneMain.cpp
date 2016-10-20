
#define	_CRT_SECURE_NO_WARNINGS
#include	<stdio.h>
#include	"iextreme.h"
#include	"GameData.h"

#include	"GameParam.h"
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
	gameParam = new GameParam();
	gameParam->InitializeServer();

	for (;;)
	{
		int client = gameParam->Receive();
		if ( client != -1 )
		{
			gameParam->Send( client );
		}
	}

	delete	gameParam;
}
