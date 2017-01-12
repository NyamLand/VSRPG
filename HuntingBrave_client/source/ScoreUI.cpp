
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"Image.h"
#include	<vector>
#include	"NumberUI.h"
#include	"ScoreUI.h"
#include	<math.h>

//***************************************************************
//
//	ScoreUIクラス
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	グローバル	
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	初期化・解放
//---------------------------------------------------------------------------------------

//	コンストラクタ
ScoreUI::ScoreUI(int x, int y, int w, int h)
{
	//	座標、サイズ情報格納
	size = w;	posx = x;	posy = y;

	//	SCORE文字アイコン
	icon = new Image();
	icon->Initialize("DATA/UI/main_UI/BigHuntIcon.png", posx, posy, size, size, 0, 0, SCORE_MAX::ICON_SIZE, SCORE_MAX::ICON_SIZE);

	//	経験値の値
	number = new NumberUI(x, y, w / 2 , h, SCORE_DIGIT);


}

//	デストラクタ
ScoreUI::~ScoreUI(void)
{
	SafeDelete( icon );
	SafeDelete( number );
}



//---------------------------------------------------------------------------------------
//	更新
//---------------------------------------------------------------------------------------

//	更新
void	ScoreUI::Update(void)
{
	number->SetColor(1.0f, 0.6f, 0.0f);
	number->Update(icon);

}

//---------------------------------------------------------------------------------------
//	描画
//---------------------------------------------------------------------------------------

//	描画
void	ScoreUI::Render(void)
{
	icon->Render(IMAGE_MODE::ADOPTPARAM);

	number->Render();
}


//---------------------------------------------------------------------------------------
//	情報設定
//---------------------------------------------------------------------------------------
void	ScoreUI::SetParam(int x, int y, int w, int h)
{
	size = w;
	posx = x;
	posy = y;	//	height / 6 = アイコンサイズの1/6分余白を空ける

	//	SCORE文字アイコン
	icon->x = x;	icon->y = y;	icon->w = w;	icon->h = h;

	number->SetParam(x, y, w / 2, h);

}

void	ScoreUI::SetRenderFlag(bool c)
{
	icon->renderflag = c;
	number->SetRenderFlag(c);
}

void	ScoreUI::SetScore(int s)
{
	number->SetNum(s);
}
//---------------------------------------------------------------------------------------
//	情報取得
//---------------------------------------------------------------------------------------

