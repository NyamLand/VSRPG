
#pragma once

//******************************************************************
//
//	ReceiveData
//
//******************************************************************

	//	��M�R�}���h
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
//	��M�p�\����
//----------------------------------------------------------------------------------------------

	//	�L�����N�^�[�f�[�^���M�p
	struct ReceivePlayerData
	{
		char	com = RECEIVE_COMMAND::PLAYER_INFO;
		int		id;
		float		axisX, axisY;
		int		frame;
	};

	//	�_�����
	struct ReceivePointData
	{
		char	com = RECEIVE_COMMAND::POINT_INFO;
		int		id;
		int		addPoint;
	};

	//	�ړ����
	struct ReceiveInputData
	{
		char		com = RECEIVE_COMMAND::INPUT_INFO;
		int		id;
		int		buttonType;
		int		inputType;
	};