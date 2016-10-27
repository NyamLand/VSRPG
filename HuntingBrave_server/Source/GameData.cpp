
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
		this->active = active;
		strcpy( this->name, name );
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
	PlayerParam::PlayerParam(const Vector3& pos, Vector3& move, Vector2& axis, float angle)
	{
		this->pos = pos;
		this->move = move;
		this->axis = axis;
		this->angle = angle;
	}

	//	情報設定
	void	PlayerParam::Set(const Vector3& pos, Vector3& move, Vector2& axis, float angle)
	{
		this->pos = pos;
		this->move = move;
		this->axis = axis;
		this->angle = angle;
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
	NET_CHARA::NET_CHARA( int id, const Vector3& pos )
	{
		this->id = id;
		this->pos = pos;
	}

	//	情報設定
	void	NET_CHARA::Set( int id, const Vector3& pos )
	{
		this->id = id;
		this->pos = pos;
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
