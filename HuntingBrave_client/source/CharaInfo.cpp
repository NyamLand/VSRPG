
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
//	LifeInfo構造体
//-------------------------------------------------------------------------------------

	//	コンストラクタ
	LifeInfo::LifeInfo( void ) : 
		life( 0 ), maxLife( 0 ), 
		isAlive( true ), active( false )
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
		active = false;
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