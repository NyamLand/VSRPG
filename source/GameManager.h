
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
	float timer;

private:
	//	初期化・解放
	GameManager( void );
	~GameManager( void )override;

public:
	//enum TIMER
	//{
	//	TIME_MAX = 120
	//};
	static const int TIME_MAX = 120;

public:
	//	初期化・解放
	bool	Initialize( void )override;
	void	Release( void )override;

	//	更新・描画
	void	Update( void );

	//	動作関数
	void	TimerCount( int );

	//	ゲッター・セッター
	float	GetTimer( void ){ return timer; }
};

#define	gameManager ( GameManager::GetInstance() )
