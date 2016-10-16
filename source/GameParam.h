
#pragma once

//***************************************************************
//
//	GameParamクラス
//
//***************************************************************

//	include
#include	"GameData.h"
#include	"SocketClient.h"

//	class
class GameParam : public SocketClient
{
private:
	//	自分のプレイヤー番号
	int	myIndex;

	//	Player情報
	PlayerInfo		playerInfo[PLAYER_MAX];
	PlayerParam	playerParam[PLAYER_MAX];

public:
	//	初期化・解放
	GameParam( void );
	~GameParam( void );
	bool	InitializeClient( LPSTR addr, int nPort, LPSTR name, int type );
	void	CloseClient( void );

	//	更新
	void	Update( void );

	//	送受信
	void	Send( void );
	void	Receive( void );

	//	受信処理
	void	CharaInfoReceive( const LPSTR& data );
	void	SignUpReceive( const LPSTR& data );
	void	SignOutReceive( const LPSTR& data );

	//	送信処理
	void	SendCharaData( void );

	//	情報設定
	void	SetPlayerInfo( int id, const LPSTR& name );
	void	SetPlayerParam( int id, const PlayerParam& param );
	void	SetPlayerParam( int id, const Vector3& pos, float angle );
	
	//	情報取得
	PlayerInfo	GetPlayerInfo( int id )const;
	PlayerParam GetPlayerParam( int id )const;
	PlayerInfo	GetMyInfo( int id )const;
	int		GetMyIndex( void )const;
};

extern	GameParam*	gameParam;
