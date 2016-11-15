
#pragma once

//****************************************************************
//
//	GameData
//
//****************************************************************

//	include
#include	<time.h>
#include	"iextreme.h"
#include	"SendData.h"
#include	"ReceiveData.h"

//-------------------------------------------------------------------------------------
//	ゲーム情報
//-------------------------------------------------------------------------------------

//	時間
#define	MINUTE		60
#define	HOUR		MINUTE * 60

//-------------------------------------------------------------------------------------
//	プレイヤー情報
//-------------------------------------------------------------------------------------

#define	PLAYER_MAX		4

	//	プレイヤー基本情報
	struct PlayerInfo
	{
		bool	active;
		char	name[17];
		PlayerInfo( void ){};
		PlayerInfo( bool active, const LPSTR& name );
		void Set( bool active, const LPSTR& name );
	};

	//	プレイヤーパラメータ
	struct PlayerParam
	{
		Vector3 pos;
		float	angle;
		int		motion;
		int		frame;
		PlayerParam( void ){}
		PlayerParam( const Vector3& pos, float angle, int motion, int frame );
		void Set( const Vector3& pos, float angle, int motion, int frame );
	};

	//	点数、順位情報
	struct PointInfo
	{
		//	変数
		int		point;
		int		addPoint;
	};

	//	データ構造
	enum
	{
		COMMAND,
		ID,
		DATA,
	};

//*****************************************************************************************************************************
//	ネットデータ
//*****************************************************************************************************************************
	//	コマンド
	namespace COMMANDS
	{
		enum
		{
			SIGN_UP = 10,
			SIGN_OUT
		};
	}

	//	新規参加情報
	struct SignUp
	{
		char	com = COMMANDS::SIGN_UP;
		int		id;
		char	name[17];
		SignUp( void ){}
		SignUp( int id, const LPSTR& name );
		void Set( int id, const LPSTR& name );
	};

	//	脱退情報
	struct SignOut
	{
		char  com = COMMANDS::SIGN_OUT;
		int	  id;
		SignOut( void ){}
		SignOut( int id ){ this->id = id; }
	};
