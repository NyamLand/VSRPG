
#include	"iextreme.h"
#include	"GameParam.h"

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
#define	MOVE_SPEED	20.0f

//------------------------------------------------------------------------------------
//	初期化・解放
//------------------------------------------------------------------------------------

	//	コンストラクタ
	Enemy::Enemy( void ): timer( nullptr ),
		targetPos( 0.0f, 0.0f, 0.0f ), move( 0.0f, 0.0f, 0.0f ),
		interpolationParam( 0.0f ), searchDist( 0.0f ), attackDist( 0.0f ), count( 40 ),
		alive( true )
	{
		ZeroMemory( &lifeInfo, sizeof( lifeInfo ) );
		ZeroMemory( &enemyParam, sizeof( enemyParam ) );
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

//------------------------------------------------------------------------------------
//	動作関数
//------------------------------------------------------------------------------------
	
	//	移動
	void	Enemy::Move( void )
	{
		Vector3	target;

		//	プレイヤーが感知範囲にいれば行動開始
		if ( DistCheck( target ) )
		{
			//	プレイヤーの方を向く
			AngleAdjust( target, ANGLEADJUST_SPEED );

			//	向いてる方向に前進
			Advance();
		}
	}

	//	前進
	void	Enemy::Advance( void )
	{
		Vector3	moveVec = Vector3( sinf( angle ), 0.0f, cosf( angle ) );
		move = moveVec * MOVE_SPEED;
	}

	//	プレイヤーとの距離チェック
	bool	Enemy::DistCheck( Vector3& target )
	{
		float length = 500.0f;
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			//	非アクティブのプレイヤーはスキップ
			if ( gameParam->GetPlayerActive( i ) )	continue;
			target = gameParam->GetPlayerParam( i ).pos - enemyParam.pos;

			//	とりあえず一番近い人の長さを保存
			if ( target.Length() < length )
			{
				length = target.Length();
			}
		}
		target.Normalize();

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
	void	Enemy::AddMove( void )
	{
		enemyParam.pos += move * timer->GetErapseTime();
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
//	動作関数
//------------------------------------------------------------------------------------
	
	//	更新
	void	Enemy::Update( void )
	{
		//	通常移動
		Move();

		//	移動値加算
		AddMove();
	}

//------------------------------------------------------------------------------------
//	モード関数
//------------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------------
//	情報取得
//------------------------------------------------------------------------------------

	int	Enemy::GetMode( void )const
	{
		return mode;
	}

	bool	Enemy::GetAlive( void )const
	{
		return	alive;
	}