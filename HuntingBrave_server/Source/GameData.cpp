
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
	PlayerInfo::PlayerInfo( bool active, const LPSTR& name, int frontTitle, int backTitle )
	{
		Set( active, name, frontTitle, backTitle );
	}

	//	情報設定
	void	PlayerInfo::Set( bool active, const LPSTR& name, int frontTitle, int backTitle )
	{
		this->active = active;
		strcpy( this->name, name );
		this->frontTitle = frontTitle;
		this->backTitle = backTitle;
	}

//----------------------------------------------------------------------------------------------
//	PlayerParam構造体
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	PlayerParam::PlayerParam( const Vector3& pos, float angle, float cameraAngle, float effParam, int motion, int frame )
	{
		move = Vector3( 0.0f, 0.0f, 0.0f );
		charType = 0;
		Set( pos,angle, cameraAngle, effParam, motion,  frame );
	}

	//	情報設定
	void	PlayerParam::Set( const Vector3& pos, float angle, float cameraAngle, float effParam, int motion, int frame )
	{
		this->pos = pos;
		this->angle = angle;
		this->cameraAngle = cameraAngle;
		this->effParam = effParam;
		this->motion = motion;
		this->frame = frame;
		charType = 0;
	}

//----------------------------------------------------------------------------------------------
//	PlayerStatus構造体
//----------------------------------------------------------------------------------------------

	//	初期化
	void	PlayerStatus::Initialize( int power, int defense, int magicAttack, int magicDefense, int maxLife, float speed )
	{
		this->power = this->savePower = power;
		this->defense = this->saveDefense = defense;
		this->speed = this->saveSpeed = speed;
		this->magicAttack = this->saveMagicAttack = magicAttack;
		this->magicDefense = this->saveMagicDefense = magicDefense;
		this->maxLife = maxLife;
	}

	//	攻撃力設定
	void	PlayerStatus::CulcPower( int power )
	{
		this->power += power;
		if ( this->power <= 0 )	this->power = 0;

		savePower = this->power;
	}

	//	防御力設定
	void	PlayerStatus::CulcDefense( int defense )
	{
		this->defense += defense;
		if ( this->defense <= 0 )	this->defense = 0;

		saveDefense = this->defense;
	}

	//	魔法攻撃力設定
	void	PlayerStatus::CulcMagicAttack( int power )
	{
		this->magicAttack += power;
		if ( this->magicAttack <= 0 )	this->magicAttack = 0;

		saveMagicAttack = this->magicAttack;
	}

	//	魔法防御力設定
	void	PlayerStatus::CulcMagicDefense( int defense )
	{
		this->magicDefense += defense;
		if ( this->magicDefense <= 0 )	this->magicDefense = 0;

		saveMagicDefense = this->magicDefense;
	}

	//	最大ライフ
	void	PlayerStatus::CulcMaxLife( int maxLife )
	{
		this->maxLife += maxLife;
	}

	//	スピード設定
	void	PlayerStatus::DoubleSpeed( float param )
	{
		speed = param;
		if ( speed <= 0.0f )		speed = 0.0f;

		saveSpeed = speed;
	}
	
//----------------------------------------------------------------------------------------------
//	SignUp構造体
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	SignUp::SignUp( int id, int* name, int frontTitle, int backTitle )
	{
		Set( id, name, frontTitle, backTitle );
	}

	//	情報設定
	void	SignUp::Set( int id, int* name, int frontTitle, int backTitle )
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
//	Matching構造体
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	Matching::Matching( void ) : id( 0 )
	{

	}
	
	//	コンストラクタ
	Matching::Matching( int id, bool mode )
	{
		Set( id, mode );
	}

	//	情報設定
	void Matching::Set( int id, bool mode )
	{
		this->id = id;
		this->isComplete = mode;
	}
