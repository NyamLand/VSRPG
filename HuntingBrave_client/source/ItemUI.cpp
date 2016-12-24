
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"Interpolation.h"
#include	"GameManager.h"
#include	"system/System.h"
#include	"ItemManager.h"
#include	"Image.h"
#include	"ItemUI.h"

//***************************************************************
//
//	ItemUIクラス
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	グローバル	
//---------------------------------------------------------------------------------------

#define	ICON_SIZE		50
#define	ICON_SPACE	90
#define	ICON_HEIGHT_DIST	20
#define	ICON_SRC_SIZE	128

#define	WIDTH  512				//	画像横幅
#define	HEIGHT  256				//	画像縦幅
#define	SPX  0
#define	SPY  256 * 3

namespace 
{
	const LPSTR fileName[] = 
	{
		"DATA/UI/icon/item/01Heal.png",
		"DATA/UI/icon/item/02Atk.png",
		"DATA/UI/icon/item/03Def.png",
		"DATA/UI/icon/item/03Led.png"
	};

}

//---------------------------------------------------------------------------------------
//	初期化・解放
//---------------------------------------------------------------------------------------

	//	コンストラクタ
	ItemUI::ItemUI( int x, int y, int w, int h )
	{
		posx = x;
		posy = y;
		width = w;
		height = h;

		//	アイコン初期化
		IconInitialize();

		//	アイテム背景初期化
		obj = new Image();
		obj->Initialize( "DATA/UI/main_UI/HP_item_UI.png", 
			posx, posy, width, height, 
			SPX, SPY, WIDTH, HEIGHT );
	}

	//	デストラクタ
	ItemUI::~ItemUI( void )
	{
		SafeDelete( obj );
		SafeDelete( icon[0] );
		SafeDelete( icon[1] );
	}

	//	アイコン初期化
	void	ItemUI::IconInitialize( void )
	{
		//	タイプ取得
		char leftItem = itemManager->GetItemType( ITEM_POS::LEFT_ITEM );
		char rightItem = itemManager->GetItemType( ITEM_POS::RIGHT_ITEM );

		//	左アイテム初期化
		icon[ITEM_POS::LEFT_ITEM] = new Image();
		icon[ITEM_POS::LEFT_ITEM]->Initialize(
			fileName[leftItem],
			posx - ICON_SPACE / 2, posy + ICON_HEIGHT_DIST,
			ICON_SIZE, ICON_SIZE,
			0, 0, ICON_SRC_SIZE, ICON_SRC_SIZE );

		//	右アイテム初期化
		icon[ITEM_POS::RIGHT_ITEM] = new Image();
		icon[ITEM_POS::RIGHT_ITEM]->Initialize(
			fileName[rightItem],
			posx + ICON_SPACE / 2, posy + ICON_HEIGHT_DIST,
			ICON_SIZE, ICON_SIZE,
			0, 0, ICON_SRC_SIZE, ICON_SRC_SIZE );

		//	仮
		itemInterval[ITEM_POS::LEFT_ITEM] = 1.0f;
		itemInterval[ITEM_POS::RIGHT_ITEM] = 1.0f;
	}

//---------------------------------------------------------------------------------------
//	更新・描画
//---------------------------------------------------------------------------------------

//	更新
void	ItemUI::Update( void )
{
	itemInterval[ITEM_POS::LEFT_ITEM] = 
		itemManager->GetInterval( ITEM_POS::LEFT_ITEM );

	itemInterval[ITEM_POS::RIGHT_ITEM] =
		itemManager->GetInterval( ITEM_POS::RIGHT_ITEM );
}

//	描画
void	ItemUI::Render( void )
{
	obj->Render( IMAGE_MODE::ADOPTPARAM );

	for ( int i = 0; i < ITEM_POS::ITEM_MAX; i++ )
	{
		shader2D->SetValue( "center", Vector3( icon[i]->x, icon[i]->y, 0.0f ) );
		shader2D->SetValue( "radian", ( PI * 2 ) * itemInterval[i] - PI );
		icon[i]->Render( IMAGE_MODE::NORMAL, shader2D, "circleShadow" );
	}
}

