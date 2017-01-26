
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
				ENEMY_INFO,
				ITEM_INFO,
				COMMAND_MAX
			};
		}
	}

	//	敵情報受信コマンド
	namespace 
	{
		namespace RECEIVE_ENEMY_COMMAND
		{
			enum 
			{
				NO_COMMAND = -1,
				BIG_ENEMY_HUNT = 1,
				SMALL_ENEMY_HUNT,
				PLAYER_HIT,
				CLIENT_OK,
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
		float		cameraAngle;
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
		char		key;
		char		keyState;
	};

	//	レベル情報
	struct ReceiveLevelData
	{
		char	com = RECEIVE_COMMAND::LEVEL_INFO;
		char levelType;
	};
