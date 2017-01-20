
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"Image.h"
#include	<vector>
#include	"NumberUI.h"
#include	"TimerUI.h"

//***************************************************************
//
//	TimerUIクラス
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	グローバル	
//---------------------------------------------------------------------------------------
//	include
#define	TIME_DIGIT	2
//---------------------------------------------------------------------------------------
//	初期化・解放
//---------------------------------------------------------------------------------------

//	コンストラクタ
TimerUI::TimerUI(int x, int y, int w, int h)
{
	//	座標、サイズ情報格納
	size = w;
	posx = x;
	posy = y;	//	height / 6 = アイコンサイズの1/6分余白を空ける
	color = NUM_COLOR::WHITE;

	//	タイマーの値
	number[TIME::MIN] = new NumberUI(x - (size * 1.5f), y, w, h, TIME_DIGIT);
	number[TIME::SECOND] = new NumberUI(x + (size * 0.5f) , y, w, h, TIME_DIGIT);

	period = new Image();
	period->Initialize("DATA/UI/main_UI/Number.png", posx, posy, size, size, 64 * 10, 64 * color , 64, 64);
}

//	デストラクタ
TimerUI::~TimerUI(void)
{

}



//---------------------------------------------------------------------------------------
//	更新・描画
//---------------------------------------------------------------------------------------

//	更新
void	TimerUI::Update(void)
{
	timer = gameManager->GetTime();

	number[TIME::MIN]->SetNum(timer / 60);
	number[TIME::SECOND]->SetNum((int)timer % 60);

	number[TIME::MIN]->Update();
	number[TIME::SECOND]->Update();
}

//	描画
void	TimerUI::Render(void)
{
	char str[64];
	sprintf_s( str, "timer = %f秒",timer );
	IEX_DrawText( str, 600, 100, 400, 100, 0xFF00FF00 );

	period->Render(IMAGE_MODE::ADOPTPARAM);
	number[TIME::MIN]->Render();
	number[TIME::SECOND]->Render();

	//time_obj->Render( IMAGE_MODE::FLASH );
}

//--------------------------------------------------------------------------------------
//	動作関数-
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	情報設定
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	情報取得
//---------------------------------------------------------------------------------------

