
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"Image.h"
#include	"HpUI.h"

//***************************************************************
//
//	HpUIクラス
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	グローバル	
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	初期化・解放
//---------------------------------------------------------------------------------------

//	コンストラクタ
HpUI::HpUI(int x, int y, int w, int h)
{
	//	座標、サイズ情報格納
	posx = x;	posy = y;	width = w;	height = h;
	
	//	HPバーフレーム
	hpFrame_obj = new Image();
	hpFrame_obj->Initialize("DATA/UI/main_UI/HP_UI.png", posx, posy, width, height, 0, 0, HP_MAX::WIDTH, HP_MAX::HEIGHT);

	//	HPダメージ
	hpDamage_obj = new Image();
	hpDamage_obj->Initialize("DATA/UI/main_UI/HP_UI.png", posx, posy, width, height, 0, HP_MAX::HEIGHT * 1, HP_MAX::WIDTH, HP_MAX::HEIGHT);

	//	HP残量
	hp_obj = new Image();				
	hp_obj->Initialize("DATA/UI/main_UI/HP_UI.png", posx, posy, width, height, 0, HP_MAX::HEIGHT * 2, HP_MAX::WIDTH, HP_MAX::HEIGHT);


	//	HP背景
	hpBack_obj = new Image();
	hpBack_obj->Initialize("DATA/UI/main_UI/HP_UI.png", posx, posy, width, height, 0, HP_MAX::HEIGHT * 3, HP_MAX::WIDTH, HP_MAX::HEIGHT);

}

//	デストラクタ
HpUI::~HpUI(void)
{
	SafeDelete(hpFrame_obj);
	SafeDelete(hpDamage_obj);
	SafeDelete(hp_obj);
	SafeDelete(hpBack_obj);
}



//---------------------------------------------------------------------------------------
//	更新・描画
//---------------------------------------------------------------------------------------

//	更新
void	HpUI::Update(void)
{
	
}

//	描画
void	HpUI::Render(void)
{
	//----------------------
	//	HPバー
	//----------------------
	hpBack_obj->Render(IMAGE_MODE::ADOPTPARAM);		//	背景
	hp_obj->Render(IMAGE_MODE::ADOPTPARAM);			//	HP残量
	hpDamage_obj->Render(IMAGE_MODE::ADOPTPARAM);	//	HPダメージ
	hpFrame_obj->Render(IMAGE_MODE::ADOPTPARAM);	//	フレーム
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

