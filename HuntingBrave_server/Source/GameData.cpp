
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
	PlayerParam::PlayerParam( const Vector3& pos, float angle, int motion, int frame )
	{
		Set( pos,angle, motion, frame );
	}

	//	���ݒ�
	void	PlayerParam::Set( const Vector3& pos, float angle, int motion, int frame )
	{
		this->pos = pos;
		this->angle = angle;
		this->motion = motion;
		this->frame = frame;
	}

//----------------------------------------------------------------------------------------------
//	PlayerStatus�\����
//----------------------------------------------------------------------------------------------

	//	������
	void	PlayerStatus::Initialize( int power, int defense, int magicAttack, int magicDefense, float speed )
	{
		this->power = power;
		this->defense = defense;
		this->speed = speed;
		this->magicAttack = magicAttack;
		this->magicDefense = magicDefense;
	}

	//	�U���͐ݒ�
	void	PlayerStatus::CulcPower( int power )
	{
		this->power += power;
		if ( this->power <= 0 )	this->power = 0;
	}

	//	�h��͐ݒ�
	void	PlayerStatus::CulcDefense( int defense )
	{
		this->defense += defense;
		if ( this->defense <= 0 )	this->defense = 0;
	}

	//	���@�U���͐ݒ�
	void	PlayerStatus::CulcMagicAttack( int power )
	{
		this->magicAttack += power;
		if ( this->magicAttack <= 0 )	this->magicAttack = 0;
	}

	//	���@�h��͐ݒ�
	void	PlayerStatus::CulcMagicDefense( int defense )
	{
		this->magicDefense += defense;
		if ( this->magicDefense <= 0 )	this->magicDefense = 0;
	}

	//	�X�s�[�h�ݒ�
	void	PlayerStatus::DoubleSpeed( float param )
	{
		speed = param;
		if ( speed <= 0.0f )		speed = 0.0f;
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

//----------------------------------------------------------------------------------------------
//	Matching�\����
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	Matching::Matching( void ) : id( 0 )
	{

	}
	
	//	�R���X�g���N�^
	Matching::Matching( int id, int mode )
	{
		Set( id, mode );
	}

	//	���ݒ�
	void Matching::Set( int id, int mode )
	{
		this->id = id;
		this->isComplete = mode;
	}
