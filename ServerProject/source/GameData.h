
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

		Vector3	move;
	};

//-------------------------------------------------------------------------------------
//	ネット情報
//-------------------------------------------------------------------------------------

	//	動作定数
	enum DATA_MODE
	{
		MOVE,
		POS,
		CHAT,
		SIGN_UP = 10,
		SIGN_OUT = 11,
		DATA_MAX
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

	//	移動情報
	struct NET_MOVE
	{
		char  com;
		float vx;
		float vz;
	};

	//	位置情報
	struct NET_POS
	{
		char com;
		int id;
		Vector3	pos;
	};
