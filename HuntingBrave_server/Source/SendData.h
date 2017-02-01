
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
			STATUS_INFO,
			CLASS_CHANGE_INFO,
			ENEMY_INFO,
		};
	}

	//	�X�e�[�^�X���M
	namespace SEND_STATUS
	{
		enum
		{
			ATTACK,
			DEFENSE,
			MAGIC_ATTACK,
			MAGIC_DEFENSE,
			SPEED,
			LIFE,
			ALL
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
		float		limitTimer;
		SendGameData( float timer ) : limitTimer( timer ){}
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
		float			effParam;
		SendCharaData( int id, char attackParam, const Vector3& pos, float angle, float effParam, int motion, int life ) : 
			id( id ), attackParam( attackParam ), pos( pos ), angle( angle ), effParam( effParam ), motion( motion ), life( life ){}
	};

	//	�N���X�`�F���W���
	struct SendClassChangeData
	{
		char com = SEND_COMMAND::CLASS_CHANGE_INFO;
		int		id;
		char		nextClass;
		SendClassChangeData( int id, char nextClass ) : 
			id( id ), nextClass( nextClass ){}
	};
