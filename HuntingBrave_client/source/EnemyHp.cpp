
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"Image.h"
#include	"EnemyManager.h"


#include	"EnemyHp.h"

//***************************************************************
//
//	EnemyHpUIクラス
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	グローバル	
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	初期化・解放
//---------------------------------------------------------------------------------------

//	コンストラクタ
EnemyHpUI::EnemyHpUI(int x, int y, int w, int h)
{
	//	座標、サイズ情報格納
	posx = x;	posy = y;	width = w;	height = h;

	//	HPバーフレーム
	hpFrame_obj = new Image();
	hpFrame_obj->Initialize("DATA/UI/main_UI/Enemy_HP.png", posx, posy, width, height, 0, 0, HP_MAX::WIDTH, HP_MAX::HEIGHT);

	//	HP残量
	hp_obj = new Image();
	hp_obj->Initialize("DATA/UI/main_UI/Enemy_HP.png", posx, posy, width, height, 0, HP_MAX::HEIGHT * 1, HP_MAX::WIDTH, HP_MAX::HEIGHT);


	//	HP背景
	hpBack_obj = new Image();
	hpBack_obj->Initialize("DATA/UI/main_UI/HP_UI.png", posx, posy, width, height, 0, HP_MAX::HEIGHT * 3, HP_MAX::WIDTH, HP_MAX::HEIGHT);

}

//	デストラクタ
EnemyHpUI::~EnemyHpUI(void)
{
	SafeDelete(hpFrame_obj);
	SafeDelete(hp_obj);
	SafeDelete(hpBack_obj);
}



//---------------------------------------------------------------------------------------
//	更新・描画
//---------------------------------------------------------------------------------------

//	更新
void	EnemyHpUI::Update(void)
{
	
	
}

//	描画
void	EnemyHpUI::Render(void)
{
	//----------------------
	//	HPバー
	//----------------------
	hpBack_obj->Render(IMAGE_MODE::NORMAL);		//	背景
	hp_obj->Render(IMAGE_MODE::NORMAL);			//	HP残量
	hpFrame_obj->Render(IMAGE_MODE::NORMAL);	//	フレーム
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

