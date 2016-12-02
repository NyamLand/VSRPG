
#pragma once

//***************************************************************
//
//	GameManagerクラス
//
//***************************************************************

//	include
#include	"Singleton.h"

namespace SCENE
{
	enum
	{
		MATCHING,
		MAIN,
		RESULT,
		END
	};
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

private:
	//	初期化・解放
	GameManager( void );
	~GameManager( void )override;

public:
	//	初期化・解放
	bool	Initialize( void )override;
	void	Release( void )override;
	void	InitializeClient( void );

	//	更新・描画
	void	Update( void );

	//	情報設定
	void	SetTimer( float time ){ timer = time; }
	void	SetScene( char scene ){ this->scene = scene; }

	//	情報取得
	float		GetTime( void ){ return timer; }
	bool		GetIsComplete( void ){ return isComplete; }
	char		GetNextScene( void ){ return scene; }
};

#define	gameManager ( GameManager::GetInstance() )
