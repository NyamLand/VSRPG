
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
				POINT_INFO,
				INPUT_INFO,
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

	//	点数情報
	struct ReceivePointData
	{
		char		com = RECEIVE_COMMAND::POINT_INFO;
		int		addPoint;
	};

	//	攻撃情報
	struct ReceiveAttackData
	{
		char			com = RECEIVE_COMMAND::ATTACK_INFO;
		char			shape;
		float			radius;
		Vector3	attackPos1;
		Vector3	attackPos2;
	};

	//	入力情報
	struct ReceiveInputData
	{
		char		com = RECEIVE_COMMAND::INPUT_INFO;
		int		keyType;
		int		keyState;
	};