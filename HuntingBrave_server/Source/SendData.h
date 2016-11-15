
#pragma once

//******************************************************************
//
//	SendData
//
//******************************************************************

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
			SIGN_UP = 10,
			SIGN_OUT,
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
		int			id;
		Vector3		pos;
		float			angle;
		int			motion;
		SendCharaData( int id, const Vector3& pos, float angle, int motion ) : 
			id( id ), pos( pos ), angle( angle ), motion( motion ){}
	};