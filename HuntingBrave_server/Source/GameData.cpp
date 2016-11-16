
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
	PlayerParam::PlayerParam( const Vector3& pos, float angle, int motion, int frame, int life )
	{
		Set( pos,angle, motion, frame, life );
	}

	//	情報設定
	void	PlayerParam::Set( const Vector3& pos, float angle, int motion, int frame, int life )
	{
		this->pos = pos;
		this->angle = angle;
		this->motion = motion;
		this->frame = frame;
		this->life = life;
	}

//----------------------------------------------------------------------------------------------
//	SignUp構造体
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	SignUp::SignUp( int id, const LPSTR& name )
	{
		this->id = id;
		strcpy( this->name, name );
	}

	//	情報設定
	void	SignUp::Set( int id, const LPSTR& name )
	{
		this->com = com;
		this->id = id;
		strcpy( this->name, name );
	}
