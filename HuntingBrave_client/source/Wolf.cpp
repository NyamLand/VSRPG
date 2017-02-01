
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"DrawShape.h"
#include	"Sound.h"
#include	"Interpolation.h"
#include	"Wolf.h"

//***************************************************************
//
//	Enemyクラス
//
//***************************************************************

//------------------------------------------------------------------------------------
//	グローバル
//------------------------------------------------------------------------------------

//	モデル情報
#define	WOLF_SCALE	0.1f
#define	WOLF_HEIGHT	2.0f
#define	WOLF_RADIUS	2.0f

//	動作スピード
#define	ANGLE_ADJUST_SPEED	0.3f
#define	MOVE_SPEED		0.18f

//	その他パラメータ
#define	ATTACK_DIST		5.0f
#define	SEARCH_DIST	10.0f

//モーションフレーム
namespace
{
	namespace MOTION_FRAME
	{
		const int ATTACK_HIT_START = 195;
		const int ATTACK_HIT_END = 240;
		const int DEAD_START = 321;
		const int FALL_END = 335;
	}
}
//------------------------------------------------------------------------------------
//	初期化・解放
//------------------------------------------------------------------------------------

	//	コンストラクタ
	Wolf::Wolf(void)
	{
		ModeFunction[MODE::ENTRY] = &Wolf::EntryMode;
		ModeFunction[MODE::WAIT] = &Wolf::WaitMode;
		ModeFunction[MODE::MOVE] = &Wolf::MoveMode;
		ModeFunction[MODE::ATTACK] = &Wolf::AttackMode;
		ModeFunction[MODE::DAMAGE] = &Wolf::DamageMode;
		ModeFunction[MODE::DEAD] = &Wolf::DeadMode;
		
		//	変数初期化
		speed = MOVE_SPEED;
		searchDist = SEARCH_DIST;
		attackDist = ATTACK_DIST;
		lifeInfo.isAlive = true;
		lifeInfo.active = false;
		enemyType = ENEMY_TYPE::WOLF;
	}

	//	デストラクタ
	Wolf::~Wolf(void)
	{

	}

	//	初期化
	bool	Wolf::Initialize( int life )
	{
		SetMode( MODE::ENTRY );
		SetAngle( 0.0f );
		SetScale( 0.0f );
		SetMotion( 1 );	//	数値仮
		
		lifeInfo.Initialize( life );
		ZeroMemory( &attackInfo, sizeof( AttackInfo ) );
		collisionInfo.Set(SHAPE_TYPE::CAPSULE, WOLF_HEIGHT, WOLF_RADIUS);

		bar = new EnemyHpUI();
		bar->Initilaize(HPUI_TYPE::ENEMY, GetLifeInfo().maxLife);
		//	情報更新
		UpdateInfo();

		if ( obj == nullptr )	return	false;
		return	true;
	}

	//	解放

//------------------------------------------------------------------------------------
//	更新・描画
//------------------------------------------------------------------------------------

	//	更新
	void	Wolf::Update(void)
	{
		//	各モードに応じた動作関数
		( this->*ModeFunction[mode] )();

		//	情報更新
		BaseChara::Update();
	}

//------------------------------------------------------------------------------------
//	動作関数
//------------------------------------------------------------------------------------

	//	出現時モード動作
	void	Wolf::EntryMode(void)
	{
		//	補間
		bool	expantion = Interpolation::LinearInterpolation(
			scale, 0.0f, WOLF_SCALE, interpolationParam);

		//	補間パラメータ更新
		Interpolation::PercentageUpdate( interpolationParam, 0.01f );

		//	補間終了後移動
		if ( expantion )
		{
			lifeInfo.active = true;
			SetMode( MODE::MOVE );
		}
	}

	//	移動モード動作
	void	Wolf::MoveMode(void)
	{
		//	移動
		Move( speed );
	}

	//	攻撃モード動作
	void	Wolf::AttackMode(void)
	{
		SetMotion( 2 );

		//	フレーム取得
		int frame = obj->GetFrame();

		//	フレーム制御
		if ( frame >= MOTION_FRAME::ATTACK_HIT_START 
			&& frame <= MOTION_FRAME::ATTACK_HIT_END )
		{
			//	攻撃状態を有効にする
			attackInfo.Set(SHAPE_TYPE::SPHERE, WOLF_RADIUS, pos + (GetFront() * WOLF_RADIUS), Vector3(0, 0, 0));
			attackInfo.attackParam = ATTACK_PARAM::ATTACK1;
		}
		else
		{
			//	攻撃状態を無効にする
			attackInfo.attackParam = ATTACK_PARAM::NO_ATTACK;

			//	通常モードへ移行
			if (frame >= 245)
				
				SetMode( MODE::WAIT );
		}
	}


	void	Wolf::DeadMode(void)
	{
		SetMotion(3);
		static float alpha = 1.0f;

		//	フレーム取得
		int frame = obj->GetFrame();

		//	フレーム制御
		if (frame >= MOTION_FRAME::DEAD_START)
		{
			//	透過開始
			alpha -= 0.1f;
			if ( frame >= MOTION_FRAME::FALL_END )
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

	void	Wolf::Attack()
	{

	}

//------------------------------------------------------------------------------------
//	情報設定
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	情報取得
//------------------------------------------------------------------------------------

