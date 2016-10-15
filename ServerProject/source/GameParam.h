
#pragma once

//***************************************************************
//
//	GameParamクラス
//
//***************************************************************

//	include
#include	"UDPServer.h"
#include	"GameData.h"

//	class
class GameParam : public UDPServer
{
private:
	PlayerInfo	playerInfo[PLAYER_MAX];
	PlayerParam	playerParam[PLAYER_MAX];

public:
	//	初期化・解放
	GameParam( void );
	bool	InitializeServer( void );

	//	描画
	void	Render( void );

	//	受信・送信
	int		Receive( void );
	int		Send( int client );

	//	情報設定
	void	SetPlayer( int id, const LPSTR name );
	void	SetPlayerParam( int id, const PlayerParam& param );
	void	SetPlayerParam( int id, const Vector3& pos, float angle );

	//	情報取得
	bool	GetPlayerActive( int id );
	PlayerParam& GetPlayerParam( int id );
};

