
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
	PlayerParam::PlayerParam(const Vector3& pos, Vector3& move, Vector2& axis, float angle)
	{
		this->pos = pos;
		this->move = move;
		this->axis = axis;
		this->angle = angle;
	}

	//	���ݒ�
	void	PlayerParam::Set(const Vector3& pos, Vector3& move, Vector2& axis, float angle)
	{
		this->pos = pos;
		this->move = move;
		this->axis = axis;
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
//	NET_	SEMDDATA�\����
//----------------------------------------------------------------------------------------------
	NET_CHAR_RECEIVEDATA::NET_CHAR_RECEIVEDATA(int id, const float& axisX, const float& axisY, const float& angle)
	{
		this->id = id;
		this->axisX = axisX;
		this->axisY = axisY;
		this->angle = angle;
	}

	void NET_CHAR_RECEIVEDATA::Set(int id, const float& axisX, const float& axisY, float& angle)
	{
		this->id = id;
		this->axisX = axisX;
		this->axisY = axisY;
		this->angle = angle;
	}
//----------------------------------------------------------------------------------------------
//	NET_CONTROLLE_AXIS�\����
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	NET_CONTROLLE_AXIS::NET_CONTROLLE_AXIS(int id, const float& axisX, const float& axisY)
	{
		this->id = id;
		this->axisX = axisX;
		this->axisY = axisY;
	}

	//	���ݒ�
	void	NET_CONTROLLE_AXIS::Set(int id, const float& axisX, const float& axisY)
	{
		this->id = id;
		this->axisX = axisX;
		this->axisY = axisY;
	}

//----------------------------------------------------------------------------------------------
//	NET_	CHARA_MOVE�\����
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	NET_CHARA_MOVE::NET_CHARA_MOVE(int id, const Vector3& move)
	{
		this->id = id;
		this->move = move;
	}

	//	���ݒ�
	void	NET_CHARA_MOVE::Set(int id, const Vector3& move)
	{
		this->id = id;
		this->move = move;
	}
