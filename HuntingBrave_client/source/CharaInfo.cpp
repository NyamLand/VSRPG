
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

	}

	//	リセット
	void	AttackInfo::Reset( void )
	{
		attackParam = NO_ATTACK;
		step = 0; 
		timer = 0;
		initFlag = false;
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
		if ( life <= 0 )				life = 0;
		if ( life >= maxLife )	life = maxLife;
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