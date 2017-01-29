
#pragma once

//***************************************************************
//
//	PlayerManagerクラス
//
//***************************************************************

//	include
#include	"Singleton.h"
#include	"Suppin.h"
#include	"Fighter.h"
#include	"Magician.h"
#include	"Player.h"

//	class
class PlayerManager : public Singleton<PlayerManager>
{
	friend class Singleton<PlayerManager>;

private:
	Player*		player[PLAYER_MAX];

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
	void	RenderHp( void );

	//	動作関数
	void	ClassChange( int id, char nextClass );
	void	Receive( const LPSTR& data );
	
	//	情報設定
	void	SetPlayer( int id );

	//	情報取得
	Player*&	GetPlayer( int id );
};

#define	playerManager ( PlayerManager::GetInstance() )
