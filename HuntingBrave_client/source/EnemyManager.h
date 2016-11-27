
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

public:
	enum ENEMY_TYPE
	{
		BIG_ENEMY,
		SMALL_ENEMY,
		TYPE_MAX,
	};

private:
	//	パラメータ
	std::list<Enemy*> enemylist;
	iex3DObj*	org[ENEMY_TYPE::TYPE_MAX];
	bool		appendOK;

	//	初期化・解放
	EnemyManager( void );
	~EnemyManager( void )override;

public:
	//	初期化・解放
	bool	Initialize( void )override;
	void	Release( void )override;
	void	Load( void );

	//	更新・描画
	void	Update( void );
	void	Render( void );

	//	動作関数
	void	Append( const Vector3& pos, int type );
	void	PosCheck( Enemy*	enemy );
	void	PlayerPosCheck( Enemy*	eneny );
	void	AddRegularTimeIntervals( void );

	//	情報設定

	//	情報取得
	std::list<Enemy*>&	GetList( void );
};

#define	enemyManager ( EnemyManager::GetInstance() )
