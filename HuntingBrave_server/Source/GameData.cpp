
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
	PlayerParam::PlayerParam( const Vector3& pos, float angle, int motion, int frame )
	{
		Set( pos,angle, motion, frame );
	}

	//	情報設定
	void	PlayerParam::Set( const Vector3& pos, float angle, int motion, int frame )
	{
		this->pos = pos;
		this->angle = angle;
		this->motion = motion;
		this->frame = frame;
	}

//----------------------------------------------------------------------------------------------
//	PlayerStatus構造体
//----------------------------------------------------------------------------------------------

	//	初期化
	void	PlayerStatus::Initialize( int power, int defense, int magicAttack, int magicDefense, float speed )
	{
		this->power = power;
		this->defense = defense;
		this->speed = speed;
		this->magicAttack = magicAttack;
		this->magicDefense = magicDefense;
	}

	//	攻撃力設定
	void	PlayerStatus::CulcPower( int power )
	{
		this->power += power;
		if ( this->power <= 0 )	this->power = 0;
	}

	//	防御力設定
	void	PlayerStatus::CulcDefense( int defense )
	{
		this->defense += defense;
		if ( this->defense <= 0 )	this->defense = 0;
	}

	//	魔法攻撃力設定
	void	PlayerStatus::CulcMagicAttack( int power )
	{
		this->magicAttack += power;
		if ( this->magicAttack <= 0 )	this->magicAttack = 0;
	}

	//	魔法防御力設定
	void	PlayerStatus::CulcMagicDefense( int defense )
	{
		this->magicDefense += defense;
		if ( this->magicDefense <= 0 )	this->magicDefense = 0;
	}

	//	スピード設定
	void	PlayerStatus::DoubleSpeed( float param )
	{
		speed = param;
		if ( speed <= 0.0f )		speed = 0.0f;
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

//----------------------------------------------------------------------------------------------
//	Matching構造体
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	Matching::Matching( void ) : id( 0 )
	{

	}
	
	//	コンストラクタ
	Matching::Matching( int id, int mode )
	{
		Set( id, mode );
	}

	//	情報設定
	void Matching::Set( int id, int mode )
	{
		this->id = id;
		this->isComplete = mode;
	}
