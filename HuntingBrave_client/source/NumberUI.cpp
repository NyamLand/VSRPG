
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"Image.h"
#include	<vector>
#include	"NumberUI.h"
#include	<math.h>

//***************************************************************
//
//	NumberUIクラス
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	グローバル	
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	初期化・解放
//---------------------------------------------------------------------------------------

//	コンストラクタ
NumberUI::NumberUI(int x, int y, int w, int h, int digit)
{
	//	座標、サイズ情報格納
	size = w;
	posx = x;
	posy = y;	//	height / 6 = アイコンサイズの1/6分余白を空ける
	number.clear();
	numbox.clear();

	number.resize(digit);
	numbox.resize(digit);

	DIGIT_MAX = digit;
	slide_state = true;
	//	経験値の値
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		number[i] = new Image();
		number[i]->Initialize("DATA/UI/main_UI/Number.png", posx, posy, size, size, 0, 0, 0, 0);	//	初期化

		numbox[i] = -1;
	}
	num = 0;
	digit = 0;
	color = NUM_COLOR::WHITE;
}

//	デストラクタ
NumberUI::~NumberUI(void)
{
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		SafeDelete(number[i]);
	}
}



//---------------------------------------------------------------------------------------
//	更新
//---------------------------------------------------------------------------------------

//	更新
void	NumberUI::Update(const Image* icon)
{
	//	経験値を1桁ずつに分ける
	NumberManager();

	//	各値に合わせたパラメータを入れる
	//	アイコンあり
	if (icon != null)
	{
		for (int i = 0; i < DIGIT_MAX; i++){
			NumberSet(number[i], numbox[i], i, icon, color);
		}
	}
	//	アイコンなし
	else
	{
		for (int i = 0; i < DIGIT_MAX; i++){
			NumberSet(number[i], numbox[i], i, color);
		}
	}

}

//---------------------------------------------------------------------------------------
//	動作関数
//---------------------------------------------------------------------------------------

//	経験値の値調整関数
void	NumberUI::NumberManager(void)
{

	//	桁数分の入れ物を用意(初期化)
	digit = (int)log10((float)num) + 1;				//	桁数
	if (num == 0) digit = 1;
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		numbox[i] = -1;
	}

	if (!slide_state)	digit = DIGIT_MAX;
	//-------------------------------------------------------
	//	もし、最大桁数を超えた値の場合最大桁数の最大数を表示
	//-------------------------------------------------------
	if (DIGIT_MAX < digit)
	{
		for (int i = 0; i < DIGIT_MAX; i++)
		{
			numbox[i] = 9;
		}
		return;
	}
	//-------------------------------------------------------


	for (int i = 0; i < digit; i++)
	{
		int n = 10;	//	べき乗計算用
		for (int j = digit - 2; j > i; j--){		//	-2はべき乗計算のために減らしている
			n *= 10;
		}

		//-------------------------
		//	1の位の時のみ
		//-------------------------
		if (i == digit - 1)
		{
			numbox[i] = num % 10;
			continue;
		}

		//-------------------------
		//	その他の位
		//-------------------------
		numbox[i] = num / n % 10;
	}

}

//	アイコンあり
void	NumberUI::NumberSet(Image* img, const int num, const int digit, const Image* icon, int color)
{
	//	0～9以外の値の場合飛ばす。
	if (num < 0 || num > 9)
	{
		img->renderflag = false;
		return;
	}

	//	桁数に対応した配置
	img->w = size;	img->h = size;
	img->x = icon->x + icon->w / 2 + img->w / 2 + (img->w * digit); // アイコンの右の位置からサイズの半分*桁で場所をとる
	img->y = posy;

	//	数値に対応した切り取り範囲指定
	img->sx = num * 64;	img->sy = 64 * color;
	img->sw = 64;		img->sh = 64;
	
	img->renderflag = true;
}

//	アイコンなし
void	NumberUI::NumberSet(Image* img, const int num, const int digit, int color)
{
	//	0～9以外の値の場合飛ばす。
	if (num < 0 || num > 9)
	{
		img->renderflag = false;
		return;
	}

	//	桁数に対応した配置
	img->w = size;	img->h = size;
	img->x = posx + img->w / 2 + (img->w * digit);
	img->y = posy;

	//	数値に対応した切り取り範囲指定
	img->sx = num * 64;	img->sy = 64 * color;
	img->sw = 64;		img->sh = 64;

	img->renderflag = true;
}

//---------------------------------------------------------------------------------------
//	描画
//---------------------------------------------------------------------------------------

void	NumberUI::Render(int mode)
{

	for (int i = 0; i < DIGIT_MAX; i++)
	{
		number[i]->Render(mode);
	}
}


//---------------------------------------------------------------------------------------
//	情報設定
//---------------------------------------------------------------------------------------
void	NumberUI::SetParam(int x, int y, int w, int h)
{
	size = w;
	posx = x;
	posy = y;	//	height / 6 = アイコンサイズの1/6分余白を空ける

}

void	NumberUI::SetRenderFlag(bool c)
{
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		number[i]->renderflag = c;
	}
}

void	NumberUI::SetNum(int n)
{
	num = n;
}

void	NumberUI::SetColor(int c)
{
	color = c;
}

void	NumberUI::SetSlide(bool state)
{
	slide_state = state;
}

Image*	NumberUI::GetNumber(int num)
{
	return number[num];
}

void	NumberUI::SetColor(float r, float g, float b)
{
	for (int i = 0; i < DIGIT_MAX; i++)
	{
		number[i]->color = Vector3(r, g, b);
	}
}

//---------------------------------------------------------------------------------------
//	情報取得
//---------------------------------------------------------------------------------------

