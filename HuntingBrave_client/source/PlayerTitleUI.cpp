
#include	"iextreme.h"
#include	"system/System.h"
#include	"GlobalFunction.h"
#include	"GameParam.h"
#include	"PlayerTitleUI.h"

//***************************************************************
//
//	PlayerTitleUIクラス
//
//***************************************************************

//----------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------

#define	FRONT_MAX		10
#define	SRC_W		256
#define	SRC_H		102

//----------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------

	//	コンストラクタ
	PlayerTitleUI::PlayerTitleUI( void ) : frontTitleImage( nullptr ), backTitleImage( nullptr ),
		index( - 1 ), posx( 0 ), posy( 0 )
	{

	}

	//	デストラクタ
	PlayerTitleUI::~PlayerTitleUI( void )
	{
		SafeDelete( frontTitleImage );
		SafeDelete( backTitleImage );
	}

	//	初期化 front : 0 ~ 19 back : 0 ~ 9
	void	PlayerTitleUI::Initialize( int front, int back, int x, int y, int w, int h )
	{
		this->front = front;
		this->back = back;

		//	前称号初期化
		frontTitleImage = new Image();
		
		//	frontTitle初期化
		if ( front >= FRONT_MAX )
		{
			frontTitleImage->Initialize( "DATA/UI/menu_UI/PlTitle_front01.png", 
				x - w / 2, y, w, h, 
				( ( front - FRONT_MAX ) % 2 ) * SRC_W,
				( ( front - FRONT_MAX ) / 2 )	 * SRC_H,
				SRC_W, SRC_H );
		}
		else
		{
			frontTitleImage->Initialize( "DATA/UI/menu_UI/PlTitle_front02.png",
				x - w / 2, y, w, h,
				( front % 2 ) * SRC_W,
				( front / 2 )	 * SRC_H,
				SRC_W, SRC_H );
		}

		//	backTitle初期化
		backTitleImage = new Image();
		backTitleImage->Initialize( "DATA/UI/menu_UI/PlTitle_back01.png",
			x + w / 2, y, w, h,
			( back % 2 ) * SRC_W,
			( back / 2 )	 * SRC_H,
			SRC_W, SRC_H );
	}

//----------------------------------------------------------------------------------
//	更新
//----------------------------------------------------------------------------------

	//	更新
	void	PlayerTitleUI::Update( void )
	{

	}

//----------------------------------------------------------------------------------
//	更新
//----------------------------------------------------------------------------------

	//	描画
	void	PlayerTitleUI::Render( void )
	{
		frontTitleImage->Render( IMAGE_MODE::NORMAL );
		backTitleImage->Render( IMAGE_MODE::NORMAL );
	}

//----------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------

	//	座標
	void	PlayerTitleUI::SetPos( int x, int y )
	{
		frontTitleImage->x = x - frontTitleImage->w / 2;
		frontTitleImage->y = y;
		backTitleImage->x = x + frontTitleImage->w / 2;
		backTitleImage->y = y;
	}

	//	称号設定
	void	PlayerTitleUI::SetTitle( int front, int back )
	{
		this->front = front;
		this->back = back;

		//	frontTitle初期化
		if ( front >= FRONT_MAX )
		{
				frontTitleImage->sx = ( ( front - FRONT_MAX ) % 2 ) * SRC_W;
				frontTitleImage->sy = ( ( front - FRONT_MAX ) / 2 )	 * SRC_H;
		}
		else
		{
				frontTitleImage->sx = ( front % 2 ) * SRC_W;
				frontTitleImage->sy = ( front / 2 )	 * SRC_H;
		}

		//	backTitle初期化
		backTitleImage->sx = ( back % 2 ) * SRC_W;
		backTitleImage->sy = ( back / 2 ) * SRC_H;
	}