
#include	"iextreme.h"
#include	"BaseChara.h"
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
		power( 0 ), step( 0 )
	{
		timer.Initialize();
		ZeroMemory( &collisionShape, sizeof( CollisionShape ) );
	}

	//	リセット
	void	AttackInfo::Reset( void )
	{
		attackParam = NO_ATTACK;
		step = 0;
		timer.Initialize();
		ZeroMemory( &collisionShape, sizeof( CollisionShape ) );
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

	//	ライフ計算
	void	LifeInfo::CulcLife( int param )
	{
		life += param;
		if ( life >= maxLife )	life = maxLife;
		if ( life <= 0 )
		{
			life = 0;
			isAlive = false;
		}
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