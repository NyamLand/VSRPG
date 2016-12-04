
#include	"iextreme.h"

#include	"GlobalFunction.h"
#include	"system/Framework.h"
#include	"sceneMatching.h"
#include	"sceneMain.h"
#include	"sceneResult.h"
#include	"sceneTitle.h"
#include	"GameManager.h"

//***************************************************************
//
//	GameManagerクラス
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	グローバル	
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	初期化・解放
//---------------------------------------------------------------------------------------

	//	コンストラクタ
	GameManager::GameManager( void ) : timer(0), isComplete( false ), changeSceneFrag( false )
	{
		scene = SCENE::MATCHING;
	}

	//	デストラクタ
	GameManager::~GameManager( void )
	{

	}

	//	初期化
	bool	GameManager::Initialize( void )
	{
		return	true;
	}

	//	解放
	void	GameManager::Release( void )
	{

	}

	//	クライアント初期化
	void	GameManager::InitializeClient( void )
	{
		////	WinSock初期化
		//WSADATA	wsaData;
		//WSAStartup( MAKEWORD( 1, 1 ), &wsaData );
	}

//---------------------------------------------------------------------------------------
//	更新・描画
//---------------------------------------------------------------------------------------

	//	更新
	void	GameManager::Update( void )
	{
		
	}

//---------------------------------------------------------------------------------------
//	動作関数
//---------------------------------------------------------------------------------------

	//	シーン切り替え
	void	GameManager::ChangeScene( char nextScene )
	{
		if ( !changeSceneFrag )	return;

		//	シーン切り替え
		switch ( nextScene )
		{
		case SCENE::TITLE:
			MainFrame->ChangeScene( new sceneTitle() );
			break;

		case SCENE::MATCHING:
			MainFrame->ChangeScene( new sceneMatching() );
			break;

		case SCENE::MAIN:
			MainFrame->ChangeScene( new sceneMain() );
			break;

		case SCENE::RESULT:
			MainFrame->ChangeScene( new sceneResult() );
			break;
		}

		changeSceneFrag = false;
	}

//---------------------------------------------------------------------------------------
//	情報設定
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	情報取得
//---------------------------------------------------------------------------------------

