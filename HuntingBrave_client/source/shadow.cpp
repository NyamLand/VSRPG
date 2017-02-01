
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"DrawShape.h"
#include	"Interpolation.h"
#include	"Sound.h"
#include	"PlayerManager.h"
#include	"Random.h"

#include	"Shadow.h"

//***************************************************************
//
//	SmallEnemyクラス
//
//***************************************************************

//------------------------------------------------------------------------------------
//	グローバル
//------------------------------------------------------------------------------------

//	シャドウ
#define	Shadow_SCALE		0.1f
#define	Shadow_HEIGHT	0.125f
#define	Shadow_RADIUS	1.0f

//	動作スピード
#define	ANGLE_ADJUST_SPEED	0.3f
#define	MOVE_SPEED		0.2f

//	その他パラメータ
#define	ATTACK_DIST		5.0f
#define	SEARCH_DIST	10.0f



namespace
{
	namespace MOTION_FRAME
	{
		const int ATTACK_HIT_START = 140;
		const int ATTACK_HIT_END = 161;
		const int DEAD_START = 240;
		const int FALL_END = 291;
	}

}

//------------------------------------------------------------------------------------
//	初期化・解放
//------------------------------------------------------------------------------------

//	コンストラクタ
Shadow::Shadow(void)
{
	ModeFunction[MODE::ENTRY] = &Shadow::EntryMode;
	ModeFunction[MODE::WAIT] = &Shadow::WaitMode;
	ModeFunction[MODE::MOVE] = &Shadow::MoveMode;
	ModeFunction[MODE::ATTACK] = &Shadow::AttackMode;
	ModeFunction[MODE::DAMAGE] = &Shadow::DamageMode;
	ModeFunction[MODE::DEAD] = &Shadow::DeadMode;

	//	変数初期化
	speed = MOVE_SPEED;
	searchDist = SEARCH_DIST;
	attackDist = ATTACK_DIST;
	lifeInfo.active = false;
	lifeInfo.isAlive = true;
	enemyType = ENEMY_TYPE::SHADOW;
}

//	デストラクタ
Shadow::~Shadow(void)
{

}

//	初期化
bool	Shadow::Initialize(int life)
{
	SetMode(MODE::ENTRY);
	SetAngle(0.0f);
	SetScale(0.0f);
	SetMotion(1);	//	数値仮

	//	ライフ初期化
	lifeInfo.Initialize(life);

	//	攻撃情報初期化
	ZeroMemory(&attackInfo, sizeof(AttackInfo));

	//	当たり判定情報初期化
	collisionInfo.Set(SHAPE_TYPE::CAPSULE, Shadow_HEIGHT, Shadow_RADIUS);

	//	HPバー初期化
	bar = new EnemyHpUI();
	bar->Initilaize(HPUI_TYPE::ENEMY, GetLifeInfo().maxLife);

	//	情報更新
	UpdateInfo();

	if (obj == nullptr)	return	false;
	return	true;
}

//------------------------------------------------------------------------------------
//	更新・描画
//-----------------------------------------------------------------------------------

//	更新
void	Shadow::Update(void)
{
	//	各モードに応じた動作関数
	(this->*ModeFunction[mode])();

	BaseChara::Update();
}


//------------------------------------------------------------------------------------
//	動作関数
//------------------------------------------------------------------------------------

//	出現時モード動作
void	Shadow::EntryMode(void)
{
	//	補間
	bool	expantion = Interpolation::LinearInterpolation(
		scale, 0.0f, Shadow_SCALE, interpolationParam);

	//	補間パラメータ更新
	Interpolation::PercentageUpdate(interpolationParam, 0.01f);

	//	補間終了後移動
	if (expantion)
	{
		lifeInfo.active = true;
		SetMode(MODE::MOVE);
	}
}

//	移動モード動作
void	Shadow::MoveMode(void)
{
	//	移動
	Move(speed);
}

//	攻撃モード動作
void	Shadow::AttackMode(void)
{
	SetMotion(2);

	//	フレーム取得
	int frame = obj->GetFrame();

	//	フレーム制御
	if (frame >= MOTION_FRAME::ATTACK_HIT_START
		&& frame <= MOTION_FRAME::ATTACK_HIT_END)
	{
		//	攻撃状態を有効にする
		attackInfo.Set(SHAPE_TYPE::SPHERE, Shadow_RADIUS, pos + (GetFront() * Shadow_RADIUS), Vector3(0, 0, 0));
		attackInfo.attackParam = ATTACK_PARAM::ATTACK1;
	}
	else
	{
		//	攻撃状態を無効にする
		attackInfo.attackParam = ATTACK_PARAM::NO_ATTACK;

		//	通常モードへ移行
		if (frame >= 170)
			SetMode(MODE::WAIT);
	}
}

void	Shadow::DeadMode(void)
{
	SetMotion(4);
	static float alpha = 1.0f;

	//	フレーム取得
	int frame = obj->GetFrame();

	//	フレーム制御
	if (frame >= MOTION_FRAME::DEAD_START)
	{
		//	透過開始
		alpha -= 0.1f;
		if (frame>MOTION_FRAME::FALL_END)
		{
			alpha = 1.0f;
			lifeInfo.isAlive = false;
			sound->PlaySE(SE::ENEMY_DEAD);
		}
	}

}
//------------------------------------------------------------------------------------
//	動作関数
//------------------------------------------------------------------------------------

//	攻撃
void	Shadow::Attack(void)
{

}

//------------------------------------------------------------------------------------
//	情報設定
//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
//	情報取得
//------------------------------------------------------------------------------------

