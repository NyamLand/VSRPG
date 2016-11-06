
#include	"iextreme.h"
#include	"GameData.h"

//*****************************************************************************************************************************
//
//	GameData
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	PlayerInfo構造体
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	PlayerInfo::PlayerInfo( bool active, const LPSTR& name )
	{
		Set( active, name );
	}

	//	情報設定
	void	PlayerInfo::Set( bool active, const LPSTR& name )
	{
		this->active = active;
		strcpy( this->name, name );
	}

//----------------------------------------------------------------------------------------------
//	PlayerParam構造体
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	PlayerParam::PlayerParam( const Vector3& pos, float moveX, float moveZ, float angle, int motion )
	{
		Set( pos, moveX, moveZ, angle, motion );
	}

	//	情報設定
	void	PlayerParam::Set( const Vector3& pos, float moveX, float moveZ, float angle, int motion )
	{
		this->pos = pos;
		this->moveX = moveX;
		this->moveZ = moveZ;
		this->angle = angle;
		this->motion = motion;
	}

//----------------------------------------------------------------------------------------------
//	NET_IN	構造体
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	NET_IN::NET_IN( int id, const LPSTR& name )
	{
		this->id = id;
		strcpy( this->name, name );
	}

	//	情報設定
	void	NET_IN::Set( int id, const LPSTR& name )
	{
		this->com = com;
		this->id = id;
		strcpy( this->name, name );
	}

//----------------------------------------------------------------------------------------------
//	NET_	CHARA構造体
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	NET_CHARA::NET_CHARA( int id, const Vector3& pos, float angle, int motion )
	{
		Set( id, pos, angle, motion );
	}

	//	情報設定
	void	NET_CHARA::Set( int id, const Vector3& pos, float angle, int motion )
	{
		this->id = id;
		this->pos = pos;
		this->angle = angle;
		this->motion = motion;
	}

//----------------------------------------------------------------------------------------------
//	NET_MOVE構造体
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	NET_MOVE::NET_MOVE( int id, float axisX, float axisY )
	{
		Set( id, axisX, axisY );
	}

	//	情報設定
	void	NET_MOVE::Set( int id, float axisX, float axisY )
	{
		this->id = id;
		this->axisX = axisX;
		this->axisY = axisY;
	}

//----------------------------------------------------------------------------------------------
//	NET_POINT構造体
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	NET_POINT::NET_POINT( void ) : point( 0 )
	{

	}
	
	//	コンストラクタ
	NET_POINT::NET_POINT( int id, int point )
	{
		Set( id, point );
	}

	//	情報設定
	void	NET_POINT::Set( int id, int point )
	{
		this->id = id;
		this->point = point;
	}

//----------------------------------------------------------------------------------------------
//	NET_	SEMDDATA構造体
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
//	NET_CONTROLLE_AXIS構造体
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	NET_CONTROLLE_AXIS::NET_CONTROLLE_AXIS(int id, const float& axisX, const float& axisY)
	{
		this->id = id;
		this->axisX = axisX;
		this->axisY = axisY;
	}

	//	情報設定
	void	NET_CONTROLLE_AXIS::Set(int id, const float& axisX, const float& axisY)
	{
		this->id = id;
		this->axisX = axisX;
		this->axisY = axisY;
	}

//----------------------------------------------------------------------------------------------
//	NET_	CHARA_MOVE構造体
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	NET_CHARA_MOVE::NET_CHARA_MOVE(int id, const Vector3& move)
	{
		this->id = id;
		this->move = move;
	}

	//	情報設定
	void	NET_CHARA_MOVE::Set(int id, const Vector3& move)
	{
		this->id = id;
		this->move = move;
	}
