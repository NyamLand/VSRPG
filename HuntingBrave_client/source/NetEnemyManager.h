
#pragma once

//****************************************************************
//
//	NetEnemyManagerクラス
//
//****************************************************************

//	include
#include	"Singleton.h"
#include	"NetEnemy.h"

//	class
class NetEnemyManager : public Singleton<NetEnemyManager>
{
	friend	class Singleton<NetEnemyManager>;
private:
	iex3DObj*	org;
	std::vector<NetEnemy*>	enemyList;
private:
	//	初期化・解放
	NetEnemyManager( void );
	~NetEnemyManager( void )override;

public:
	//	初期化・解放
	bool	Initialize( void );
	void	Release( void );

	//	更新・描画
	void	Update( void );
	void	Render( void );
	//void	RenderHp(void);
	//	動作関数
	void	Erase( int index );
	void	Append( const Vector3& pos, float angle );

	//	受信関数
	void	Receive( const LPSTR& data );
	void	ReceiveEnemyInfo( const LPSTR& data );
	void	ReceiveMoveInfo( const LPSTR& data );
	void	ReceiveModeInfo( const LPSTR& data );
	void	ReceiveMotionInfo( const LPSTR& data );
	void	ReceiveDeadInfo( const LPSTR& data );
	void	ReceiveEraseInfo( const LPSTR& data );
	void	ReceiveAppendInfo( const LPSTR& data );

	//	情報設定
	void	SetInfo( int index, const Vector3& pos, float angle );
	

	//	情報取得
	std::vector<NetEnemy*>&		GetList( void );
};

#define	netEnemyManager ( NetEnemyManager::GetInstance() )