
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
		int		id;
		float		axisX, axisY;
		int		frame;
	};

	//	点数情報
	struct ReceivePointData
	{
		char	com = RECEIVE_COMMAND::POINT_INFO;
		int		id;
		int		addPoint;
	};

	//	移動情報
	struct ReceiveInputData
	{
		char		com = RECEIVE_COMMAND::INPUT_INFO;
		int		id;
		int		buttonType;
		int		inputType;
	};