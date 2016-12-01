
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"Image.h"
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
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		number[i] = new Image();
		number[i]->Initialize("DATA/UI/main_UI/Number.png", 0, 0, 0, 0, 0, 0, 0, 0);	//	初期化

		numbox[i] = -1;
	}
	exp = 1016;
	exp_digit = 0;
}

//	デストラクタ
ExpUI::~ExpUI(void)
{
	SafeDelete( icon );
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		SafeDelete( number[i] );
	}
}



//---------------------------------------------------------------------------------------
//	更新・描画
//---------------------------------------------------------------------------------------

//	更新
void	ExpUI::Update(void)
{
	//	経験値を1桁ずつに分ける
	ExpManager();

	//	各値に合わせたパラメータを入れる
	for (int i = 0; i < DIGIT_MAX; i++){
		NumberSet(number[i], numbox[i], i);
	}


}

//	経験値の値調整関数
void	ExpUI::ExpManager(void)
{

	//	桁数分の入れ物を用意(初期化)
	exp_digit = (int)log10((float)exp) + 1;				//	桁数
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		numbox[i] = -1;
	}
	//-------------------------------------------------------
	//	もし、最大桁数を超えた値の場合最大桁数の最大数を表示
	//-------------------------------------------------------
	if (DIGIT_MAX < exp_digit)
	{
		for (int i = 0; i < DIGIT_MAX; i++)
		{
			numbox[i] = 9;
		}
		return;
	}
	//-------------------------------------------------------


	for (int i = 0; i < exp_digit; i++)
	{
		int n = 10;	//	べき乗計算用
		for (int j = exp_digit - 2; j > i; j--){		//	-2はべき乗計算のために減らしている
			n *= 10;
		}

		//-------------------------
		//	1の位の時のみ
		//-------------------------
		if (i == exp_digit -1)
		{
			numbox[i] = exp % 10;
			continue;
		}

		//-------------------------
		//	その他の位
		//-------------------------
		numbox[i] = exp / n % 10;
	}
	
}

void	ExpUI::NumberSet(Image* img, const int num, const int digit)
{
	//	0～9以外の値の場合飛ばす。
	if (num < 0 || num > 9)
	{
		img->renderflag = false;
		return;
	}

	//	桁数に対応した配置
	img->w = size / 2;	img->h = size / 2;

	img->x = icon->x + icon->w / 2 + img->w / 2 + (img->w * digit);	//	アイコンの右の位置からサイズの半分*桁で場所をとる
	img->y = icon->y;
	
	//	数値に対応した切り取り範囲指定
	img->sx = num * 64;	img->sy = 64 * 3;
	img->sw = 64;		img->sh = 64;
}

//	描画
void	ExpUI::Render(void)
{
	icon->Render(IMAGE_MODE::ADOPTPARAM);

	for (int i = 0; i < DIGIT_MAX; i++)
	{
		number[i]->Render(IMAGE_MODE::ADOPTPARAM);
	}
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

}

void	ExpUI::SetRenderFlag(bool c)
{
	icon->renderflag = c;
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		number[i]->renderflag = c;
	}
}
//---------------------------------------------------------------------------------------
//	情報取得
//---------------------------------------------------------------------------------------

