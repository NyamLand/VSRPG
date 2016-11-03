
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
		power( power ), step( 0 ), timer( 0 ),
		initFlag( false )
	{
		ZeroMemory( &collisionShape, sizeof( CollisionShape ) );
	}

	//	リセット
	void	AttackInfo::Reset( void )
	{
		attackParam = NO_ATTACK;
		step = 0; 
		timer = 0;
		initFlag = false;
		ZeroMemory( &collisionShape, sizeof( CollisionShape ) );
	}

//-------------------------------------------------------------------------------------
//	LifeInfo構造体
//-------------------------------------------------------------------------------------

	//	コンストラクタ
	LifeInfo::LifeInfo( void ) : 
		life( 0 ), maxLife( 0 ), 
		isAlive( true )
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
	}