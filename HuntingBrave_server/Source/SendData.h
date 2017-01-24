
#pragma once

//**************************************************************************
//
//	SendData
//
//**************************************************************************

	//	送信コマンド
	namespace
{
	//	コマンド
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

	//	ステータス送信
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
//	送信用構造体
//----------------------------------------------------------------------------------------------

	//	ゲーム情報
	struct SendGameData
	{
		char		com = SEND_COMMAND::GAME_INFO;
		float		limitTimer;
		SendGameData( float timer ) : limitTimer( timer ){}
	};

	//	点数情報
	struct SendPointData
	{
		char	com = SEND_COMMAND::POINT_INFO;
		int		id;
		int		point;
		SendPointData( int id, int point ) : id( id ), point( point ){}
	};

	//	キャラクター情報
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

	//	魔法攻撃情報
	struct SendMagicData
	{
		char	com = SEND_COMMAND::MAGIC_INFO;
		int	index;
		Vector3	pos;
		SendMagicData( int index, const Vector3& pos ) :
			index( index ), pos( pos ) {}
	};

	//	魔法発動情報
	struct SendMagicAppend
	{
		char	com = SEND_COMMAND::MAGIC_APPEND;
		int	id;
		Vector3	pos;
		float			angle;

		SendMagicAppend( int id, const Vector3& pos, float angle ) :
			id( id ), pos( pos ), angle( angle ) {}
	};

	//	魔法消去情報
	struct SendMagicErase
	{
		char	com = SEND_COMMAND::MAGIC_ERASE;
		int	index;
		SendMagicErase( int index ) : index( index ){}
	};

	//	レベル情報
	struct SendLevelData
	{
		char com = SEND_COMMAND::LEVEL_INFO;
		char levelType;
		char level;

		SendLevelData( char levelType, char level ) :
			levelType( levelType ), level( level ){}
	};

	//	経験値情報
	struct SendExpData
	{
		char com = SEND_COMMAND::EXP_INFO;
		int	exp;

		SendExpData( int exp ) :	exp( exp ){}
	};

	//	全パラメータ情報
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

	//	各パラメータ情報
	struct SendStatusData
	{
		char com = SEND_COMMAND::STATUS_INFO;
		char statusType;
		float status;
		SendStatusData( char statusType, float status ) : 
			statusType( statusType ), status( status ){}
		SendStatusData( void ){}
	};

	//	クラスチェンジ情報
	struct SendClassChangeData
	{
		char com = SEND_COMMAND::CLASS_CHANGE_INFO;
		int		id;
		char		nextClass;
		SendClassChangeData( int id, char nextClass ) : 
			id( id ), nextClass( nextClass ){}
	};
