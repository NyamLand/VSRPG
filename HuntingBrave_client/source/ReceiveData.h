
#pragma once

//****************************************************************
//
//	ReceiveData
//
//****************************************************************

//----------------------------------------------------------------------------------------------
//	受信用構造体
//----------------------------------------------------------------------------------------------

	//	コマンド
	namespace RECEIVE_COMMAND
	{
		enum
		{
			NO_COMMAND = -1,
			GAME_INFO,
			POINT_INFO,
			CHARA_INFO,
			MAGIC_INFO,
			MAGIC_APPEND,
			MAGIC_ERASE,
			LEVEL_INFO,
			EXP_INFO,
			STATUS_INFO,
			CLASS_CHANGE_INFO,
			COMMAND_MAX
		};
	}

	//	ステータス送信
	namespace RECEIVE_STATUS
	{
		enum
		{
			ATTACK,
			DEFENSE,
			MAGIC_ATTACK,
			MAGIC_DEFENSE,
			SPEED,
			LIFE,
			ALL
		};
	}

	//	ゲーム情報
	struct ReceiveGameData
	{
		char	com = RECEIVE_COMMAND::GAME_INFO;
		float		limitTimer;
	};

	//	点数情報
	struct ReceivePointData
	{
		char	com = RECEIVE_COMMAND::POINT_INFO;
		int		id;
		int		point;
	};

	//	キャラクター情報
	struct ReceiveCharaData
	{
		char	com = RECEIVE_COMMAND::CHARA_INFO;
		char			attackParam;
		int			id;
		int			life;
		int			motion;
		Vector3	pos;
		float			angle;
	};

	//	魔法攻撃情報
	struct ReceiveMagicData
	{
		char	com = RECEIVE_COMMAND::MAGIC_INFO;
		int	index;
		Vector3	pos;
	};

	//	魔法発動情報
	struct ReceiveMagicAppend
	{
		char	com = RECEIVE_COMMAND::MAGIC_APPEND;
		int	id;
		Vector3	pos;
		float			angle;
	};

	//	魔法消去情報
	struct ReceiveMagicErase
	{
		char	com = RECEIVE_COMMAND::MAGIC_ERASE;
		int	index;
		ReceiveMagicErase( int index ) : index( index ){}
	};

	//	レベル情報
	struct ReceiveLevelData
	{
		char com = RECEIVE_COMMAND::LEVEL_INFO;
		char levelType;
		char level;
	};

	//	経験値情報
	struct ReceiveExpData
	{
		char com = RECEIVE_COMMAND::EXP_INFO;
		int exp;
	};
	
	//	全ステータス情報
	struct ReceiveAllStatusData
	{
		char com = RECEIVE_COMMAND::STATUS_INFO;
		char statusType;
		int attack;
		int defense;
		int magicAttack;
		int magicDefense;
		int life;
		float speed;
	};

	//	各ステータス情報
	struct ReceiveStatusData
	{
		char		com = RECEIVE_COMMAND::STATUS_INFO;
		char		statusType;
		float		status;
	};

	//	クラスチェンジ情報
	struct ReceiveClassChangeData
	{
		char com = RECEIVE_COMMAND::CLASS_CHANGE_INFO;
		int id;
		char nextClass;
	};
