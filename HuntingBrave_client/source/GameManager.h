
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
		MAIN
	};
}

//	class
class GameManager : public Singleton<GameManager>
{
	//	コンストラクタを呼ぶためにfriend設定
	friend Singleton<GameManager>;

public:
	float		timer;
	bool	isComplete;		//接続時に準備完了したかどうか


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

	//	情報取得
	float		GetTime( void ){ return timer; }
	bool		GetIsComplete(void){ return isComplete; }
};

#define	gameManager ( GameManager::GetInstance() )
