
#include	"iextreme.h"
#include	"GameData.h"

//*****************************************************************************************************************************
//
//	GameData
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	PlayerInfo�\����
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	PlayerInfo::PlayerInfo( bool active, const LPSTR& name )
	{
		this->active = active;
		strcpy( this->name, name );
	}

	//	���ݒ�
	void	PlayerInfo::Set( bool active, const LPSTR& name )
	{
		this->active = active;
		strcpy( this->name, name );
	}

//----------------------------------------------------------------------------------------------
//	PlayerParam�\����
//----------------------------------------------------------------------------------------------
	
	//	�R���X�g���N�^
	PlayerParam::PlayerParam( const Vector3& pos, float angle )
	{
		this->pos = pos;
		this->angle = angle;
	}

	//	���ݒ�
	void	PlayerParam::Set( const Vector3& pos, float angle )
	{
		this->pos = pos;
		this->angle = angle;
	}

//----------------------------------------------------------------------------------------------
//	NET_IN	�\����
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	NET_IN::NET_IN( int id, const LPSTR& name )
	{
		this->id = id;
		strcpy( this->name, name );
	}

	//	���ݒ�
	void	NET_IN::Set( int id, const LPSTR& name )
	{
		this->com = com;
		this->id = id;
		strcpy( this->name, name );
	}

//----------------------------------------------------------------------------------------------
//	NET_	CHARA�\����
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	NET_CHARA::NET_CHARA( int id, const Vector3& pos )
	{
		this->id = id;
		this->pos = pos;
	}

	//	���ݒ�
	void	NET_CHARA::Set( int id, const Vector3& pos )
	{
		this->id = id;
		this->pos = pos;
	}


//----------------------------------------------------------------------------------------------
//	EquipmentParam�\����
//----------------------------------------------------------------------------------------------


	void	EquipmentData::Set(vector<string> tokens)
	{
		EquipmentInfo temp;

		temp.name = tokens[0].c_str();
		temp.atk = atoi(tokens[1].c_str());
		temp.def = atoi(tokens[2].c_str());
		temp.mat = atoi(tokens[3].c_str());
		temp.mdf = atoi(tokens[4].c_str());
		temp.hp = atoi(tokens[5].c_str());
		temp.spe = atoi(tokens[6].c_str());
		temp.text = tokens[7].c_str();

		equipments.push_back(temp);
	}