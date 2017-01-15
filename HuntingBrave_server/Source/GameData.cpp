
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
	PlayerInfo::PlayerInfo( bool active, const LPSTR& name, char frontTitle, char backTitle )
	{
		Set( active, name, frontTitle, backTitle );
	}

	//	���ݒ�
	void	PlayerInfo::Set( bool active, const LPSTR& name, char frontTitle, char backTitle )
	{
		this->active = active;
		strcpy( this->name, name );
		this->frontTitle = frontTitle;
		this->backTitle = backTitle;
	}

//----------------------------------------------------------------------------------------------
//	PlayerParam�\����
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	PlayerParam::PlayerParam( const Vector3& pos, float angle, float cameraAngle, int motion, int frame )
	{
		move = Vector3( 0.0f, 0.0f, 0.0f );
		Set( pos,angle, cameraAngle, motion,  frame );
	}

	//	���ݒ�
	void	PlayerParam::Set( const Vector3& pos, float angle, float cameraAngle, int motion, int frame )
	{
		this->pos = pos;
		this->angle = angle;
		this->cameraAngle = cameraAngle;
		this->motion = motion;
		this->frame = frame;
	}

//----------------------------------------------------------------------------------------------
//	PlayerStatus�\����
//----------------------------------------------------------------------------------------------

	//	������
	void	PlayerStatus::Initialize( int power, int defense, int magicAttack, int magicDefense, float speed )
	{
		this->power = this->savePower = power;
		this->defense = this->saveDefense = defense;
		this->speed = this->saveSpeed = speed;
		this->magicAttack = this->saveMagicAttack = magicAttack;
		this->magicDefense = this->saveMagicDefense = magicDefense;
	}

	//	�U���͐ݒ�
	void	PlayerStatus::CulcPower( int power )
	{
		this->power += power;
		if ( this->power <= 0 )	this->power = 0;

		savePower = this->power;
	}

	//	�h��͐ݒ�
	void	PlayerStatus::CulcDefense( int defense )
	{
		this->defense += defense;
		if ( this->defense <= 0 )	this->defense = 0;

		saveDefense = this->defense;
	}

	//	���@�U���͐ݒ�
	void	PlayerStatus::CulcMagicAttack( int power )
	{
		this->magicAttack += power;
		if ( this->magicAttack <= 0 )	this->magicAttack = 0;

		saveMagicAttack = this->magicAttack;
	}

	//	���@�h��͐ݒ�
	void	PlayerStatus::CulcMagicDefense( int defense )
	{
		this->magicDefense += defense;
		if ( this->magicDefense <= 0 )	this->magicDefense = 0;

		saveMagicDefense = this->magicDefense;
	}

	//	�X�s�[�h�ݒ�
	void	PlayerStatus::DoubleSpeed( float param )
	{
		speed = param;
		if ( speed <= 0.0f )		speed = 0.0f;

		saveSpeed = speed;
	}
	
//----------------------------------------------------------------------------------------------
//	SignUp�\����
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	SignUp::SignUp( int id, int* name, char frontTitle, char backTitle )
	{
		Set( id, name, frontTitle, backTitle );
	}

	//	���ݒ�
	void	SignUp::Set( int id, int* name, char frontTitle, char backTitle )
	{
		this->id = id;
		this->frontTitle = frontTitle;
		this->backTitle = backTitle;
		for ( int i = 0; i < 4; i++ )
		{
			this->name[i] = name[i];
		}
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
