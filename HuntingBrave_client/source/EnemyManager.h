
#pragma once

//***************************************************************
//
//	EnemyManagerクラス
//
//***************************************************************

//	include
#include	"Singleton.h"
#include	<list>
#include	"Timer.h"
#include	"Wolf.h"
#include	"Moffu.h"
#include	"shadow.h"

//	class
class EnemyManager : public Singleton<EnemyManager>
{
	friend class Singleton<EnemyManager>;

public:
	enum ENEMY_TYPE
	{
		WOLF,
		MOFFU,
		SHADOW,
		TYPE_MAX,
	};

private:
	//	パラメータ
	std::list<Enemy*> enemylist;
	iex3DObj*	org[ENEMY_TYPE::TYPE_MAX];
	bool		appendOK;

	std::vector<Enemy*>	netList;

	int lifeUpParam[ENEMY_TYPE::TYPE_MAX];

	Timer*	timer;

	//	初期化・解放
	EnemyManager( void );
	~EnemyManager( void )override;

public:
	//	初期化・解放
	bool	Initialize( void );
	void	Release( void );
	void	Load( void );

	//	更新・描画
	void	Update( void );
	void	Render( void );
	void	RenderHp( void );

	//	動作関数
	void	Append( const Vector3& pos, char type );
	void	PosCheck( Enemy*	enemy );
	void	PlayerPosCheck( Enemy*	eneny );
	void	AddRegularTimeIntervals( void );
	void	LifeUP( void );

	//	情報設定

	//	情報取得
	std::list<Enemy*>&	GetList( void );
};

#define	enemyManager ( EnemyManager::GetInstance() )
