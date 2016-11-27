
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
				INPUT_INFO,
				LEVEL_INFO,
				HUNT_INFO
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

	//	�U�����
	struct ReceiveAttackData
	{
		char			com = RECEIVE_COMMAND::ATTACK_INFO;
		char			shape;
		float			radius;
		Vector3	vec1;
		Vector3	vec2;
	};

	//	���͏��
	struct ReceiveInputData
	{
		char		com = RECEIVE_COMMAND::INPUT_INFO;
		int		keyType;
		int		keyState;
	};

	//	���x�����
	struct ReceiveLevelData
	{
		char	com = RECEIVE_COMMAND::LEVEL_INFO;
		char levelType;
	};

	//	�o���l���
	struct ReceiveHuntData
	{
		char com = RECEIVE_COMMAND::HUNT_INFO;
		char	enemyType;
	};