
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"Image.h"
#include	<vector>
#include	"NumberUI.h"
#include	"TimeUpUI.h"
#include	<math.h>

//***************************************************************
//
//	TimeUpUIクラス
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	グローバル	
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
//	初期化・解放
//---------------------------------------------------------------------------------------

//	コンストラクタ
TimeUpUI::TimeUpUI() : flag(false)
{
	//	座標、サイズ情報格納
	width = TIMEUP_MAX::WIDTH;		height = TIMEUP_MAX::HEIGHT;		posx = iexSystem::ScreenWidth / 2;		posy = iexSystem::ScreenHeight / 2;

	//	SCORE文字アイコン
	obj = new Image();
	obj->Initialize("DATA/UI/main_UI/time_up.png", posx, posy, 0, 0, 0, 0, TIMEUP_MAX::WIDTH, TIMEUP_MAX::HEIGHT);

	//	演出用
	obj_wave = new Image();
	obj_wave->Initialize("DATA/UI/main_UI/time_up.png", posx, posy, width, height, 0, 0, TIMEUP_MAX::WIDTH, TIMEUP_MAX::HEIGHT);



}

//	デストラクタ
TimeUpUI::~TimeUpUI(void)
{
	SafeDelete(obj);
	SafeDelete(obj_wave);
}



//---------------------------------------------------------------------------------------
//	更新
//---------------------------------------------------------------------------------------

//	更新
bool	TimeUpUI::Update(void)
{

	//	ウェーブ開始
	if (flag)
	{
		if (obj_wave->WaveUpdate(TIMEUP_MAX::WIDTH))	return true;
	}
	else{
		//	じょじょに大きく表示
		obj->SetScaling(0.1f);
		if (obj->ScalingBigUpdate(TIMEUP_MAX::WIDTH))
		{
			obj_wave->SetWave(0.04f);
			flag = true;
		}
	}
	return false;
}

//---------------------------------------------------------------------------------------
//	描画
//---------------------------------------------------------------------------------------

//	描画
void	TimeUpUI::Render(void)
{
	obj->Render(IMAGE_MODE::SCALING);

	if (flag)
	{
		obj_wave->Render(IMAGE_MODE::WAVE);
	}
}


//---------------------------------------------------------------------------------------
//	情報設定
//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
//	情報取得
//---------------------------------------------------------------------------------------

