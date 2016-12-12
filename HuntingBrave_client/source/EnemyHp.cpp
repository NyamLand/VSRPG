
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

namespace
{
	namespace HP_MAX
	{
		enum
		{
			WIDTH = 768,				//	画像横幅
			HEIGHT = 128,				//	画像縦幅
		};
	}
}
//---------------------------------------------------------------------------------------
//	初期化・解放
//---------------------------------------------------------------------------------------

//	コンストラクタ
EnemyHpUI::EnemyHpUI()
{
	//	座標、サイズ情報格納
	width = 100;	height = 25;
	id = -1;

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
void	EnemyHpUI::Render(float hp,const Vector3& pos,const Vector3& up)
{
	
	Vector3	BarPos;
	Vector3	out;
	BarPos = pos + up * 5.0f;
	WorldToClient(BarPos, out, matView * matProjection);
	out.x -= 60;

	float	parsent = (float)hp / (float)maxHp;
	int w = (int)((float)width * parsent);
	int	sx = (int)((float)HP_MAX::WIDTH * parsent);

	//----------------------
	//	HPバー
	//----------------------
	switch (mode_type)
	{
	case HPUI_TYPE::ENEMY:

		hpFrame_obj->Render((int)out.x, (int)out.y, width, height, 0, 0, HP_MAX::WIDTH, HP_MAX::HEIGHT);	//	フレーム
		hp_obj->Render((int)out.x, (int)out.y, w, height, 0, HP_MAX::HEIGHT * 1, sx, HP_MAX::HEIGHT);		//	HP残量
		hpFrame_obj->Render((int)out.x-2, (int)out.y+2, 20, 20, 128, HP_MAX::HEIGHT * 6, 128, 128);	//	フレーム
		break;

	case HPUI_TYPE::PLAYER:

		if (gameParam->GetMyIndex() == id)break;
		hpFrame_obj->Render((int)out.x, (int)out.y, width, height, 0, HP_MAX::HEIGHT * 3, HP_MAX::WIDTH, HP_MAX::HEIGHT);	//	フレーム
		hp_obj->Render((int)out.x, (int)out.y, w, height, 0, HP_MAX::HEIGHT * 4, sx, HP_MAX::HEIGHT);		//	HP残量
		hpFrame_obj->Render((int)out.x, (int)out.y, 20, 20, 0, HP_MAX::HEIGHT * 6, 128, 128);	//	フレーム
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

