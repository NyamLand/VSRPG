
#pragma once

//*****************************************************************************************************************************
//
//	GameParamクラス
//
//*****************************************************************************************************************************

//	include
#include	"GameData.h"
#include	"CharaInfo.h"
#include	"SocketClient.h"

//	class
class GameParam : public SocketClient
{
private:
	//	プレイヤー番号
	int		myIndex;
	bool		inputAcceptance;	//	入力受付

	PlayerInfo		playerInfo[PLAYER_MAX];
	PlayerParam	playerParam[PLAYER_MAX];
	AttackInfo	attackInfo[PLAYER_MAX];
	PointInfo		pointInfo[PLAYER_MAX];
	MatchingInfo	matchingInfo[PLAYER_MAX];

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
	void	SendPlayerInfo( void );
	void	SendPointInfo( void );
	void	SendAttackParam( void );
	void	SendMatching( void );
	void	SendInputInfo( void );

	//	受信処理
	void	ReceiveCharaInfo( const LPSTR& data );
	void	ReceivePointInfo( const LPSTR& data );
	void	ReceiveSignUpInfo( const LPSTR& data );
	void	ReceiveSignOutInfo( const LPSTR& data );
	void	ReceiveMatching( const LPSTR& data );
	void	ReceiveGameInfo( const LPSTR& data );

	//	動作関数
	void CheckInputData( int keyType );

	//	情報設定
	void	SetPlayerParam( int id, const PlayerParam& param );
	void	SetPlayerParam( int id, const Vector3& pos, float angle, int motion, int life );
	void	SetPlayerInfo( int id, char* name );
	void	SetPointInfo( int id, int addPoint );
	void	SetMatchingInfo( int id, bool isComplete );
	void	AddPoint( int id, int point );
	void	RemovePlayerInfo( int id );
	
	//	情報取得
	PlayerParam GetPlayerParam( int id )const{ return playerParam[id]; }
	PlayerInfo	GetPlayerInfo( int id )const{ return playerInfo[id]; }
	AttackInfo&	GetAttackInfo( int id ){ return	attackInfo[id]; }
	PointInfo&	GetPointInfo( int id ){ return	pointInfo[id]; }
	MatchingInfo&	GetMatchingInfo( int id ){ return	matchingInfo[id]; }
	bool		GetPlayerActive( int id ){ return playerInfo[id].active; }
	int		GetMyIndex( void ){ return myIndex; }
	char*	GetPlayerName( int id ){ return playerInfo[id].name; }
};

extern	GameParam*	gameParam;