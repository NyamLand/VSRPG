
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
		char	com = RECEIVE_COMMAND::PLAYER_INFO;
		float		axisX, axisY;
		char		button;
		char		inputType;
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
		float			radius;
		Vector3	attackPos1;
		Vector3	attackPos2;
	};