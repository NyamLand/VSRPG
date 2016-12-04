
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
	Player*	player[PLAYER_MAX];

	//	初期化・解放
	PlayerManager( void );
	~PlayerManager( void )override;

public:
	//	初期化・解放
	bool	Initialize( void );
	void	Release( void );

	//	更新・描画
	void	Update( void );
	void	Render( void );

	//	情報設定
	void	SetPlayer( int id );

	//	情報取得
	Player*&	GetPlayer( int id );
};

#define	playerManager ( PlayerManager::GetInstance() )
