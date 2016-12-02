
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"


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
EnemyHpUI::EnemyHpUI()
{
	//	座標、サイズ情報格納
	width = 100;	height = 25;

}

//	デストラクタ
EnemyHpUI::~EnemyHpUI(void)
{
	SafeDelete(hpFrame_obj);
	SafeDelete(hp_obj);
}


void	EnemyHpUI::Initilaize(int type, int maxhp)
{
	
	hp = 0;
	//	HPバーフレーム
	hpFrame_obj = new iex2DObj("DATA/UI/main_UI/Enemy_HP.png");

	//	HP残量
	hp_obj = new iex2DObj("DATA/UI/main_UI/Enemy_HP.png");

	mode_type = type;
	maxHp = maxhp;
}

//---------------------------------------------------------------------------------------
//	更新・描画
//---------------------------------------------------------------------------------------

//	更新
void	EnemyHpUI::Update( void )
{
	
	
}

//	描画
void	EnemyHpUI::Render(int hp,Vector3 pos,Vector3 up)
{
	
	Vector3	BarPos;
	Vector3	out;
	BarPos = pos + up * 5.0f;
	WorldToClient(BarPos, out, matView * matProjection);
	out.x -= 60;
	//----------------------
	//	HPバー
	//----------------------
	switch (mode_type)
	{
	case HPUI_TYPE::ENEMY:

		hpFrame_obj->Render(out.x, out.y, width, height, 0, 0, HP_MAX::WIDTH, HP_MAX::HEIGHT);	//	フレーム
		hp_obj->Render(out.x, out.y, width*(hp / maxHp), height, 0, HP_MAX::HEIGHT * 1, HP_MAX::WIDTH, HP_MAX::HEIGHT);		//	HP残量
		break;

	case HPUI_TYPE::PLAYER:

		hpFrame_obj->Render(out.x, out.y, width, height, 0, HP_MAX::HEIGHT * 2, HP_MAX::WIDTH, HP_MAX::HEIGHT);	//	フレーム
		hp_obj->Render(out.x, out.y, width*(hp / maxHp), height, 0, HP_MAX::HEIGHT * 3, HP_MAX::WIDTH, HP_MAX::HEIGHT);		//	HP残量
		break;

	default:

		return;
		break;
	}
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

