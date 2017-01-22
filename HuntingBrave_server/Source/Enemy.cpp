
#include	"iextreme.h"
#include	"GameParam.h"
#include	"GlobalFunction.h"

#include	"Enemy.h"

//***************************************************************
//
//	Enemyクラス
//
//***************************************************************

//------------------------------------------------------------------------------------
//	グローバル
//------------------------------------------------------------------------------------

#define	MINOTAURUS_HEIGHT	2.0f
#define	MINOTAURUS_RADIUS	1.5f

#define	ANGLEADJUST_SPEED 1.0f
#define	MOVE_SPEED	10.0f
#define	SEARCH_DIST	10.0f
#define	ATTACK_DIST	5.0f

namespace
{
	namespace MOTION_NUM
	{
		enum
		{
			POSTURE,	//	待機モーション
			MOVE,			//	移動モーション
			ATTACK,		//	攻撃モーション
		};
	}
}

//------------------------------------------------------------------------------------
//	初期化・解放
//------------------------------------------------------------------------------------

	//	コンストラクタ
	Enemy::Enemy( void ): timer( nullptr ),
		deltaTime( 0.0f ),
		searchDist( SEARCH_DIST ), alive( true )
	{
		//	構造体初期化
		ZeroMemory( &lifeInfo, sizeof( lifeInfo ) );
		ZeroMemory( &enemyParam, sizeof( enemyParam ) );

		//	コリジョン情報設定
		collisionInfo.Set( SHAPE_TYPE::CAPSULE, MINOTAURUS_HEIGHT, MINOTAURUS_RADIUS );
		
		//	タイマー初期化
		timer = new Timer();
	}

	//	デストラクタ
	Enemy::~Enemy( void )
	{
		if ( timer != nullptr )
		{
			delete timer;
			timer = nullptr;
		}
	}

//------------------------------------------------------------------------------------
//	更新・描画
//------------------------------------------------------------------------------------

	//	更新
	void	Enemy::Update( float deltaTime )
	{
		this->deltaTime = deltaTime;

		//	通常移動
		Move();
	}

//------------------------------------------------------------------------------------
//	動作関数
//------------------------------------------------------------------------------------
	
	//	移動
	void	Enemy::Move( void )
	{
		Vector3	target = Vector3( 0.0f, 0.0f, 0.0f );
		bool	atkFlag = false;

		//	プレイヤーが感知範囲にいれば行動開始
		if ( DistCheck( target, atkFlag ) )
		{
			if ( !atkFlag )
			{
				//	プレイヤーの方を向く
				target.Normalize();
				AngleAdjust( target, ANGLEADJUST_SPEED );

				//	向いてる方向に前進
				Advance();
			}
			else
			{
				//	攻撃時
				SetMotion( MOTION_NUM::ATTACK );
			}
		}
		else
		{
			//	待機モーション
			SetMotion( MOTION_NUM::POSTURE );
		}
	}

	//	前進
	void	Enemy::Advance( void )
	{
		SetMotion( MOTION_NUM::MOVE );
		Vector3	moveVec = Vector3( sinf( enemyParam.angle ), 0.0f, cosf( enemyParam.angle ) );
		AddMove( moveVec * MOVE_SPEED );
	}

	//	プレイヤーとの距離チェック
	bool	Enemy::DistCheck( Vector3& target, bool& attackFlag )
	{
		float length = 500.0f;
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			//	非アクティブのプレイヤーはスキップ
			if ( gameParam->GetPlayerActive( i ) == false )	continue;
			target = gameParam->GetPlayerParam( i ).pos - enemyParam.pos;

			//	とりあえず一番近い人の長さを保存
			if ( target.Length() < length )
			{
				length = target.Length();
			}
		}
		target.Normalize();

		//	攻撃フラグ設定
		if ( length <= ATTACK_DIST )	attackFlag = true;
		else attackFlag = false;

		//	一定の距離まで近づくと感知
		if ( length <= searchDist )	return	true;
		return false;
	}

	//	ライフチェック（ ０以下なら死亡モードに移行 ）
	void	Enemy::LifeCheck( void )
	{
		if ( !lifeInfo.active )	return;

		if ( lifeInfo.life <= 0 )
		{
			lifeInfo.active = false;
			SetMode( MODE::DEAD );
		}
	}
	
	//	移動値加算
	void	Enemy::AddMove( const Vector3& move )
	{
		enemyParam.pos += move * deltaTime;
	}

	//	向き調整（ カメラ影響なし ）
	void	Enemy::AngleAdjust( const Vector3& moveVec, float adjustSpeed )
	{
		//	移動方向を求める
		float	moveAngle = atan2f( moveVec.x, moveVec.z );

		//	親に投げる
		AngleAdjustParent(
			Vector3( sinf( moveAngle ), 0.0f, cosf( moveAngle ) ),
			adjustSpeed );
	}

	//	向き調整（親）
	void	Enemy::AngleAdjustParent( const Vector3& direction, float adjustSpeed )
	{
		//	現在の向きと目標の向きの差を求める
		float	targetAngle( atan2f( direction.x, direction.z ) );

		//	角度差を求める
		float	dAngle( targetAngle - enemyParam.angle );

		//	差の正規化
		if ( dAngle > 1.0f * D3DX_PI )		dAngle -= 2.0f * D3DX_PI;
		if ( dAngle < -1.0f * D3DX_PI )	dAngle += 2.0f * D3DX_PI;

		//	差をspeed分縮める
		if ( dAngle > 0.0f )
		{
			dAngle -= adjustSpeed;
			if ( dAngle < 0.0f )	dAngle = 0.0f;
		}
		else
		{
			dAngle += adjustSpeed;
			if ( dAngle > 0.0f )	dAngle = 0.0f;
		}

		enemyParam.angle = targetAngle - dAngle;

		//	キャラクターの向きがPI以上にならないようにする
		if ( enemyParam.angle >= 1.0f * D3DX_PI )  		enemyParam.angle -= 2.0f * D3DX_PI;
		if ( enemyParam.angle <= -1.0f * D3DX_PI )		enemyParam.angle += 2.0f * D3DX_PI;
	}

//------------------------------------------------------------------------------------
//	情報設定
//------------------------------------------------------------------------------------

	//	座標設定
	void	Enemy::SetPos( const Vector3& pos )
	{
		enemyParam.pos = pos;
	}

	//	向き設定
	void	Enemy::SetAngle( float angle )
	{
		enemyParam.angle = angle;
	}

	//	モーション設定
	void	Enemy::SetMotion( int motion )
	{
		if ( enemyParam.motion != motion )
		{
			enemyParam.motion = motion;
		}
	}

//------------------------------------------------------------------------------------
//	情報取得
//------------------------------------------------------------------------------------

	//	座標取得
	Vector3	Enemy::GetPos( void )const
	{
		return	enemyParam.pos;
	}

	//	方向取得
	float			Enemy::GetAngle( void )const
	{
		return	enemyParam.angle;
	}

	//	モーション取得
	int			Enemy::GetMotion( void )const
	{
		return	enemyParam.motion;
	}

	int	Enemy::GetMode( void )const
	{
		return mode;
	}

	bool	Enemy::GetAlive( void )const
	{
		return	alive;
	}