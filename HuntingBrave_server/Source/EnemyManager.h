
#pragma once

//*****************************************************************************************************************************
//
//	EnemyManagerクラス
//
//*****************************************************************************************************************************

//	include
#include	"Enemy.h"
#include	"Timer.h"

//	class
class EnemyManager
{
private:
	std::vector<Enemy*>		enemyList;
	Timer*	timer;

public:
	//	初期化・解放
	EnemyManager( void );
	~EnemyManager( void );
	bool	Initialize( void );
	void	Release( void );
	
	//	更新
	void	Update( float deltaTime );
	void	SendErase( int index );
	void	SendAppend( const Vector3& pos, float angle );

	//	動作関数
	void	Append( const Vector3& pos, float angle );
	void	PosCheck( Enemy*	enemy );
	void	PlayerPosCheck( Enemy*	eneny );

	//	情報設定
	void	TimerStart( void );

	//	情報取得
};

extern	EnemyManager* enemyManager;