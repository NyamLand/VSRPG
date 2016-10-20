
#pragma once

//***************************************************************
//
//	GameParamクラス
//
//***************************************************************

//	include
#include	"GameData.h"
#include	"UDPServer.h"

//	class
class GameParam : public UDPServer
{
private:
	PlayerInfo	playerInfo[PLAYER_MAX];
	PlayerParam	playerParam[PLAYER_MAX];

public:
	//	初期化・解放
	GameParam( void );
	bool InitializeServer( void );

	//	データ送受信
	int Receive( void );
	int Send( int client );

	//	送信処理
	void	SendCharaInfo( int client );

	//	受信処理
	void	ReceiveChara( int client, const LPSTR& data );
	void	ReceiveSignUp( int client, const LPSTR& data );
	void	ReceiveSignOut( int client, const LPSTR& data );

	//	情報設定
	void SetPlayerParam( int id, PlayerParam& param );
	void SetPlayer( int id, char* name );
	void SetPlayerParam( int id, Vector3& pos, float angle );
	PlayerParam& getPlayerParam( int id ){ return playerParam[id]; }

	//	情報取得
	bool GetPlayerActive( int id ){ return playerInfo[id].active; }
};
