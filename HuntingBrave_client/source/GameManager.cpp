
#include	"iextreme.h"
#include	<vector>
#include	<memory>
#include	"GlobalFunction.h"
#include	"GameParam.h"
#include	"system/Framework.h"
#include	"sceneMatching.h"
#include	"sceneMain.h"
#include	"sceneResult.h"
#include	"sceneTitle.h"
#include	"sceneLoad.h"
#include	"LevelManager.h"
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
	GameManager::GameManager( void ) : 
		timer( 0 ),
		isComplete( false ), changeSceneFrag( false ), gameState( false )
	{
		//	フォント追加
		AddFontResourceEx( "DATA/font001.TTF", FR_PRIVATE, NULL );

		scene = SCENE::MATCHING;

		//	初期化
		Initialize();
	}

	//	デストラクタ
	GameManager::~GameManager( void )
	{
		Release();
	}

	//	初期化
	bool	GameManager::Initialize( void )
	{
		//	CSV読み込み
		LoadData();

		//	初期パラメータ読み込み
		int power = GetUpGrade( 0, UPGRADE_DATA::ATTACK, 0 );
		int defense = GetUpGrade( 0, UPGRADE_DATA::DIFENSE, 0 );
		int magicAttack = GetUpGrade( 0, UPGRADE_DATA::MAGIC_ATTACK, 0 );
		int magicDefense = GetUpGrade( 0, UPGRADE_DATA::MAGIC_DIFENSE, 0 );
		int hp = GetUpGrade( 0, UPGRADE_DATA::HP, 0 );
		float speed = GetUpGrade( 0, UPGRADE_DATA::SPEED, 0 );
		
		//	初期値設定
		gameParam->GetPlayerStatus().Initialize(
			power, defense, magicAttack, magicDefense, hp, speed );
		return	true;
	}

	//	解放
	void	GameManager::Release( void )
	{
		
	}

	//	CSV読み込み
	bool	GameManager::LoadData( void )
	{
		//	CSVファイル
		fstream playerStream( "DATA/player_data.csv" );

		//	CSVリーダー初期化
		std::unique_ptr<CSVReader>	reader = 
			std::make_unique<CSVReader>( playerStream );

		//	ファイルから読み込み、vector配列に保存する
		playerData.clear();
		int index = 0;
		while (1)
		{
			playerData.resize( index + 1 );
			reader->Read( playerData[index] );
			if ( playerData[index].size() == 0 )	break;
			index++;
		}
		return	true;
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
			MainFrame->ChangeScene( new sceneLoad( new sceneTitle() ) );
			break;

		case SCENE::MATCHING:
			MainFrame->ChangeScene( new sceneMatching() );
			break;

		case SCENE::MAIN:
			MainFrame->ChangeScene( new sceneLoad( new sceneMain() ) );
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

	//	アップグレードデータ取得
	int	GameManager::GetUpGrade( char type, char upGradeData, char level )
	{
		return	std::stoi( playerData[1 + ( type * 5 )+ level][upGradeData] );
	}

	//	フレーバーテキスト取得
	char*	GameManager::GetFlavorText( char type, char level )
	{
		//	一行目は説明なのでスキップ
		string str = playerData[2 + ( type * 7 ) + level][UPGRADE_DATA::TEXT];
		int length = str.length();
		char*	ret = new char[length + 1];
		memcpy( ret, str.c_str(), length + 1 );
		return	ret;
	}