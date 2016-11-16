
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
	PlayerParam::PlayerParam( const Vector3& pos, float angle, int motion, int frame, int life )
	{
		Set( pos,angle, motion, frame, life );
	}

	//	���ݒ�
	void	PlayerParam::Set( const Vector3& pos, float angle, int motion, int frame, int life )
	{
		this->pos = pos;
		this->angle = angle;
		this->motion = motion;
		this->frame = frame;
		this->life = life;
	}

//----------------------------------------------------------------------------------------------
//	SignUp�\����
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	SignUp::SignUp( int id, const LPSTR& name )
	{
		this->id = id;
		strcpy( this->name, name );
	}

	//	���ݒ�
	void	SignUp::Set( int id, const LPSTR& name )
	{
		this->com = com;
		this->id = id;
		strcpy( this->name, name );
	}
