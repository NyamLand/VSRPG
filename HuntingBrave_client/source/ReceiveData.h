
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
			MAGIC_ERASE
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

	//	���@�U�����
	struct ReceiveMagicData
	{
		char	com = RECEIVE_COMMAND::MAGIC_INFO;
		int	index;
		Vector3	pos;
		ReceiveMagicData( int index, const Vector3& pos ) :
			index( index ), pos( pos ) {}
	};

	//	���@�������
	struct ReceiveMagicAppend
	{
		char	com = RECEIVE_COMMAND::MAGIC_APPEND;
		int	id;
		Vector3	pos;

		ReceiveMagicAppend( int id, const Vector3& pos ) :
			id( id ), pos( pos ) {}
	};

	//	���@�������
	struct ReceiveMagicErase
	{
		char	com = RECEIVE_COMMAND::MAGIC_ERASE;
		int	index;
		ReceiveMagicErase( int index ) : index( index ){}
	};