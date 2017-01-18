
#pragma once

//***************************************************************
//
//	GameManagerクラス
//
//***************************************************************

//	include
#include	"Singleton.h"
#include	"CSVReader.h"


namespace
{
	//	シーン
	namespace SCENE
	{
		enum
		{
			TITLE,
			MATCHING,
			MAIN,
			RESULT,
			END
		};
	}

	//	アップグレードデータ
	namespace UPGRADE_DATA
	{
		enum
		{
			NAME,
			ATTACK,
			DIFENSE,
			MAGIC_ATTACK,
			MAGIC_DIFENSE,
			HP,
			SPEED,
			TEXT
		};
	}
}

//	class
class GameManager : public Singleton<GameManager>
{
	//	コンストラクタを呼ぶためにfriend設定
	friend Singleton<GameManager>;

public:
	float	timer;
	bool	isComplete;		//接続時に準備完了したかどうか
	char	scene;
	bool	changeSceneFrag;
	bool	gameState; 
	std::vector<std::vector<string>>		playerData;
	std::vector<std::vector<string>>		enemyData;

private:
	//	初期化・解放
	GameManager( void );
	~GameManager( void )override;
	bool	LoadData( void );

public:
	//	初期化・解放
	bool	Initialize( void );
	void	Release( void );

	//	更新・描画
	void	Update( void );

	//	動作関数
	void	ChangeScene( char nextScene );

	//	情報設定
	void	SetTimer( float time ){ timer = time; }
	void	SetScene( char scene ){ this->scene = scene; }
	void	SetChangeSceneFrag( bool state ){ changeSceneFrag = state; }

	//	情報取得
	float		GetTime( void ){ return timer; }
	bool		GetIsComplete( void ){ return isComplete; }
	bool		GetChangeSceneFrag( void ){ return	changeSceneFrag; }
	char		GetNextScene( void ){ return scene; }
	bool		GetGameState( void ){ return	gameState; }

	//	アップグレードデータ取得
	int		GetUpGrade( char type, char upGradeData, char level );
	char*	GetFlavorText( char type, char level );
};

#define	gameManager ( GameManager::GetInstance() )
