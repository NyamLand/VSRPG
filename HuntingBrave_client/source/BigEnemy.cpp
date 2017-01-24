
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"DrawShape.h"
#include	"Interpolation.h"
#include	"BigEnemy.h"

//***************************************************************
//
//	Enemyクラス
//
//***************************************************************

//------------------------------------------------------------------------------------
//	グローバル
//------------------------------------------------------------------------------------

//	モデル情報
#define	MINOTAURUS_SCALE	0.02f
#define	MINOTAURUS_HEIGHT	2.0f
#define	MINOTAURUS_RADIUS	1.5f
#define	INIT_LIFE	 4

//	動作スピード
#define	ANGLE_ADJUST_SPEED	0.3f
#define	MOVE_SPEED		0.15f

//	その他パラメータ
#define	ATTACK_DIST		5.0f
#define	SEARCH_DIST	10.0f

//モーションフレーム
namespace
{
	namespace MOTION_FRAME
	{
		const int ATTACK_HIT_START = 138;
		const int ATTACK_HIT_END = 150;
		const int DEAD_START = 725;
		const int FALL_END = 1000;
	}
}
//------------------------------------------------------------------------------------
//	初期化・解放
//------------------------------------------------------------------------------------

	//	コンストラクタ
	BigEnemy::BigEnemy( void )
	{
		ModeFunction[MODE::ENTRY] = &BigEnemy::EntryMode;
		ModeFunction[MODE::MOVE] = &BigEnemy::MoveMode;
		ModeFunction[MODE::ATTACK] = &BigEnemy::AttackMode;
		ModeFunction[MODE::DAMAGE] = &BigEnemy::DamageMode;
		ModeFunction[MODE::DEAD] = &BigEnemy::DeadMode;
		
		//	変数初期化
		speed = MOVE_SPEED;
		searchDist = SEARCH_DIST;
		attackDist = ATTACK_DIST;
		lifeInfo.isAlive = true;
		lifeInfo.active = false;
	}

	//	デストラクタ
	BigEnemy::~BigEnemy( void )
	{

	}

	//	初期化
	bool	BigEnemy::Initialize( void )
	{
		SetMode( MODE::ENTRY );
		SetAngle( 0.0f );
		SetScale( 0.0f );
		SetMotion( 1 );	//	数値仮
		
		lifeInfo.Initialize( INIT_LIFE );
		ZeroMemory( &attackInfo, sizeof( AttackInfo ) );
		collisionInfo.Set( SHAPE_TYPE::CAPSULE, MINOTAURUS_HEIGHT, MINOTAURUS_RADIUS );

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
	void	BigEnemy::Update( void )
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
	void	BigEnemy::EntryMode( void )
	{
		//	補間
		bool	expantion = Interpolation::LinearInterpolation(
			scale, 0.0f, MINOTAURUS_SCALE, interpolationParam );

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
	void	BigEnemy::MoveMode( void )
	{
		//	移動
		Move( speed );
	}

	//	攻撃モード動作
	void	BigEnemy::AttackMode( void )
	{
		SetMotion( 2 );

		//	フレーム取得
		int frame = obj->GetFrame();

		//	フレーム制御
		if ( frame >= 138 && frame <= 150 )
		{
			//	攻撃状態を有効にする
			attackInfo.Set(SHAPE_TYPE::SPHERE, MINOTAURUS_RADIUS, pos + (GetFront() * MINOTAURUS_RADIUS), Vector3(0, 0, 0));
			attackInfo.attackParam = ATTACK_PARAM::ATTACK1;
		}
		else
		{
			//	攻撃状態を無効にする
			attackInfo.attackParam = ATTACK_PARAM::NO_ATTACK;

			//	通常モードへ移行
			if ( frame >= 170 )
				SetMode( MODE::MOVE );
		}
	}


	void	BigEnemy::DeadMode(void)
	{
		SetMotion(12);
		static float alpha = 1.0f;

		//	フレーム取得
		int frame = obj->GetFrame();

		//	フレーム制御
		if (frame >= MOTION_FRAME::DEAD_START)
		{
			//	透過開始
			alpha -= 0.1f;
			if (alpha <= 0.0f)
			{
				lifeInfo.isAlive = false;
			}
		}
	}
//------------------------------------------------------------------------------------
//	動作関数
//------------------------------------------------------------------------------------

	void	BigEnemy::Attack()
	{

	}

//------------------------------------------------------------------------------------
//	情報設定
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	情報取得
//------------------------------------------------------------------------------------

