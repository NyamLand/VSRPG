
#pragma once

//***************************************************************
//
//	GameManagerクラス
//
//***************************************************************

//	include
#include	"Singleton.h"

//	class
class GameManager : public Singleton<GameManager>
{
	//	コンストラクタを呼ぶためにfriend設定
	friend Singleton<GameManager>;

public:
	int		timer;

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
	void	SetTimer( int time ){ timer = time; }

	//	情報取得
	int		GetTime( void ){ return timer; }
};

#define	gameManager ( GameManager::GetInstance() )
