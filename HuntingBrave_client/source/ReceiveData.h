
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
			MAGIC_INFO,
			STATUS_INFO,
			CLASS_CHANGE_INFO,
			ENEMY_INFO,
			COMMAND_MAX
		};
	}

	//	�Q�[�����
	struct ReceiveGameData
	{
		char	com = RECEIVE_COMMAND::GAME_INFO;
		float		limitTimer;
	};

	//	�L�����N�^�[���
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

	//	�N���X�`�F���W���
	struct ReceiveClassChangeData
	{
		char com = RECEIVE_COMMAND::CLASS_CHANGE_INFO;
		int id;
		char nextClass;
	};
