
#pragma once

//***************************************************************
//
//	PlayerManagerクラス
//
//***************************************************************

//	include
#include	"GameData.h"
#include	"GameParam.h"
#include	"Singleton.h"
#include	"Player.h"

//	class
class PlayerManager : public Singleton<PlayerManager>
{
	friend class Singleton<PlayerManager>;

private:
	//	パラメータ
	Player*	player[PLAYER_MAX];

	GameParam*	gameParam;

	//	初期化・解放
	PlayerManager( void );
	~PlayerManager( void )override;

public:
	//	初期化・解放
	bool	Initialize( GameParam* gameParam );
	void	Release( void )override;

	//	更新・描画
	void	Update( int id );

	//	プレイヤー生成
	void	SetPlayer( int id, int type );

	//	情報取得
	Vector3	GetPos( int id );
};

#define	playerManager ( PlayerManager::GetInstance() )
