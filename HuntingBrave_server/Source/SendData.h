
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
		float			effParam;
		SendCharaData( int id, char attackParam, const Vector3& pos, float angle, float effParam, int motion, int life ) : 
			id( id ), attackParam( attackParam ), pos( pos ), angle( angle ), effParam( effParam ), motion( motion ), life( life ){}
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
