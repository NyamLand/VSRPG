
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"Image.h"
#include	<vector>
#include	"NumberUI.h"
#include	"ExpUI.h"
#include	<math.h>

//***************************************************************
//
//	ExpUIクラス
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	グローバル	
//---------------------------------------------------------------------------------------

namespace
{
	const int NEED_EXP_SRC_POS_Y = 256;
	const int NEED_EXP_SRC_WIDTH = 256;
	const int NEED_EXP_SRC_HEIGHT = 128;
}

//---------------------------------------------------------------------------------------
//	初期化・解放
//---------------------------------------------------------------------------------------

//	コンストラクタ
ExpUI::ExpUI(int x, int y, int w, int h)
{
	//	座標、サイズ情報格納
	size = w;	posx = x;	posy = y;

	//	EXP文字アイコン
	icon = new Image();
	icon->Initialize("DATA/UI/main_UI/ExpIcon.png", posx, posy, size, size, 0, 0, EXP_MAX::ICON_SIZE, EXP_MAX::ICON_SIZE);

	//	経験値の値
	number = new NumberUI(x, y, w / 2, h, EXP_DIGIT);
}

//	デストラクタ
ExpUI::~ExpUI(void)
{
	SafeDelete( icon );
	SafeDelete( number );
}



//---------------------------------------------------------------------------------------
//	更新
//---------------------------------------------------------------------------------------

//	更新
void	ExpUI::Update(void)
{
	number->SetColor(NUM_COLOR::GREEN);
	number->Update(icon);
	
}

//---------------------------------------------------------------------------------------
//	描画
//---------------------------------------------------------------------------------------

//	描画
void	ExpUI::Render(void)
{
	icon->Render(IMAGE_MODE::ADOPTPARAM);

	number->Render();
}

//---------------------------------------------------------------------------------------
//	動作関数
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	情報設定
//---------------------------------------------------------------------------------------
void	ExpUI::SetParam(int x, int y, int w, int h)
{
	size = w;
	posx = x;
	posy = y;	//	height / 6 = アイコンサイズの1/6分余白を空ける

	//	SCORE文字アイコン
	icon->x = x;	icon->y = y;	icon->w = w;	icon->h = h;

	number->SetParam(x, y, w / 2, h);

}

void	ExpUI::SetRenderFlag(bool c)
{
	icon->renderflag = c;
	number->SetRenderFlag(c);
}

void	ExpUI::SetExp(int e)
{
	number->SetNum(e);
}

//***************************************************************
//
//	NeedExpUIクラス
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	初期化・解放
//---------------------------------------------------------------------------------------

	//	コンストラクタ
	NeedExpUI::NeedExpUI( int x, int y, int w, int h ) : ExpUI( x, y, w, h )
	{
		//	座標、サイズ情報格納
		size = w;	posx = x;	posy = y;

		//	EXP文字アイコン
		icon = new Image();
		icon->Initialize( "DATA/UI/BackGround/Upgrade_UIparts.png", posx, posy, size, size, 
			0, NEED_EXP_SRC_POS_Y, 
			NEED_EXP_SRC_WIDTH, NEED_EXP_SRC_HEIGHT );

		//	経験値の値
		number = new NumberUI( x, y, w / 2, h, EXP_DIGIT );
	}

	NeedExpUI::~NeedExpUI( void )
	{

	}