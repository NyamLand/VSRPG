
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
				ATTACK_INFO,
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
		char		com = RECEIVE_COMMAND::PLAYER_INFO;
		float		axisX, axisY;
		int		frame;
	};

	//	�_�����
	struct ReceivePointData
	{
		char		com = RECEIVE_COMMAND::POINT_INFO;
		int		addPoint;
	};

	//	�U�����
	struct ReceiveAttackData
	{
		char			com = RECEIVE_COMMAND::ATTACK_INFO;
		char			shape;
		float			radius;
		Vector3	attackPos1;
		Vector3	attackPos2;
	};

	//	���͏��
	struct ReceiveInputData
	{
		char		com = RECEIVE_COMMAND::INPUT_INFO;
		int		keyType;
		int		keyState;
	};