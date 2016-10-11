
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

	//	モード別関数ポインタ
	int( GameParam::*ReceiveFunction[DATA_MODE::DATA_MAX])( int client, LPSTR data );

public:
	//	初期化・解放
	GameParam( void );
	~GameParam( void );
	bool	InitializeServer( void );

	//	描画
	void	Render( void );

	//	受信・送信
	int		Receive( void );
	int		Send( int client );

	//	情報設定
	void	SetPlayer( int id, LPSTR name, int type );
	void	SetPlayerParam( int id, PlayerParam& param );
	void	SetPlayerParam( int id, Vector3& pos, float angle, int motion );

	//	各モード動作
	int		PosReceive( int client, LPSTR data );
	int		MoveReceive( int client, LPSTR data );
	int		ChatReceive( int client, LPSTR data );
	int		SignUpReceive( int client, LPSTR data );
	int		SignOutReceive( int client, LPSTR data );

	//	情報取得
	bool	GetPlayerActive( int id );
	PlayerParam& GetPlayerParam( int id );
};

