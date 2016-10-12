
#pragma once

//***************************************************************
//
//	GameData
//
//***************************************************************

//	include
#include	"iextreme.h"

//----------------------------------------------------------------------------
//	定数
//----------------------------------------------------------------------------

#define	PLAYER_MAX	4			//	プレイヤー人数
#define	PORT_NUM	9000		//	ポート番号

//----------------------------------------------------------------------------
//	プレイヤー情報
//----------------------------------------------------------------------------

	//	プレイヤー基本情報
	struct PlayerInfo
	{
		bool	active;
		int		type;
		char	name[17];
	};

	//	プレイヤーパラメータ
	struct PlayerParam
	{
		char	com;
		int		id;
		Vector3	pos;
		float		angle;
		int			motion;
	};

	//	チャットパラメータ
	struct ChatParam
	{
		char	msg[50];
		int		count;
	};

//----------------------------------------------------------------------------
//	データ送受信用構造体
//----------------------------------------------------------------------------

	enum COMMANDS
	{
		NO_COMMAND = -1,
		CHARA_INFO,
		CHAT,
		SIGN_UP = 10,
		SIGN_OUT,
		COMMAND_MAX
	};

	struct NET_MOVE
	{
		char	com;
		int		id;
		float	x, y, z;
	};

	//	新規参加情報
	struct NET_INFO
	{
		char	com;
		int		id;
		int		type;
		char	name[17];
	};

	//	脱退情報
	struct NET_OUT
	{
		char	com;
		int		id;
	};

	//	チャット情報
	struct NET_CHAT
	{
		char	com;
		int		id;
		char	msg[50];
	};

	//	位置情報
	struct NET_POS
	{
		char com;
		int		id;
		Vector3	pos;
	};
