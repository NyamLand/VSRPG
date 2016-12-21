
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
			MAGIC_APPEND,
			MAGIC_ERASE,
			LEVEL_INFO,
			EXP_INFO,
			CLASS_CHANGE_INFO,
			COMMAND_MAX
		};
	}

	//	�Q�[�����
	struct ReceiveGameData
	{
		char	com = RECEIVE_COMMAND::GAME_INFO;
		float		limitTimer;
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
		char			attackParam;
		int			id;
		int			life;
		int			motion;
		Vector3	pos;
		float			angle;
	};

	//	���@�U�����
	struct ReceiveMagicData
	{
		char	com = RECEIVE_COMMAND::MAGIC_INFO;
		int	index;
		Vector3	pos;
	};

	//	���@�������
	struct ReceiveMagicAppend
	{
		char	com = RECEIVE_COMMAND::MAGIC_APPEND;
		int	id;
		Vector3	pos;
		float			angle;
	};

	//	���@�������
	struct ReceiveMagicErase
	{
		char	com = RECEIVE_COMMAND::MAGIC_ERASE;
		int	index;
		ReceiveMagicErase( int index ) : index( index ){}
	};

	//	���x�����
	struct ReceiveLevelData
	{
		char com = RECEIVE_COMMAND::LEVEL_INFO;
		char levelType;
		char level;
	};

	//	�o���l���
	struct ReceiveExpData
	{
		char com = RECEIVE_COMMAND::EXP_INFO;
		int exp;
	};

	//	�N���X�`�F���W���
	struct ReceiveClassChangeData
	{
		char com = RECEIVE_COMMAND::CLASS_CHANGE_INFO;
		int id;
		char nextClass;
	};
