
#pragma once

//**************************************************************************
//
//	SendData
//
//**************************************************************************

	//	���M�R�}���h
	namespace
{
	//	�R�}���h
	namespace SEND_COMMAND
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
}

//----------------------------------------------------------------------------------------------
//	���M�p�\����
//----------------------------------------------------------------------------------------------

	//	�Q�[�����
	struct SendGameData
	{
		char		com = SEND_COMMAND::GAME_INFO;
		int		limitTimer;
		SendGameData( int timer ) : limitTimer( timer ){}
	};

	//	�_�����
	struct SendPointData
	{
		char	com = SEND_COMMAND::POINT_INFO;
		int		id;
		int		point;
		SendPointData( int id, int point ) : id( id ), point( point ){}
	};

	//	�L�����N�^�[���
	struct SendCharaData
	{
		char com = SEND_COMMAND::CHARA_INFO;
		char	attackParam;
		int			id;
		int			life;
		int			motion;
		Vector3	pos;
		float			angle;
		SendCharaData( int id, char attackParam, const Vector3& pos, float angle, int motion, int life ) : 
			id( id ), attackParam( attackParam ), pos( pos ), angle( angle ), motion( motion ), life( life ){}
	};

	//	���@�U�����
	struct SendMagicData
	{
		char	com = SEND_COMMAND::MAGIC_INFO;
		int	index;
		Vector3	pos;
		SendMagicData( int index, const Vector3& pos ) :
			index( index ), pos( pos ) {}
	};

	//	���@�������
	struct SendMagicAppend
	{
		char	com = SEND_COMMAND::MAGIC_APPEND;
		int	id;
		Vector3	pos;

		SendMagicAppend( int id, const Vector3& pos ) :
			id( id ), pos( pos ) {}
	};

	//	���@�������
	struct SendMagicErase
	{
		char	com = SEND_COMMAND::MAGIC_ERASE;
		int	index;
		SendMagicErase( int index ) : index( index ){}
	};