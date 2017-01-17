
#pragma once

//*****************************************************************************************************************************
//
//	GameParam�N���X
//
//*****************************************************************************************************************************

//	include
#include	"GameData.h"
#include	"CharaInfo.h"
#include	"SocketClient.h"
#include	"PlayerName.h"

//	class
class GameParam : public SocketClient
{
private:
	//	�v���C���[�ԍ�
	int		myIndex;
	bool		inputAcceptance;	//	���͎�t

	PlayerInfo		playerInfo[PLAYER_MAX];
	PlayerParam	playerParam[PLAYER_MAX];
	PlayerStatus	playerStatus;
	AttackInfo	attackInfo[PLAYER_MAX];
	PointInfo		pointInfo[PLAYER_MAX];
	MatchingInfo	matchingInfo[PLAYER_MAX];
	PlayerName*	playerName;

public:
	//	�������E���
	GameParam( void );
	~GameParam( void );
	bool	Initialize( void );
	bool InitializeClient( char* addr, int nPort, int* name );
	void CloseClient( void );

	//	�f�[�^�X�V�i����M�j
	void Update( void );
	void Receive( void );

	//	���M����
	void	SendPlayerInfo( void );
	void	SendAttackParam( void );
	void	SendMatching( void );
	void	SendInputInfo( void );
	void	SendHuntInfo( char enemyType );
	void	SendSignOut( void );
	void	SendResponseInfo( char com );

	//	��M����
	void	ReceiveCharaInfo( const LPSTR& data );
	void	ReceivePointInfo( const LPSTR& data );
	void	ReceiveGameInfo( const LPSTR& data );
	void	ReceiveMagicInfo( const LPSTR& data );
	void	ReceiveMagicAppendInfo( const LPSTR& data );
	void	ReceiveMagicEraseInfo( const LPSTR& data );
	void	ReceiveLevelInfo( const LPSTR& data );
	void	ReceiveExpInfo( const LPSTR& data );
	void	ReceiveClassChangeInfo( const LPSTR& data );
	void	ReceiveStatusInfo( const LPSTR& data );

	//	���O�C������M
	void	ReceiveSignUpInfo( const LPSTR& data );
	void	ReceiveSignOutInfo( const LPSTR& data );
	void	ReceiveMatching( const LPSTR& data );
	void	ReceiveResponse( const LPSTR& data );
	
	//	����֐�
	void CheckInputData( char keyType );

	//	���ݒ�
	void	SetPlayerParam( int id, const PlayerParam& param );
	void	SetPlayerParam( int id, const Vector3& pos, float angle, int motion, int life );
	void	SetPlayerInfo( int id, char* name, char frontTItle, char backTitle );
	void	SetPointInfo( int id, int addPoint );
	void	SetMatchingInfo( int id, bool isComplete );
	void	AddPoint( int id, int point );
	void	RemovePlayerInfo( int id );
	
	//	���擾
	PlayerParam GetPlayerParam( int id )const{ return playerParam[id]; }
	PlayerInfo	GetPlayerInfo( int id )const{ return playerInfo[id]; }
	PlayerStatus&	GetPlayerStatus( void ){ return playerStatus; }
	AttackInfo&	GetAttackInfo( int id ){ return	attackInfo[id]; }
	PointInfo&	GetPointInfo( int id ){ return	pointInfo[id]; }
	MatchingInfo&	GetMatchingInfo( int id ){ return	matchingInfo[id]; }
	bool		GetPlayerActive( int id ){ return playerInfo[id].active; }
	int		GetMyIndex( void ){ return myIndex; }
	PlayerName*&	GetPlayerName( void ){ return playerName; }
};

extern	GameParam*	gameParam;