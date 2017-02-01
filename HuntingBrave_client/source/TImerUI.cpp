
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
	number[TIME::MIN] = new NumberUI(x - (size * 2.5f), y, w, h, TIME_DIGIT);
	number[TIME::SECOND] = new NumberUI(x + (size * 0.5f) , y, w, h, TIME_DIGIT);
	number[TIME::MIN]->SetSlide(false);
	number[TIME::SECOND]->SetSlide(false);

	period = new Image();
	period->Initialize("DATA/UI/main_UI/Number.png", posx, posy, size, size, 64 * 10, 64 * color , 64, 64);

	//	演出用タイマー
	number_wave[TIME::MIN] = new NumberUI(x - (size * 2.5f), y, w, h, TIME_DIGIT);
	number_wave[TIME::SECOND] = new NumberUI(x + (size * 0.5f), y, w, h, TIME_DIGIT);
	number_wave[TIME::MIN]->SetSlide(false);
	number_wave[TIME::SECOND]->SetSlide(false);

	period_wave = new Image();
	period_wave->Initialize("DATA/UI/main_UI/Number.png", posx, posy, size, size, 64 * 10, 64 * color, 64, 64);
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

	//	30秒切ってからの演出
	if (timer > 30) return;

	

	for (int i = 0; i < TIME_DIGIT; i++){
		number_wave[TIME::MIN]->GetNumber(i)->SetWave(0.017f);
		number_wave[TIME::MIN]->GetNumber(i)->WaveUpdate(32, 1.0f);

		number_wave[TIME::SECOND]->GetNumber(i)->SetWave(0.017f);
		number_wave[TIME::SECOND]->GetNumber(i)->WaveUpdate(32, 1.0f);
	}
	period_wave->SetWave(0.017f);
	period_wave->WaveUpdate(32, 1.0f);

	number_wave[TIME::MIN]->SetNum(timer / 60);
	number_wave[TIME::SECOND]->SetNum((int)timer % 60);

	number_wave[TIME::MIN]->Update();
	number_wave[TIME::SECOND]->Update();
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

	if (timer > 30) return;
	period_wave->Render(IMAGE_MODE::WAVE);
	number_wave[TIME::MIN]->Render(IMAGE_MODE::WAVE);
	number_wave[TIME::SECOND]->Render(IMAGE_MODE::WAVE);

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

