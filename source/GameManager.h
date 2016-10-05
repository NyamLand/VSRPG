
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

private:
	//	初期化・解放
	GameManager( void );
	~GameManager( void )override;

public:
	//	初期化・解放
	bool	Initialize( void )override;
	void	Release( void )override;

	//	更新・描画
	void	Update( void );
};

#define	gameManager ( GameManager::GetInstance() )
