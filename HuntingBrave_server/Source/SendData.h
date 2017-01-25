
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
			MAGIC_ERASE,
			LEVEL_INFO,
			EXP_INFO,
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
		float			angle;

		SendMagicAppend( int id, const Vector3& pos, float angle ) :
			id( id ), pos( pos ), angle( angle ) {}
	};

	//	���@�������
	struct SendMagicErase
	{
		char	com = SEND_COMMAND::MAGIC_ERASE;
		int	index;
		SendMagicErase( int index ) : index( index ){}
	};

	//	���x�����
	struct SendLevelData
	{
		char com = SEND_COMMAND::LEVEL_INFO;
		char levelType;
		char level;

		SendLevelData( char levelType, char level ) :
			levelType( levelType ), level( level ){}
	};

	//	�o���l���
	struct SendExpData
	{
		char com = SEND_COMMAND::EXP_INFO;
		int	exp;

		SendExpData( int exp ) :	exp( exp ){}
	};

	//	�S�p�����[�^���
	struct SendAllStatusData
	{
		char com = SEND_COMMAND::STATUS_INFO;
		char statusType = SEND_STATUS::ALL;
		int attack;
		int defense;
		int magicAttack;
		int magicDefense;
		int life;
		float speed;
		SendAllStatusData( int attack, int defense, int magicAttack, int magicDefense, int life, float speed ) :
			attack( attack ), defense( defense ), 
			magicAttack( magicAttack ), magicDefense( magicDefense ), life( life ), speed( speed ) {}
	};

	//	�e�p�����[�^���
	struct SendStatusData
	{
		char com = SEND_COMMAND::STATUS_INFO;
		char statusType;
		float status;
		SendStatusData( char statusType, float status ) : 
			statusType( statusType ), status( status ){}
		SendStatusData( void ){}
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
