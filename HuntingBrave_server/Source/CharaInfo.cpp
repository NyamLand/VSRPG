
#include	"iextreme.h"
#include	"CharaInfo.h"

//***************************************************************
//
//	Chara用構造体
//
//***************************************************************

//-------------------------------------------------------------------------------------
//	グローバル
//-------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------
//	AttackInfo構造体
//-------------------------------------------------------------------------------------

	//	コンストラクタ
	AttackInfo::AttackInfo( void ) : attackParam( NO_ATTACK ),
		step( 0 ),
		shapeType( 0 ),
		vec1( 0.0f, 0.0f, 0.0f ), vec2( 0.0f, 0.0f, 0.0f ),
		radius( 0.0f )
	{
		
	}

	//	リセット
	void	AttackInfo::Reset( void )
	{
		attackParam = NO_ATTACK;
		step = 0;
	}

//-------------------------------------------------------------------------------------
//	LifeInfo構造体
//-------------------------------------------------------------------------------------

	//	コンストラクタ
	LifeInfo::LifeInfo( void ) :
		life( 0 ), maxLife( 0 ),
		isAlive( true ), active( true )
	{

	}

	//	ライフ計算( 死んだらfalseをかえす )
	bool	LifeInfo::CulcLife( int param )
	{
		life += param;
		if ( life >= maxLife )	life = maxLife;
		if ( life <= 0 )
		{
			life = 0;
			isAlive = false;
			active = false;
			return	false;
		}

		return	true;
	}

	//	リセット
	void	LifeInfo::Reset( void )
	{
		life = maxLife;
	}

	//	情報設定
	void	LifeInfo::Initialize( int initLife )
	{
		life = initLife;
		maxLife = initLife;
		isAlive = true;
		active = true;
	}

	//	ライフ最大値加算
	void	LifeInfo::AddMaxLife( int param )
	{
		maxLife += param;
	}

//-------------------------------------------------------------------------------------
//	CollisionInfo構造体
//-------------------------------------------------------------------------------------

	//	デフォルトコンストラクタ
	CollisionInfo::CollisionInfo( void ) : height( 0.0f ), radius( 0.0f )
	{
		ZeroMemory( &collisionShape, sizeof( CollisionShape ) );
	}
	 
	//	コンストラクタ
	CollisionInfo::CollisionInfo( const CollisionShape& colShape, float hitHeight, float hitRadius )
	{
		collisionShape = colShape;
		height = hitHeight;
		radius = hitRadius;
	}

	//	形状設定
	void	CollisionInfo::SetCollisionShape( const CollisionShape& colShape )
	{
		collisionShape = colShape;
	}

	//	情報設定
	void	CollisionInfo::Set( SHAPE_TYPE shapeType, float hitHeight, float hitRadius )
	{
		collisionShape.shapeType = shapeType;
		height = hitHeight;
		radius = hitRadius;
	}