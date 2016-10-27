
#pragma once

//***************************************************************
//
//	EnemyManagerクラス
//
//***************************************************************

//	include
#include	"Singleton.h"
#include	<list>
#include	"BigEnemy.h"
#include	"SmallEnemy.h"

//	class
class EnemyManager : public Singleton<EnemyManager>
{
	friend class Singleton<EnemyManager>;

private:
	//	パラメータ
	std::list<Enemy*> enemylist;


	//	初期化・解放
	EnemyManager( void );
	~EnemyManager( void )override;

public:
	//	初期化・解放
	bool	Initialize( void )override;
	void	Release( void )override;

	//	更新・描画
	void	Update( void );
	void	Render( void );

	//	動作関数
	void	Append( const Vector3& pos, int type );
	void	DistCheck( int n );

	//	情報取得
	//Enemy*	GetEnemy(void);
};

#define	enemyManager ( EnemyManager::GetInstance() )
