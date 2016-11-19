
#pragma once

//****************************************************************
//
//	ReceiveData
//
//****************************************************************

//----------------------------------------------------------------------------------------------
//	��M�p�\����
//----------------------------------------------------------------------------------------------

	//	�R�}���h
	namespace RECEIVE_COMMAND
	{
		enum
		{
			NO_COMMAND = -1,
			GAME_INFO,
			POINT_INFO,
			CHARA_INFO,
			SIGN_UP = 10,
			SIGN_OUT,
		};
	}

	//	�Q�[�����
	struct ReceiveGameData
	{
		char	com = RECEIVE_COMMAND::GAME_INFO;
		int		limitTimer;
	};

	//	�_�����
	struct ReceivePointData
	{
		char	com = RECEIVE_COMMAND::POINT_INFO;
		int		id;
		int		point;
	};

	//	�L�����N�^�[���
	struct ReceiveCharaData
	{
		char	com = RECEIVE_COMMAND::CHARA_INFO;
		char	attackParam;
		int			id;
		int			life;
		int			motion;
		Vector3	pos;
		float			angle;
	};