
#pragma once

//***************************************************************
//
//	GameParamクラス
//
//***************************************************************

//	include
#include	"GameData.h"
#include	"CharaInfo.h"
#include	"ShapeInfo.h"
#include	"PlayerName.h"
#include	"UDPServer.h"

//	class
class GameParam : public UDPServer
{
private:
	PlayerInfo		playerInfo[PLAYER_MAX];
	PlayerParam	playerParam[PLAYER_MAX];
	PlayerStatus	playerStatus[PLAYER_MAX];
	AttackInfo	attackInfo[PLAYER_MAX];
	LifeInfo			lifeInfo[PLAYER_MAX];
	PlayerName*	playerName;

public:
	//	初期化・解放
	GameParam( void );
	~GameParam( void );
	bool InitializeServer( void );
	void	InitializePlayer( int id );
	void	InitializeGame( void );
	void	ReleaseGame( void );

	//	データ送受信
	int Receive( char scene );
	int Send( int client );

	//	送信処理
	void	SendCharaInfo( int client, int player );
	void	SendMatchingInfo( int client, int player );
	void	SendGameInfo( int client );
	void	SendKillInfo( int killer, int dead );

	//	受信処理
	int	ReceiveChara( int client, const LPSTR& data );
	int	ReceiveAttackInfo( int client, const LPSTR& data );
	int	ReceiveInput( int client, const LPSTR& data );
	int	ReceiveEnemyInfo( int client, const LPSTR& data );
	int	ReceiveLevelInfo( int client, const LPSTR& data );
	int	ReceiveItemInfo( int client, const LPSTR& data );

	//	ログイン関連受信
	int	ReceiveSignUp( int client, const LPSTR& data );
	int	ReceiveSignOut( int client, const LPSTR& data );
	int	ReceiveMatching( int client, const LPSTR& data );
	int	ReceiveResponse( int client, const LPSTR& data );

	//	応答コマンド
	int	SignUpResponse( int client );
	int	GameStartResponse( int client );

	//	情報設定
	void SetPlayer( int id, char* name );
	void SetPlayerParam( int id, const Vector3& pos, float angle, float eddParam, int motion );

	//	情報取得
	bool GetPlayerActive( int id ){ return playerInfo[id].active; }
	PlayerParam&	GetPlayerParam( int id ){ return playerParam[id]; }
	PlayerStatus&	GetPlayerStatus( int id ){ return playerStatus[id]; }
	AttackInfo&		GetAttackInfo( int id ){ return attackInfo[id]; }
	LifeInfo&			GetLifeInfo( int id ){ return	lifeInfo[id]; }
};

extern	GameParam*	gameParam;