
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"DrawShape.h"
#include	"Interpolation.h"
#include	"PlayerManager.h"

#include	"SmallEnemy.h"

//***************************************************************
//
//	SmallEnemyクラス
//
//***************************************************************

//------------------------------------------------------------------------------------
//	グローバル
//------------------------------------------------------------------------------------

//	モデル情報
#define	MINOTAURUS_SCALE	0.01f
#define	INIT_LIFE	1

//	動作スピード
#define	ANGLE_ADJUST_SPEED	0.3f
#define	MOVE_SPEED		0.1f

//	その他パラメータ
#define	ATTACK_DIST		5.0f
#define	SEARCH_DIST	10.0f

//------------------------------------------------------------------------------------
//	初期化・解放
//------------------------------------------------------------------------------------

	//	コンストラクタ
	SmallEnemy::SmallEnemy( void )
	{
		ModeFunction[MODE::ENTRY] = &SmallEnemy::EntryMode;
		ModeFunction[MODE::MOVE] =  &SmallEnemy::MoveMode;
		ModeFunction[MODE::ATTACK] =&SmallEnemy::AttackMode;

		//	変数初期化
		speed = MOVE_SPEED;
		active = false;
		lifeInfo.isAlive = true;
		searchDist = SEARCH_DIST;
		attackDist = ATTACK_DIST;
	}

	//	デストラクタ
	SmallEnemy::~SmallEnemy( void )
	{

	}

	//	初期化
	bool	SmallEnemy::Initialize( void )
	{
		SetMode(MODE::ENTRY);
		SetAngle(0.0f);
		SetScale(0.0f);
		SetMotion(1);	//	数値仮
		rad = 0.1f;
		lifeInfo.Initialize(INIT_LIFE);

		//	情報更新
		UpdateInfo();

		if (obj == nullptr)	return	false;
		return	true;
	}

	//	解放

//------------------------------------------------------------------------------------
//	更新・描画
//-----------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	動作関数
//------------------------------------------------------------------------------------

	//	移動モード動作
	void	SmallEnemy::Update( void )
	{
		//	各モードに応じた動作関数
		(this->*ModeFunction[mode])();

		//	情報更新
		BaseChara::Update();
	}

	//------------------------------------------------------------------------------------
	//	動作関数
	//------------------------------------------------------------------------------------

	//	出現時モード動作
	void	SmallEnemy::EntryMode(void)
	{
		//	補間
		bool	expantion = Interpolation::LinearInterpolation(
			scale, 0.0f, MINOTAURUS_SCALE, interpolationParam);

		//	補間パラメータ更新
		Interpolation::PercentageUpdate(interpolationParam, 0.01f);

		//	補間終了後移動
		if (expantion)
		{
			active = true;
			SetMode(MODE::MOVE);
		}
	}

	//	移動モード動作
	void	SmallEnemy::MoveMode(void)
	{
		//	移動
		Move(speed);
	}

	//	攻撃モード動作
	void	SmallEnemy::AttackMode(void)
	{
		SetMotion(2);

		//	フレーム取得
		int frame = obj->GetFrame();

		//	フレーム制御
		if (frame >= 138 && frame <= 150)
		{
			//	攻撃状態を有効にする
			attackInfo.attackParam = AttackInfo::ATTACK1;
		}
		else
		{
			//	攻撃状態を無効にする
			attackInfo.attackParam = AttackInfo::NO_ATTACK;

			//	通常モードへ移行
			if (frame >= 170)
				SetMode(MODE::MOVE);
		}
	}

	//------------------------------------------------------------------------------------
	//	動作関数
	//------------------------------------------------------------------------------------

	void	SmallEnemy::Attack()
	{

	}
	//------------------------------------------------------------------------------------
	//	情報設定
	//------------------------------------------------------------------------------------

	//------------------------------------------------------------------------------------
	//	情報取得
	//------------------------------------------------------------------------------------

