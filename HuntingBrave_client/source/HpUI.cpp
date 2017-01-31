
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"Interpolation.h"
#include	"Image.h"
#include	"NumberUI.h"
#include	"HpUI.h"

//***************************************************************
//
//	HpUIクラス
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	グローバル	
//---------------------------------------------------------------------------------------
//include
#define HP_DIGIT 3


//---------------------------------------------------------------------------------------
//	初期化・解放
//---------------------------------------------------------------------------------------

//	コンストラクタ
HpUI::HpUI(int x, int y, int w, int h)
{
	//	座標、サイズ情報格納
	posx = x - w / 2;	posy = y - h / 2;	width = w;	height = h;

	//	HPのパラメータ容器
	hp = 0;		max_hp = 0;		damage = 0;
	
	//	HPバーフレーム
	hpFrame_obj = new Image();
	hpFrame_obj->Initialize("DATA/UI/main_UI/HP_UI.png", x, y, width, height, 0, 0, HP_MAX::WIDTH, HP_MAX::HEIGHT);

	//	HPダメージ
	hpDamage_obj = new iex2DObj("DATA/UI/main_UI/HP_UI.png");
	//	HP残量(バー)
	hp_obj = new iex2DObj("DATA/UI/main_UI/HP_UI.png");
	//	HP背景
	hpBack_obj = new Image();
	hpBack_obj->Initialize("DATA/UI/main_UI/HP_UI.png", x, y, width, height, 0, HP_MAX::HEIGHT * 3, HP_MAX::WIDTH, HP_MAX::HEIGHT);

	//	HP残量(数字）
	nowHpUI = new NumberUI(x - (HP_MAX::SIZE * 2.0f), y, HP_MAX::SIZE, HP_MAX::SIZE, HP_DIGIT);
	maxHpUI = new NumberUI(x + (HP_MAX::SIZE * 2.0f), y, HP_MAX::SIZE, HP_MAX::SIZE, HP_DIGIT);
	period = new Image();
	period->Initialize("DATA/UI/main_UI/Number.png", x + (HP_MAX::SIZE * 1.5f), y, HP_MAX::SIZE, HP_MAX::SIZE, 64 * 11, 64 * NUM_COLOR::WHITE, 64, 64);

	hp_damage_sw = 0;		hp_w = width;
	hp_sw = HP_MAX::WIDTH;	damage_width = 0;	keep_width = 0;			damage_volume = 0.0f;


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
	if (damage != 0)
	{
		SetDamage();
		DamageManager();
	}

	nowHpUI->SetNum(this->hp);
	maxHpUI->SetNum(this->max_hp);

	nowHpUI->Update();
	maxHpUI->Update();
}

//
void	HpUI::SetDamage(void)
{
	if (damage_state == true) return;

	//	hpの割合
	float p = (float)((float)hp / (float)max_hp);

	//	hp残量の計算
	hp_w = width * p;
	hp_sw = HP_MAX::WIDTH * p;
	
	//	ダメージ量の幅
	damage_width = keep_width - hp_w;

	//	ダメージ割合
	//damage_volume = (float)damage_width / 60.0f;

	damage_state = true;
	

}

//
void	HpUI::DamageManager(void)
{
	

	//	ダメージの全体割合
	float d = (float)(damage_width + hp_w) / (float)width;
	

	hp_damage_sw = HP_MAX::WIDTH * d;

	Interpolation::LinearInterpolation(damage_width, keep_width - hp_w, 0, damage_volume);

	damage_volume += 0.02;

	if (damage_volume >= 1.0f)
	{
		damage = 0;
		damage_volume = 0.0f;
		keep_width = 0;
		damage_state = false;
	}
}

//	描画
void	HpUI::Render(void)
{
	//----------------------
	//	HPバー
	//----------------------
	hpBack_obj->Render(IMAGE_MODE::ADOPTPARAM);		//	背景
	hpDamage_obj->Render(posx, posy, hp_w + damage_width, height, 0, HP_MAX::HEIGHT * 1, hp_damage_sw, HP_MAX::HEIGHT);	//	HPダメージ
	hp_obj->Render(posx, posy, hp_w, height, 0, HP_MAX::HEIGHT * 2, hp_sw, HP_MAX::HEIGHT);	//	HP残量
	hpFrame_obj->Render(IMAGE_MODE::ADOPTPARAM);	//	フレーム

	//	hp数値
	period->Render(IMAGE_MODE::ADOPTPARAM);
	nowHpUI->Render();
	maxHpUI->Render();
}

//---------------------------------------------------------------------------------------
//	動作関数
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	情報設定
//---------------------------------------------------------------------------------------

void	HpUI::SetHp(int hp)
{
	//	ダメージ処理中かつ、HPダメージを受けてなければスルー
	if (this->damage != 0 && this->hp == hp) return;

	this->damage = this->hp - hp;
	this->hp = hp;

	//	もしダメージ受けていれば
	if (this->damage != 0)
	{
		keep_width = hp_w;
		damage_state = false;
		damage_volume = 0.0f;
	}
}

void	HpUI::SetMaxHp(int max_hp)
{
	this->max_hp = max_hp;
}

//---------------------------------------------------------------------------------------
//	情報取得
//---------------------------------------------------------------------------------------

