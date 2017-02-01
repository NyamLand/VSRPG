
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
		for ( int id = 0; id < PLAYER_MAX; id++ )
		{
			itemState[id].leftItem = nullptr;
			itemState[id].rightItem = nullptr;
		}

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
//	更新
//----------------------------------------------------------------------------------------------

	//	更新
	void	ItemManager::Update( void )
	{
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			if ( itemState[i].leftItem != nullptr )		itemState[i].leftItem->Update();
			if ( itemState[i].rightItem != nullptr )	itemState[i].rightItem->Update();
		}
	}

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

	//	情報受信
	void	ItemManager::ReceiveData( int id, const LPSTR& data )
	{
		//	初期化
		if ( data[1] == ITEM_TYPE::SET_ITEM )	AddItemState( id, data );

		//	アイテムステート切り替え
		ChangeItemState( id, data[1] );
	}

	//	アイテムステート切り換え
	void	ItemManager::ChangeItemState( int id, char itemPos )
	{
		switch ( itemPos )
		{
		case ITEM_POS::LEFT_ITEM:
			itemState[id].leftItem->UseItem();
			break;

		case ITEM_POS::RIGHT_ITEM:
			itemState[id].rightItem->UseItem();
			break;

		default:
			break;
		}
	}

	//	アイテムステート追加
	void	ItemManager::AddItemState( int id, const LPSTR& data )
	{
		//	受信したアイテム情報
		struct ReceiveData
		{
			char com;
			char itemCom;
			char leftItem;
			char rightItem;
		} *receiveData;

		//	変換
		receiveData = ( ReceiveData* )data;

		//	アイテム設定
		SetItem( id, itemState[id].leftItem, receiveData->leftItem );
		SetItem( id, itemState[id].rightItem, receiveData->rightItem );
	}

	//	アイテムセット
	void	ItemManager::SetItem( int id, Item*& item, char itemType )
	{
		if ( item != nullptr )	return;

		switch ( itemType )
		{
		case ITEM_TYPE::ATK:
			item = new AttackItem( id );
			break;

		case ITEM_TYPE::DEF:
			item = new DefenseItem( id );
			break;

		case ITEM_TYPE::HEAL:
			item = new HealItem( id );
			break;

		case ITEM_TYPE::SPEED:
			item = new SpeedItem( id );
			break;

		default:
			printf( "%dP itemSetError\n", id );
			break;
		}
	}
	
//----------------------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------------------
