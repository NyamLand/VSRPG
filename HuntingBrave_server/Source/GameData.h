
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
#define	GRAVITY	-0.1f

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
		int frontTitle;
		int backTitle;
		PlayerInfo( void ){};
		PlayerInfo( bool active, const LPSTR& name, int frontTitle, int backTitle );
		void Set( bool active, const LPSTR& name, int frontTitle, int backTitle );
	};

	//	プレイヤーパラメータ
	struct PlayerParam
	{
		Vector3	pos;
		Vector3	move;
		char			charType;
		float			angle;
		float			cameraAngle;
		float			effParam;
		int			motion;
		int			frame;
		PlayerParam( void ){}
		PlayerParam( const Vector3& pos, float angle, float cameraAngle, float effParam, int motion, int frame );
		void Set( const Vector3& pos, float angle, float cameraAngle, float effParam, int motion, int frame );
	};

	//	プレイヤーステータス
	struct PlayerStatus
	{
		//	parameter
		int	power, savePower;
		int	defense, saveDefense;
		int	magicAttack, saveMagicAttack;
		int	magicDefense, saveMagicDefense;
		int	maxLife;
		float	speed, saveSpeed;

		//	計算
		void	Initialize( int power, int defense, int magicAttack, int magicDefense, int maxLife, float speed );
		void	CulcPower( int power );
		void	CulcDefense( int defense );
		void	CulcMagicAttack( int power );
		void	CulcMagicDefense( int defense );
		void	CulcMaxLife( int maxLife );
		void	DoubleSpeed( float param );
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
				MATCHING = 12,
				SIGN_UP,
				SIGN_OUT,
				RESPONSE,
				DEBUG
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
				KILL_INFO,
				HIT_SE_TYPE
			};
		}
	}

	//	新規参加情報
	struct SignUp
	{
		char	com = COMMANDS::SIGN_UP;
		int		id;
		int		name[4];
		int		frontTitle;
		int		backTitle;
		SignUp( void ){}
		SignUp( int id, int* name, int frontTitle, int backTitle );
		void Set( int id, int* name, int frontTitle, int backTitle );
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
		Matching( int id, bool mode );
		void	Set( int id, bool mode );
	};
