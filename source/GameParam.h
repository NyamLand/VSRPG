
#pragma once

//***************************************************************
//
//	GameParamクラス
//
//***************************************************************

//	include
#include	"GameData.h"
//#include	"winsock.h"
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

	//	受信関数ポインタ
	void( GameParam::*ReceiveFunction[DATA_MODE::DATA_MAX] )( LPSTR data );

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

	//	受信関数
	void	PosReceive( LPSTR data );
	void	MoveReceive( LPSTR data );
	void	ChatReceive( LPSTR data );
	void	SignUpReceive( LPSTR data );
	void	SignOutReceive( LPSTR data );

	//	情報設定
	void	SetPlayerInfo( int id, LPSTR name, int type );
	void	SetPlayerParam( int id, PlayerParam& param );
	void	SetPlayerParam( int id, Vector3& pos, float angle, int motion );
	
	//	情報取得
	PlayerParam GetPlayerParam( int id )const;
	PlayerInfo	GetMyInfo( int id )const;
	int		GetMyIndex( void )const;
};

extern	GameParam*	gameParam;
