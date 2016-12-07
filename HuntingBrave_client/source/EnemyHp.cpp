
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"GameParam.h"

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
	width = 100.0f;	height = 25.0f;
	id = -1;

}

//	デストラクタ
EnemyHpUI::~EnemyHpUI(void)
{
	SafeDelete(hpFrame_obj);
	SafeDelete(hp_obj);
}


void	EnemyHpUI::Initilaize(int type, float maxhp)
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
void	EnemyHpUI::Render(float hp,const Vector3& pos,const Vector3& up)
{
	
	Vector3	BarPos;
	Vector3	out;
	BarPos = pos + up * 5.0f;
	WorldToClient(BarPos, out, matView * matProjection);
	out.x -= 60;

	float	parsent = (float)hp / (float)maxHp;
	//----------------------
	//	HPバー
	//----------------------
	switch (mode_type)
	{
	case HPUI_TYPE::ENEMY:

		hpFrame_obj->Render(out.x, out.y, (int)width, (int)height, 0, 0, HP_MAX::WIDTH, HP_MAX::HEIGHT);	//	フレーム
		hp_obj->Render(out.x, out.y, (int)(width*parsent), (int)height, 0, HP_MAX::HEIGHT * 1,(int)( (float)HP_MAX::WIDTH*parsent), HP_MAX::HEIGHT);		//	HP残量
		break;

	case HPUI_TYPE::PLAYER:

		if (gameParam->GetMyIndex() == id)break;
		hpFrame_obj->Render(out.x, out.y, (int)width, (int)height, 0, HP_MAX::HEIGHT * 3, HP_MAX::WIDTH, HP_MAX::HEIGHT);	//	フレーム
		hp_obj->Render(out.x, out.y, (int)(width*parsent), (int)height, 0, HP_MAX::HEIGHT * 4, (int)((float)HP_MAX::WIDTH*parsent), HP_MAX::HEIGHT);		//	HP残量
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
void	EnemyHpUI::SetId(int id)
{
	this->id = id;
}
//---------------------------------------------------------------------------------------
//	情報取得
//---------------------------------------------------------------------------------------

