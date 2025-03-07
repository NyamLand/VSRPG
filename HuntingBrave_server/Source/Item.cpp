
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"Item.h"

//**************************************************************************
//
//	Itemクラス
//
//**************************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	Item::Item( int id ) : timer( nullptr ), 
		state( false ),
		id( id )
	{
		timer = new Timer();
	}

	//	デストラクタ
	Item::~Item( void )
	{
		SafeDelete( timer );
	}
	
//----------------------------------------------------------------------------------------------
//	更新
//----------------------------------------------------------------------------------------------
	
	//	更新
	
	//	タイマー更新
	bool	Item::TimerUpdate( void )
	{
		bool	ret = timer->Update();

		return	ret;
	}

//----------------------------------------------------------------------------------------------
//	動作関数
//----------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------
//	
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

