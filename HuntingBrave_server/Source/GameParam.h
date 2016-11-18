
#pragma once

//***************************************************************
//
//	GameParam�N���X
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
	PointInfo		pointInfo[PLAYER_MAX];
	MatchingInfo		matchingInfo[PLAYER_MAX];

public:
	//	�������E���
	GameParam( void );
	bool InitializeServer( void );

	//	�f�[�^����M
	int Receive( void );
	int Send( int client );

	//	���M����
	void	SendCharaInfo( int client, int player );
	void	SendPointInfo(int client, int player);
	void	SendMatchingInfo(int client, int player);
	void	SendGameInfo( int client );

	//	��M����
	void	ReceiveChara( int client, const LPSTR& data );
	void	ReceivePoint(int client, const LPSTR& data);
	void	ReceiveMatching(int client, const LPSTR& data);
	void	ReceiveCharaDATA(int client, const LPSTR& data);
	void	ReceiveControllerAxis(int client, const LPSTR& data);
	void	ReceiveCharaMove(int client, const LPSTR& data);
	void	ReceiveSignUp( int client, const LPSTR& data );
	void	ReceiveSignOut( int client, const LPSTR& data );

	//	���ݒ�
	void SetPlayerParam( int id, const PlayerParam& param );
	void SetPointInfo( int id, const PointInfo& pointInfo );
	void SetPlayer( int id, char* name );
	void ReleasePlayer( int id );
	void SetPlayerParam( int id, const Vector3& pos, float angle, int motion );

	//	���擾
	bool GetPlayerActive( int id ){ return playerInfo[id].active; }
	PlayerParam& GetPlayerParam( int id ){ return playerParam[id]; }
	PointInfo&		GetPointInfo( int id ){ return pointInfo[id]; }

};
