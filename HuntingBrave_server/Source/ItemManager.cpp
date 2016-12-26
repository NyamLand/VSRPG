
#include	"iextreme.h"
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
			itemMap[id].clear();
		}

		return	true;
	}

	//	解放
	void	ItemManager::Release( void )
	{
		for ( int id = 0; id < PLAYER_MAX; id++ )
		{
			itemMap[id].clear();
		}
	}

//----------------------------------------------------------------------------------------------
//	動作関数
//----------------------------------------------------------------------------------------------

	//	回復
	void	ItemManager::Heal( int id )
	{
		//	回復
		gameParam->GetLifeInfo( id ).CulcLife( HEAL_LIFE );
	}

	//	攻撃
	void	ItemManager::Power( int id )
	{
		if ( !itemMap[id][ITEM_TYPE::ATK] )	return;

		//	攻撃力増加
	}

	//	防御
	void	ItemManager::Defense( int id )
	{
		if ( !itemMap[id][ITEM_TYPE::DEF] )	return;

		//	防御力増加
	}

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

	//	アイテムステート切り換え
	void	ItemManager::ChangeItemState( int id, char itemType )
	{
		//	ON/OFF
		itemMap[id][itemType] = !itemMap[id][itemType];
	}

	//	アイテムステート追加
	void	ItemManager::AddItemState( int id, char itemType )
	{
		//	見つからない
		itemMap[id].insert(
			std::map<char, bool>::value_type( itemType, false ) );
	}

//----------------------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------------------

	//	アイテムステート取得
	bool	ItemManager::GetItemState( int id, char itemType )
	{
		return	itemMap[id][itemType];
	}