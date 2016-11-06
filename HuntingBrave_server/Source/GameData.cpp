
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
		Set( active, name );
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
	PlayerParam::PlayerParam( const Vector3& pos, float moveX, float moveZ, float angle, int motion )
	{
		Set( pos, moveX, moveZ, angle, motion );
	}

	//	���ݒ�
	void	PlayerParam::Set( const Vector3& pos, float moveX, float moveZ, float angle, int motion )
	{
		this->pos = pos;
		this->moveX = moveX;
		this->moveZ = moveZ;
		this->angle = angle;
		this->motion = motion;
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
	NET_CHARA::NET_CHARA( int id, const Vector3& pos, float angle, int motion )
	{
		Set( id, pos, angle, motion );
	}

	//	���ݒ�
	void	NET_CHARA::Set( int id, const Vector3& pos, float angle, int motion )
	{
		this->id = id;
		this->pos = pos;
		this->angle = angle;
		this->motion = motion;
	}

//----------------------------------------------------------------------------------------------
//	NET_MOVE�\����
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	NET_MOVE::NET_MOVE( int id, float axisX, float axisY )
	{
		Set( id, axisX, axisY );
	}

	//	���ݒ�
	void	NET_MOVE::Set( int id, float axisX, float axisY )
	{
		this->id = id;
		this->axisX = axisX;
		this->axisY = axisY;
	}

//----------------------------------------------------------------------------------------------
//	NET_POINT�\����
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	NET_POINT::NET_POINT( void ) : point( 0 )
	{

	}
	
	//	�R���X�g���N�^
	NET_POINT::NET_POINT( int id, int point )
	{
		Set( id, point );
	}

	//	���ݒ�
	void	NET_POINT::Set( int id, int point )
	{
		this->id = id;
		this->point = point;
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
