
#pragma once

//***************************************************************
//
//	GameDataクラス
//
//***************************************************************

//	include
#include	"iextreme.h"

//-------------------------------------------------------------------------------------
//	定数
//-------------------------------------------------------------------------------------
#define	PLAYER_MAX	4		//	プレイヤー最大数
#define	PORT_NUM	9000	//	ポート番号

//-------------------------------------------------------------------------------------
//	プレイヤーデータ
//-------------------------------------------------------------------------------------

	//	プレイヤー基本情報
	struct PlayerInfo
	{
		bool	active;
		char	name[17];
		int		type;
	};

	//	プレイヤーパラメータ
	struct PlayerParam
	{
		Vector3	pos;
		float		angle;
		int			motion;
	};

//-------------------------------------------------------------------------------------
//	ネット情報
//-------------------------------------------------------------------------------------

	//	動作定数
	enum COMMANDS
	{
		NO_COMMAND = -1,
		CHARA_INFO,
		CHAT,
		SIGN_UP = 10,
		SIGN_OUT,
		COMMAND_MAX
	};

	//	基本情報
	struct NET_INFO
	{
		char com;
		int		id;
		int		type;
		char	name[17];
	};

	//	チャット情報
	struct NET_CHAT
	{
		char  com;
		int	  id;
		char  msg[50];
	} ;

	//	退室情報
	struct NET_OUT
	{
		char	com;
		int		id;
	};

	//	位置情報
	struct NET_POS
	{
		char com;
		int id;
		Vector3	pos;
	};

	//	移動情報
	struct NET_MOVE
	{
		char	com;
		int		id;
		float	x, y, z;
	};