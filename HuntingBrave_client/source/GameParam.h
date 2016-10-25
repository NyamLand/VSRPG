
#pragma once

//*****************************************************************************************************************************
//
//	GameParamクラス
//
//*****************************************************************************************************************************

//	include
#include	"GameData.h"
#include	"SocketClient.h"

//	class
class GameParam : public SocketClient
{
private:
	int		myIndex;

	PlayerInfo	playerInfo[PLAYER_MAX];
	PlayerParam	playerParam[PLAYER_MAX];

public:
	//	初期化・解放
	GameParam( void );
	~GameParam( void );
	bool InitializeClient( char* addr, int nPort, char* name );
	void CloseClient( void );

	//	データ更新（送受信）
	void Update( void );
	void Receive( void );

	//	送信処理
	void	SendChraraInfo( void );
	
	//	受信処理
	void	ReceiveCharaInfo( const LPSTR& data );
	void	ReceiveSignUp( const LPSTR& data );
	void	ReceiveSignOut( const LPSTR& data );

	//	プレイヤーパラメータ操作
	void SetPlayerParam( int id, const PlayerParam& param );
	void SetPlayerParam( int id, const Vector3& pos );
	PlayerParam GetPlayerParam( int id ){ return playerParam[id]; }
	PlayerInfo	GetPlayerInfo( int id ){ return playerInfo[id]; }
	
	//	情報設定
	void  SetPlayerInfo( int id, char* name );
	void  RemovePlayerInfo( int id );
	
	//	情報取得
	bool  GetPlayerActive( int id ){ return playerInfo[id].active; }
	int		GetMyIndex( void ){ return myIndex; }
	char* GetPlayerName( int id ){ return playerInfo[id].name; }
};

extern	GameParam*	gameParam;