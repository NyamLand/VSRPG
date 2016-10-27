
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"DrawShape.h"
#include	"PlayerManager.h"
#include	"Enemy.h"

//***************************************************************
//
//	Enemyクラス
//
//***************************************************************

//------------------------------------------------------------------------------------
//	グローバル
//------------------------------------------------------------------------------------
#define	ANGLEADJUST_SPEED 1.0f


//------------------------------------------------------------------------------------
//	初期化・解放
//------------------------------------------------------------------------------------

	//	コンストラクタ
	Enemy::Enemy( void ):
		targetPos(0.0f, 0.0f, 0.0f), active(false), eraseOK(false),
		interpolationParam(0.0f)
	{

	}

	//	デストラクタ
	Enemy::~Enemy( void )
	{

	}


//	解放

//------------------------------------------------------------------------------------
//	更新・描画
//------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------
//	動作関数
//------------------------------------------------------------------------------------
	//	移動
	void	Enemy::Move(float speed,float length)
	{
		if (DistCheck(length)){
			//	プレイヤーの方を向く
			FacingPlayer();

			//	向いてる方向に前進
			Advance(speed);
		}
		else{
			//	モーション設定
			SetMotion(1);	//	待機モーション
		}
	}

	//	プレイヤーの方を向く
	void	Enemy::FacingPlayer(void)
	{
		//	プレイヤーへのベクトルを求める
		Vector3	targetVec = playerManager->GetPlayer()->GetPos() - pos;
		targetVec.Normalize();

		AngleAdjust(targetVec, ANGLEADJUST_SPEED);
	}

	//	前進
	void	Enemy::Advance(float	speed)
	{
		//SetMove(Vector3(sinf(angle), 0.0f, cosf(angle)) * speed);
		SetMotion(1);
		Vector3	moveVec = Vector3(sinf(angle), 0.0f, cosf(angle));
		SetMove(moveVec * speed);
	}

	//	プレイヤーとの距離チェック
	bool	Enemy::DistCheck(float	length)
	{
		Vector3	vec = playerManager->GetPlayer()->GetPos() - pos;
		float	len = vec.Length();

		//	一定の距離まで近づくと攻撃
		if (len <= length)
		{
			return true;
		}
		return false;
	}

	//	ライフチェック（ ０以下なら死亡モードに移行 ）
	/*void	Enemy::LifeCheck(void)
	{
		if (!active)	return;

		if (charaLife->GetLife() <= 0)
		{
			active = false;
			charaMode->SetMode(charaMode->DEATH);
		}
	}*/
//------------------------------------------------------------------------------------
//	動作関数
//------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
//	情報設定
//------------------------------------------------------------------------------------
	//	ターゲットの位置を設定
	void	Enemy::SetTargetPos(const Vector3& pos)
	{
		targetPos = pos;
	}

	//	アクティブ状態取得
	bool	Enemy::GetActive(void)const
	{
		return	active;
	}

	//	消去可能状態取得
	bool	Enemy::GetEraseOK(void)const
	{
		return	eraseOK;
	}

//------------------------------------------------------------------------------------
//	情報取得
//------------------------------------------------------------------------------------
	
