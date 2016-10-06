
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
	void	Receive( void );

	//	情報設定
	void	SetPlayerInfo( int id, LPSTR name, int type );
	void	SetPlayerParam( int id, PlayerParam& param );
	void	SetPlayerParam( int id, Vector3& pos, float angle, int motion );
	
	//	情報取得
	PlayerParam& GetPlayerParam( int id );
};
