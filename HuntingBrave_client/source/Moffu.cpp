
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"DrawShape.h"
#include	"Interpolation.h"
#include	"Sound.h"
#include	"PlayerManager.h"
#include	"Random.h"

#include	"Moffu.h"

//***************************************************************
//
//	SmallEnemyクラス
//
//***************************************************************

//------------------------------------------------------------------------------------
//	グローバル
//------------------------------------------------------------------------------------

//	モッフ
#define	MOFFU_SCALE		0.1f
#define	MOFFU_HEIGHT	0.125f
#define	MOFFU_RADIUS	1.0f

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
		const int ATTACK_HIT_START = 138;
		const int ATTACK_HIT_END = 150;
		const int DEAD_START = 225;
		const int FALL_END = 493;
	}

	namespace MOFUMOFU
	{
		const LPSTR mofooTex0[] =
		{
			"DATA/CHR/Enemy/mofumofu/mofoo.png",
			"DATA/CHR/Enemy/mofumofu/ao_mofoo.png",
			"DATA/CHR/Enemy/mofumofu/metaru_mofoo.png",
			"DATA/CHR/Enemy/mofumofu/yuki_mofoo.png"
		};

		const LPSTR mofooTex1[] =
		{
			"DATA/CHR/Enemy/mofumofu/mofoo_trans.png",
			"DATA/CHR/Enemy/mofumofu/ao_mofoo_trans.png",
			"DATA/CHR/Enemy/mofumofu/metaru_mofoo_trans.png",
			"DATA/CHR/Enemy/mofumofu/yuki_mofoo_trans.png"
		};

		enum MOFU_TYPE
		{
			NORMAL_MOFU,
			AO_MOFU,
			METARU_MOFU,
			YUKI_MOFU,
			MOFU_MAX
		};
	}
}

//------------------------------------------------------------------------------------
//	初期化・解放
//------------------------------------------------------------------------------------

	//	コンストラクタ
	Moffu::Moffu( void ) 
	{
		ModeFunction[MODE::ENTRY] = &Moffu::EntryMode;
		ModeFunction[MODE::WAIT] = &Moffu::WaitMode;
		ModeFunction[MODE::MOVE] = &Moffu::MoveMode;
		ModeFunction[MODE::ATTACK] = &Moffu::AttackMode;
		ModeFunction[MODE::DAMAGE] = &Moffu::DamageMode;
		ModeFunction[MODE::DEAD] = &Moffu::DeadMode;

		//	変数初期化
		speed = MOVE_SPEED;
		searchDist = SEARCH_DIST;
		attackDist = ATTACK_DIST;
		lifeInfo.active = false;
		lifeInfo.isAlive = true;
		enemyType = ENEMY_TYPE::MOFFU;
	}

	//	デストラクタ
	Moffu::~Moffu(void)
	{

	}

	//	初期化
	bool	Moffu::Initialize( int life )
	{
		SetMode( MODE::ENTRY );
		SetAngle( 0.0f );
		SetScale( 0.0f );
		SetMotion( 1 );	//	数値仮

		//	ライフ初期化
		lifeInfo.Initialize( life );

		//	攻撃情報初期化
		ZeroMemory( &attackInfo, sizeof( AttackInfo ) );

		//	当たり判定情報初期化
		collisionInfo.Set( SHAPE_TYPE::CAPSULE, MOFFU_HEIGHT, MOFFU_RADIUS );

		//	HPバー初期化
		bar = new EnemyHpUI();
		bar->Initilaize( HPUI_TYPE::ENEMY, GetLifeInfo().maxLife );
		
		//	テクスチャ差し替え
		texType = random->GetInt( 0, MOFUMOFU::MOFU_MAX - 1 );

		//	情報更新
		UpdateInfo();

		if ( obj == nullptr )	return	false;
		return	true;
	}

//------------------------------------------------------------------------------------
//	更新・描画
//-----------------------------------------------------------------------------------

	//	更新
	void	Moffu::Update(void)
	{
		//	各モードに応じた動作関数
		( this->*ModeFunction[mode] )();

		BaseChara::Update();
	}

	//	描画
	void	Moffu::Render(iexShader* shader, LPSTR technique)
	{
		//	情報更新
		obj->SetTexture( 0, MOFUMOFU::mofooTex0[texType] );
		obj->SetTexture( 1, MOFUMOFU::mofooTex1[texType] );

		//	描画
		BaseChara::Render( shader, technique );
	}

//------------------------------------------------------------------------------------
//	動作関数
//------------------------------------------------------------------------------------

	//	出現時モード動作
	void	Moffu::EntryMode(void)
	{
		//	補間
		bool	expantion = Interpolation::LinearInterpolation(
			scale, 0.0f, MOFFU_SCALE, interpolationParam );

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
	void	Moffu::MoveMode(void)
	{
		//	移動
		Move( speed );
	}

	//	攻撃モード動作
	void	Moffu::AttackMode(void)
	{
		SetMotion( 2 );

		//	フレーム取得
		int frame = obj->GetFrame();

		//	フレーム制御
		if ( frame >= MOTION_FRAME::ATTACK_HIT_START 
			&& frame <= MOTION_FRAME::ATTACK_HIT_END )
		{
			//	攻撃状態を有効にする
			attackInfo.Set(SHAPE_TYPE::SPHERE, MOFFU_RADIUS, pos + (GetFront() * MOFFU_RADIUS), Vector3(0, 0, 0));
			attackInfo.attackParam = ATTACK_PARAM::ATTACK1;
		}
		else
		{
			//	攻撃状態を無効にする
			attackInfo.attackParam = ATTACK_PARAM::NO_ATTACK;

			//	通常モードへ移行
			if (frame >= 170)
				SetMode( MODE::WAIT );
		}
	}

	void	Moffu::DeadMode(void)
	{
		SetMotion(3);
		static float alpha = 1.0f;

		//	フレーム取得
		int frame = obj->GetFrame();

		//	フレーム制御
		if ( frame >= MOTION_FRAME::DEAD_START )
		{
			//	透過開始
			alpha -= 0.1f;
			if ( alpha <= 0.0f )
			{
				lifeInfo.isAlive = false;
				sound->PlaySE(SE::ENEMY_DEAD);
			}
		}
		
	}
//------------------------------------------------------------------------------------
//	動作関数
//------------------------------------------------------------------------------------

	//	攻撃
	void	Moffu::Attack(void)
	{

	}
	
//------------------------------------------------------------------------------------
//	情報設定
//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
//	情報取得
//------------------------------------------------------------------------------------

