
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	<map>
#include	"GameParam.h"
#include	"ItemManager.h"

//*****************************************************************************************************************************
//
//	ItemManagerクラス
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

ItemManager*	itemManager = nullptr;

#define	HEAL_LIFE	30

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	ItemManager::ItemManager( void )
	{
		Initialize();
	}

	//	デストラクタ
	ItemManager::~ItemManager( void )
	{
		Release();
	}

	//	初期化
	bool	ItemManager::Initialize( void )
	{
		for ( int id = 0; id < PLAYER_MAX; id++ )
		{	
			itemState[id].leftItem = nullptr;
			itemState[id].rightItem = nullptr;
		}

		return	true;
	}

	//	解放
	void	ItemManager::Release( void )
	{
		for ( int id = 0; id < PLAYER_MAX; id++ )
		{
			SafeDelete( itemState[id].leftItem );
			SafeDelete( itemState[id].rightItem );
		}
	}

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

	//	アイテムステート切り換え
	void	ItemManager::ChangeItemState( int id, char itemType )
	{
		//	ON/OFF
	}

	//	アイテムステート追加
	void	ItemManager::AddItemState( int id, char leftItem, char rightItem )
	{
		
	}

	//	アイテム初期化
	void	ItemManager::SetItem( Item* item, char itemType )
	{
		if ( item != nullptr )	return;

		switch ( itemType )
		{
		case ITEM_TYPE::ATK:
			break;

		case ITEM_TYPE::DEF:
			break;

		case ITEM_TYPE::HEAL:
			break;

		case ITEM_TYPE::LED:
			break;

		default:
			break;
		}
	}
	
//----------------------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------------------

	//	アイテムステート取得
	bool	ItemManager::GetItemState( int id, char itemType )
	{
		return	false;
	}