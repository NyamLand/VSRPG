
#pragma once

//****************************************************************
//
//	GameData
//
//****************************************************************

//	include
#include	"iextreme.h"

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
		PlayerParam( void ){};
		PlayerParam( const Vector3& pos, float angle );
		void Set( const Vector3& pos, float angle );
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
	enum COMMANDS
	{
		NO_COMMAND = -1,
		CHARA_INFO,
		SIGN_UP = 10,
		SIGN_OUT
	};

	//	新規参加情報
	struct NET_IN
	{
		char	com = COMMANDS::SIGN_UP;
		int		id;
		char	name[17];
		NET_IN( void ){}
		NET_IN( int id, const LPSTR& name );
		void Set( int id, const LPSTR& name );
	};

	//	キャラデータ
	struct NET_CHARA
	{
		char com = COMMANDS::CHARA_INFO;
		int		id;
		Vector3	pos;
		NET_CHARA( void ){}
		NET_CHARA( int id, const Vector3& pos );
		void	Set( int id, const Vector3& pos );
	};
	
	//	脱退情報
	struct NET_OUT
	{
		char  com = COMMANDS::SIGN_OUT;
		int	  id;
		NET_OUT( void ){}
		NET_OUT( int id ){ this->id; }
	};