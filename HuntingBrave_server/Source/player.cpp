
#include	"iextreme.h"
#include	"InputManager.h"
#include	"Player.h"

//*****************************************************************************************************************************
//
//	Playerクラス
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

//	初期パラメータ
#define	INIT_LIFE		5

//	入力情報
#define	MIN_INPUT_STICK		0.3f

//	動作スピード
#define	ANGLE_ADJUST_MOVE_SPEED		0.3f
#define	MOVE_SPEED		0.2f

//	定数関連
namespace
{
	//	モーション番号
	enum MOTION_NUM
	{
		POSUTURE,						//	待機
		RUN_START,						//	走り出し
		RUN,									//	走り
		ATTACK1,							//	攻撃１
		ATTACK2,							//	攻撃２
		STEP,								//	ステップ
		MAGIC_CHANT_START,		//	詠唱開始
		MAGIC_CHANT,					//	詠唱中
		MAGIC_ACTUATION,			//	魔法発動
		KNOCKBACK1,					//	仰け反り１
		KNOCKBACK2,					//	仰け反り２
		FALL,									//	倒れる
		DEAD,								//	死亡
		EAT,									//	食べる
		MENU_OPEN,						//	メニューを開く
		MENU,								//	メニュー操作中
		LEVEL_UP,							//	レベルアップ
		MENU_CLOSE,					//	メニューを閉じる
		WIN,									//	勝利
		WIN_KEEP,						//	勝利キープ
		CRY									//	泣き
	};
}

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	Player::Player( int id ) : 
		index( id )
	{
		ZeroMemory( &pParam, sizeof( PlayerParam ) );

		//	関数ポインタ設定
		ModeFunction[MODE::MOVE] = &Player::ModeMove;
		ModeFunction[MODE::SWOADATTACK] = &Player::ModeSwordAttack;

		//	体力初期化
		lifeInfo.Initialize( INIT_LIFE );
		lifeInfo.active = true;
	}

	//	デストラクタ
	Player::~Player( void )
	{
		
	}

//----------------------------------------------------------------------------------------------
//	更新
//----------------------------------------------------------------------------------------------

	//	更新
	bool	Player::Update( PlayerParam& param )
	{
		//	情報受け取り
		pParam = param;
		lifeInfo.life = pParam.life;

		//	モード別動作関数
		( this->*ModeFunction[mode] )();

		//	計算後情報反映
		pParam.life = lifeInfo.life;
		param = pParam;

		return true;
	}

//----------------------------------------------------------------------------------------------
//	モード別動作関数
//----------------------------------------------------------------------------------------------

	//	通常移動
	void	Player::ModeMove( void )
	{
		//	移動
		Move();

		//	入力受付
		if ( inputManager->GetInput( index ).inputType == InputManager::ENTER )
		{
			if( SetMode( MODE::SWOADATTACK ) ) SetMotion( MOTION_NUM::ATTACK1 );
			inputManager->GetInput( index ).inputType = InputManager::NO_INPUT;
		}
	}

	//	剣攻撃
	void	Player::ModeSwordAttack( void )
	{
		SwordAttack();
	}
	
//----------------------------------------------------------------------------------------------
//	動作関数
//----------------------------------------------------------------------------------------------

	//	移動
	void	Player::Move( void )
	{
		float moveX = inputManager->GetInput( index ).axisX;
		float moveZ = inputManager->GetInput( index ).axisY;
		float length = sqrtf( moveX * moveX + moveZ * moveZ );

		//	入力があれば移動処理
		if ( length >= MIN_INPUT_STICK )
		{
			//	向き調整
			AngleAdjust(
				Vector3( moveX, 0.0f, moveZ ),
				ANGLE_ADJUST_MOVE_SPEED );

			//	移動
			pParam.pos += 
				Vector3( sinf( pParam.angle ), 0.0f, cosf( pParam.angle ) ) * MOVE_SPEED;

			SetMotion( MOTION_NUM::RUN );
		}
		else
		{
			SetMotion( MOTION_NUM::POSUTURE );
		}
	}

	//	剣攻撃
	void	Player::SwordAttack( void )
	{
		// 一定以上のフレームに達すると移動に戻す
		if ( pParam.frame >= 190 )
		{
			SetMode( MODE::MOVE );
		}
	}

	//	ダメージ
	void	Player::Damage( void )
	{
		SetMotion( MOTION_NUM::KNOCKBACK1 );
		lifeInfo.active = false;
		if ( pParam.frame >= 465 )
		{
			SetMode( MODE::MOVE );
			lifeInfo.active = true;
		}
	}

	//	向き調整
	void	Player::AngleAdjust( const Vector3& targetVec, float adjustSpeed )
	{
		//	移動方向を求める
		float	moveAngle = atan2f( targetVec.x, targetVec.z );

		//	親に投げる
		AngleAdjustParent(
			Vector3( sinf( moveAngle ), 0.0f, cosf( moveAngle ) ),
			adjustSpeed );
	}

	//	向き調整（親）
	void	Player::AngleAdjustParent( const Vector3& direction, float adjustSpeed )
	{
		//	現在の向きと目標の向きの差を求める
		float	targetAngle( atan2f( direction.x, direction.z ) );

		//	角度差を求める
		float	dAngle( targetAngle - pParam.angle );

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

		pParam.angle = targetAngle - dAngle;

		//	キャラクターの向きがPI以上にならないようにする
		if ( pParam.angle >= 1.0f * D3DX_PI )		pParam.angle -= 2.0f * D3DX_PI;
		if ( pParam.angle <= -1.0f * D3DX_PI )		pParam.angle += 2.0f * D3DX_PI;
	}

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

	//	モーション設定
	void	Player::SetMotion( int motion )
	{
		if ( pParam.motion != motion )
		{
			pParam.motion = motion;
		}
	}

