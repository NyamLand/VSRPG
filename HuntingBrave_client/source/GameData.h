
#pragma once

//****************************************************************
//
//	GameData
//
//****************************************************************

//	include
#include	"iextreme.h"
#include	"SendData.h"
#include	"ReceiveData.h"
#include	"CSVReader.h"
#include	"BaseEquipment.h"

//-------------------------------------------------------------------------------------
//	プレイヤー情報
//-------------------------------------------------------------------------------------

#define	PLAYER_MAX		4
#define	NAME_MAX			4

	//	プレイヤー基本情報
	struct PlayerInfo
	{
		bool	active;
		char	name[17];
		int frontTitle, backTitle;
		PlayerInfo( void ){};
		PlayerInfo( bool active, const LPSTR& name, int frontTitle, int backTitle );
		void Set( bool active, const LPSTR& name, int frontTitle, int backTitle );
	};

	//	プレイヤーパラメータ
	struct PlayerParam
	{
		Vector3 pos;
		float	angle; 
		int	motion;
		int	frame;
		int	life;
		PlayerParam( void ){};
		PlayerParam( const Vector3& pos, float angle, int motion, int frame, int life );
		void Set( const Vector3& pos, float angle, int motion, int frame, int life );
	};

	//	プレイヤーステータス
	struct PlayerStatus
	{
		//	parameter
		int power;
		int defense;
		int magicPower;
		int magicDefense;
		float speed;

		//	計算
		void	Initialize( int power, int defense, int magicPower, int magicDefense, float speed );
		void	CulcPower( int power );
		void	CulcDefense( int defense );
		void	CulcMagicPower( int power );
		void	CulcMagicDefense( int defense );
		void	DoubleSpeed( float param );
	};

	//	点数、順位情報
	struct PointInfo
	{
		//	変数
		int		point;
		int		addPoint;
	};

	//	マッチング用
	struct MatchingInfo
	{
		bool	isComplete;
	};

	//	データ構造
	enum 
	{
		COMMAND,
		ID,
		DATA,
	};

	//	レベル情報
	namespace LEVEL_INFO
	{
		enum
		{
			ATTACK,
			MAGIC_ATTACK,
			DEFENSE,
			MAGIC_DEFENSE,
			SPEED,
			GET_BOOST
		};
	}

//-------------------------------------------------------------------------------------
//	ネットデータ
//-------------------------------------------------------------------------------------

	//	コマンド
	namespace
	{
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
				CHANGE_SCENE
			};
		}
	}

	//	新規参加情報
	struct SignUp
	{
		char	com = COMMANDS::SIGN_UP;
		int		id;
		int	name[4];
		int frontTitle;
		int backTitle;
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
		SignOut( int id ){ this->id; }
	};

	//	応答
	struct Response
	{
		char com = COMMANDS::RESPONSE;
		char	responseCom;
		Response( char responseCom ) : responseCom( responseCom ){}
	};

	//マッチング情報
	struct Matching
	{
		char com = COMMANDS::MATCHING;
		int	id;
		bool	isComplete;
		Matching( void );
		Matching( int id, bool isComplete );
	};

//*****************************************************************************************************************************
//	装備品データ
//*****************************************************************************************************************************

	//装備品データ
	struct EquipmentInfo
	{
		
		string	name;
		float	atk;
		float	def;
		float	mat;
		float	mdf;
		float	hp;
		float	spe;
		float	boost;
		string	text;
	};

	struct EquipmentData
	{
		vector< EquipmentInfo > equipments;

		EquipmentData(void){};
		void Set(vector<string> tokens);

		//		EquipmentParam(void){};
		//		EquipmentParam(vector<string> token, string name);
		//		void Set(vector<string> token, string name);
	};

	static EquipmentData equipmentData;

		//fstream r("DATA\\player_data.csv", ios::in);

		//csv = new CSVReader(r);


		//while (!csv->Read(tokens))
		//{
		//	for (int i = 0; i < tokens.size(); i++)
		//	{
		//		if (tokens[0] == name)
		//		{
		//			atk = atoi(tokens[1].c_str());
		//			def = atoi(tokens[2].c_str());
		//			mat = atoi(tokens[3].c_str());
		//			mdf = atoi(tokens[4].c_str());
		//			hp = atoi(tokens[5].c_str());
		//			spe = atoi(tokens[6].c_str());
		//			text = tokens[7].c_str();
		//		}
		//	}
		//}
		//csv->Close();