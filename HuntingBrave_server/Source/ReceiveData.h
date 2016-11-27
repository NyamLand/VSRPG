
#pragma once

//******************************************************************
//
//	ReceiveData
//
//******************************************************************

	//	受信コマンド
	namespace
	{
		namespace RECEIVE_COMMAND
		{
			enum
			{
				NO_COMMAND = -1,
				PLAYER_INFO = 1,
				ATTACK_INFO,
				INPUT_INFO,
				LEVEL_INFO,
				HUNT_INFO
			};
		}
	}

//----------------------------------------------------------------------------------------------
//	受信用構造体
//----------------------------------------------------------------------------------------------

	//	キャラクターデータ送信用
	struct ReceivePlayerData
	{
		char		com = RECEIVE_COMMAND::PLAYER_INFO;
		float		axisX, axisY;
		int		frame;
	};

	//	攻撃情報
	struct ReceiveAttackData
	{
		char			com = RECEIVE_COMMAND::ATTACK_INFO;
		char			shape;
		float			radius;
		Vector3	vec1;
		Vector3	vec2;
	};

	//	入力情報
	struct ReceiveInputData
	{
		char		com = RECEIVE_COMMAND::INPUT_INFO;
		int		keyType;
		int		keyState;
	};

	//	レベル情報
	struct ReceiveLevelData
	{
		char	com = RECEIVE_COMMAND::LEVEL_INFO;
		char levelType;
	};

	//	経験値情報
	struct ReceiveHuntData
	{
		char com = RECEIVE_COMMAND::HUNT_INFO;
		char	enemyType;
	};