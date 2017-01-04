
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"Interpolation.h"
#include	"InputManager.h"
#include	"GameParam.h"
#include	"ItemManager.h"

//**********************************************************************
//
//	ItemManagerクラス
//
//**********************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

#define	ITEM_INTERVAL	0.01f

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	ItemManager::ItemManager( void )
	{
		
	}

	//	デストラクタ
	ItemManager::~ItemManager( void )
	{

	}

	//	初期化
	bool	ItemManager::Initialize( char itemType1, char itemType2 )
	{
		item[ITEM_POS::LEFT_ITEM] = { itemType1, true, 1.0f  };
		item[ITEM_POS::RIGHT_ITEM] = { itemType2, true, 1.0f };
		return	true;
	}

//----------------------------------------------------------------------------------------------
//	更新・描画
//----------------------------------------------------------------------------------------------

	//	更新
	void	ItemManager::Update( void )
	{
		for ( int i = 0; i < ITEM_POS::ITEM_MAX; i++ )
		{
			if ( !item[i].state )
			{
				item[i].state = Interpolation::PercentageUpdate( item[i].percentage, ITEM_INTERVAL );
			}
		}

		//	左右キーで使用
		if ( item[ITEM_POS::LEFT_ITEM].state )
		{
			if ( KEY( KEY_LEFT ) == 3 )	
				UseItem( ITEM_POS::LEFT_ITEM );
		}
		
		if ( item[ITEM_POS::RIGHT_ITEM].state )
		{
			if ( KEY( KEY_RIGHT ) == 3 )	
				UseItem( ITEM_POS::RIGHT_ITEM );
		}
	}

//----------------------------------------------------------------------------------------------
//	動作関数
//----------------------------------------------------------------------------------------------

	//	アイテム情報送信
	void	ItemManager::SendItemState( char item )
	{
		SendItemData	sendItemData( item );

		gameParam->send( ( LPSTR )&sendItemData, sizeof( sendItemData ) );
	}

	//	アイテム設定送信
	void	ItemManager::SendItemSet( char leftItem, char rightItem )
	{
		//	送信するアイテム情報
		struct
		{
			char com;
			char itemCom;
			char leftItem;
			char rightItem;
		} sendData;

		//	情報設定
		sendData.com = SEND_COMMAND::ITEM_INFO;
		sendData.itemCom = ITEM_TYPE::SET_ITEM;
		sendData.leftItem = leftItem;
		sendData.rightItem = rightItem;
		
		//	情報送信
		gameParam->send( ( LPSTR )&sendData, sizeof( sendData ) );
	}

	//	アイテム試用
	void	ItemManager::UseItem( char itemPos )
	{
		item[itemPos].percentage = 0.0f;
		item[itemPos].state = false;
		SendItemState( itemPos );
	}

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------
