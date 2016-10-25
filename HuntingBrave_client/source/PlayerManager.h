
#pragma once

//***************************************************************
//
//	PlayerManagerクラス
//
//***************************************************************

//	include
#include	"Singleton.h"
#include	"Player.h"

//	class
class PlayerManager : public Singleton<PlayerManager>
{
	friend class Singleton<PlayerManager>;

private:
	//	パラメータ
	Player*	player;

	//	初期化・解放
	PlayerManager( void );
	~PlayerManager( void )override;

public:
	//	初期化・解放
	bool	Initialize( void )override;
	void	Release( void )override;

	//	更新・描画
	void	Update( void );
	void	Render( void );

	//	情報設定
	void	SetPlayer( int id, int type );

	//	情報取得
	Player*	GetPlayer( void );
};

#define	playerManager ( PlayerManager::GetInstance() )
