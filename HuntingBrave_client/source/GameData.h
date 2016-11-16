
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
//	�v���C���[���
//-------------------------------------------------------------------------------------

#define	PLAYER_MAX		4

	//	�v���C���[��{���
	struct PlayerInfo
	{
		bool	active;
		char	name[17];
		PlayerInfo( void ){};
		PlayerInfo( bool active, const LPSTR& name );
		void Set( bool active, const LPSTR& name );
	};

	//	�v���C���[�p�����[�^
	struct PlayerParam
	{
		Vector3 pos;
		float		angle; 
		int			motion;
		int			frame;
		PlayerParam( void ){};
		PlayerParam( const Vector3& pos, float angle, int motion, int frame );
		void Set( const Vector3& pos, float angle, int motion, int frame );
	};

	//	�_���A���ʏ��
	struct PointInfo
	{
		//	�ϐ�
		int		point;
		int		addPoint;
	};

	//	�f�[�^�\��
	enum 
	{
		COMMAND,
		ID,
		DATA,
	};

//-------------------------------------------------------------------------------------
//	�l�b�g�f�[�^
//-------------------------------------------------------------------------------------

	//	�R�}���h
	namespace COMMANDS
	{
		enum
		{
			SIGN_UP = 10,
			SIGN_OUT
		};
	}

	//	�V�K�Q�����
	struct SignUp
	{
		char	com = COMMANDS::SIGN_UP;
		int		id;
		char	name[17];
		SignUp( void ){}
		SignUp( int id, const LPSTR& name );
		void Set( int id, const LPSTR& name );
	};

	//	�E�ޏ��
	struct SignOut
	{
		char  com = COMMANDS::SIGN_OUT;
		int	  id;
		SignOut( void ){}
		SignOut( int id ){ this->id; }
	};

//*****************************************************************************************************************************
//	�����i�f�[�^
//*****************************************************************************************************************************

	//�����i�f�[�^
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