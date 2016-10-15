
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

	//	データ情報
	enum DATA_INFO
	{
		COMMAND,
		ID,
		DATA
	};
	
	//	プレイヤー基本情報
	struct PlayerInfo
	{
		bool	active;
		char	name[17];
	};

	//	プレイヤーパラメータ
	struct PlayerParam
	{
		Vector3	pos;
		float		angle;
	};

//----------------------------------------------------------------------------
//	データ送受信用構造体
//----------------------------------------------------------------------------

	//	コマンド情報
	enum COMMANDS
	{
		NO_COMMAND = -1,
		CHARA_INFO,
		SIGN_UP = 10,
		SIGN_OUT,
	};

	//	キャラ情報
	struct NET_CHARA
	{
		char	com = COMMANDS::CHARA_INFO;
		int		id;
		float	angle;
		Vector3	pos;

		//	座標設定
		void	SetPos( const Vector3& pos )
		{
			this->pos = pos;
		}

		//	座標取得
		Vector3	GetPos( void )const
		{
			return	pos;
		}

	};

	//	サインアウト
	struct NET_OUT
	{
		char	com = COMMANDS::SIGN_OUT;
		int		id;
	};

	//	サインイン
	struct NET_IN
	{
		char	com = COMMANDS::SIGN_UP;
		int		id;
		char	name[17];
	};