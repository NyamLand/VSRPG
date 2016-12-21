
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"Interpolation.h"
#include	"GameManager.h"
#include	"system/System.h"
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
	icon[0] = new Image();
	icon[0]->Initialize( fileName[0], posx - ICON_SPACE / 2, posy + ICON_HEIGHT_DIST, ICON_SIZE, ICON_SIZE, 
		0, 0, ICON_SRC_SIZE, ICON_SRC_SIZE );
	icon[1] = new Image();
	icon[1]->Initialize( fileName[1], posx + ICON_SPACE / 2, posy + ICON_HEIGHT_DIST, ICON_SIZE, ICON_SIZE,
		0, 0, ICON_SRC_SIZE, ICON_SRC_SIZE );

	//	アイテム背景初期化
	obj = new Image();
	obj->Initialize( "DATA/UI/main_UI/HP_item_UI.png", posx, posy, width, height, ITEM_MAX::SPX, ITEM_MAX::SPY, ITEM_MAX::WIDTH, ITEM_MAX::HEIGHT );

	//	仮
	itemInterval[0] = 1.0f;
	itemInterval[1] = 1.0f;
}

//	デストラクタ
ItemUI::~ItemUI( void )
{
	SafeDelete(obj);
	SafeDelete( icon[0] );
	SafeDelete( icon[1] );
}


//---------------------------------------------------------------------------------------
//	更新・描画
//---------------------------------------------------------------------------------------

//	更新
void	ItemUI::Update( void )
{
	bool	state1 = Interpolation::PercentageUpdate( itemInterval[0], 0.01f );
	bool state2 = Interpolation::PercentageUpdate( itemInterval[1], 0.01f );

	if ( KEY( KEY_LEFT ) == 3 )
	{
		if( state1 )	itemInterval[0] = 0.0f;
	}

	if ( KEY( KEY_RIGHT ) == 3 )
	{
		if( state2 )	itemInterval[1] = 0.0f;
	}
}

//	描画
void	ItemUI::Render(void)
{
	obj->Render( IMAGE_MODE::ADOPTPARAM );

	for ( int i = 0; i < 2; i++ )
	{
		shader2D->SetValue( "center", Vector3( icon[i]->x, icon[i]->y, 0.0f ) );
		shader2D->SetValue( "radian", ( 2 * PI ) * itemInterval[i] - PI );
		icon[i]->Render( IMAGE_MODE::NORMAL, shader2D, "circleShadow" );
	}
}

//---------------------------------------------------------------------------------------
//	動作関数
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	情報設定
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	情報取得
//---------------------------------------------------------------------------------------

