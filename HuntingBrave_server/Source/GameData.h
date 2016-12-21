
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

//	シーン
namespace SCENE
{
	enum
	{
		TITLE,
		MATCHING,
		MAIN,
		RESULT,
		MAX
	};

}

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
		Vector3	pos;
		float			angle;
		int			motion;
		int			frame;
		PlayerParam( void ){}
		PlayerParam( const Vector3& pos, float angle, int motion, int frame );
		void Set( const Vector3& pos, float angle, int motion, int frame );
	};

	//	プレイヤーステータス
	struct PlayerStatus
	{
		//	parameter
		int	power;
		int	defense;
		float	speed;
		float initSpeed;

		//	計算
		void	Initialize( int power, int defense, float speed );
		void	CulcPower( int id, int power );
		void	CulcDefense( int id, int defense );
		void	DoubleSpeed( int id, float param );
	};

	//	点数、順位情報
	struct PointInfo
	{
		//	変数
		int		point;
		int		addPoint;
	};

	//	マッチング情報
	struct MatchingInfo
	{
		bool		isComplete;
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
	namespace
	{
		//	サインコマンド
		namespace COMMANDS
		{
			enum
			{
				MATCHING = 10,
				SIGN_UP,
				SIGN_OUT,
				RESPONSE
			};
		}

		//	返答コマンド
		namespace RESPONSE_COMMAND
		{
			enum
			{
				SIGN_UP,
				GAME_START,
				CHANGE_SCENE,
			};
		}
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

	//	応答
	struct Response
	{
		char com = COMMANDS::RESPONSE;
		char	responseCom;
		Response( char responseCom ) : responseCom( responseCom ){}
	};

	//	マッチング情報
	struct Matching
	{
		char com = COMMANDS::MATCHING;
		int	id;
		bool	isComplete;
		Matching( void );
		Matching( int id, int mode );
		void	Set( int id, int mode );
	};
