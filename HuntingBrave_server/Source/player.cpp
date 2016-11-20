
#include	"iextreme.h"
#include	<vector>
#include	"GameParam.h"
#include	"InputManager.h"
#include	"MagicManager.h"
#include	"Player.h"

//*****************************************************************************************************************************
//
//	Playerクラス
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

//	定数
#define	CHANT_TIME	2

//	入力情報
#define	MIN_INPUT_STICK		0.3f

//	動作スピード
#define	ANGLE_ADJUST_MOVE_SPEED		0.3f
#define	MOVE_SPEED		0.2f

namespace
{
	namespace MOTION_FRAME
	{
		const int SWORDATTACK_HIT_START = 140;
		const int SWORDATTACK_HIT_END = 150;
		const int SWORDATTACK1_END = 160;
		const int MAGICCHANT_END = 290;
		const int MAGICACTIVATION = 340;
		const int MAGICATTACK_END = 370;
		const int KNOCKBACK1_END = 405;
	}

	namespace ATTACK_STEP
	{
		enum
		{
			CHANT_START,
			CHANT,
			ACTIVATION,
		};
	}
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
		ModeFunction[MODE::DAMAGE] = &Player::ModeDamage;
		ModeFunction[MODE::MAGICATTACK] = &Player::ModeMagicAttack;
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

		//	モード別動作関数
		( this->*ModeFunction[mode] )();

		//	計算後情報反映
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

		//	入力チェック
		CheckInput();
	}

	//	剣攻撃
	void	Player::ModeSwordAttack( void )
	{
		SwordAttack();
	}

	//	魔法攻撃
	void	Player::ModeMagicAttack( void )
	{
		switch ( gameParam->GetAttackInfo( index ).step )
		{
		case ATTACK_STEP::CHANT_START:
			MagicChantStart();
			break;

		case ATTACK_STEP::CHANT:
			MagicChant();
			break;

		case ATTACK_STEP::ACTIVATION:
			MagicAttack();
			break;
		}
	}

	//	ダメージ
	void	Player::ModeDamage( void )
	{
		Damage();
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

			SetMotion( PLAYER_MOTION::RUN );
		}
		else
		{
			SetMotion( PLAYER_MOTION::POSUTURE );
		}
	}

	//	剣攻撃
	void	Player::SwordAttack( void )
	{
		//	フレーム管理
		if ( pParam.frame >= MOTION_FRAME::SWORDATTACK_HIT_START &&
			pParam.frame <= MOTION_FRAME::SWORDATTACK_HIT_END )
		{
			gameParam->GetAttackInfo( index ).attackParam = AttackInfo::ATTACK1;
		}
		else
		{
			gameParam->GetAttackInfo( index ).attackParam = AttackInfo::NO_ATTACK;
		}

		// 一定以上のフレームに達すると移動に戻す
		if ( pParam.frame >= MOTION_FRAME::SWORDATTACK1_END )
		{
			SetMode( MODE::MOVE );
			gameParam->GetAttackInfo( index ).Reset();
		}
	}

	//	魔法攻撃
	void	Player::MagicAttack( void )
	{
		if ( pParam.frame == MOTION_FRAME::MAGICACTIVATION )
		{
			magicManager->Append( index, 
				gameParam->GetAttackInfo( index ).collisionShape.sphere.center,
				Vector3( 0.0f, 0.0f, 0.0f ) );
		}

		if ( pParam.frame >= MOTION_FRAME::MAGICATTACK_END )
		{
			SetMode( MODE::MOVE );
			gameParam->GetAttackInfo( index ).Reset();
		}
	}

	//	魔法詠唱
	void	Player::MagicChant( void )
	{
		//	離したとき発動可能状態なら発動、発動不可なら移動に戻る
		if ( inputManager->GetInputState( index, KEY_TYPE::A, KEY_STATE::UP ) )
		{
			//	タイマー更新
			bool	chantState = gameParam->GetAttackInfo( index ).timer.Update();

			if ( chantState )
			{
				SetMotion( PLAYER_MOTION::MAGIC_ACTIVATION );
				gameParam->GetAttackInfo( index ).step = ATTACK_STEP::ACTIVATION;
			}
			else
			{
				//	移動に戻る（パラメータリセット）
				SetMode( MODE::MOVE );
				gameParam->GetAttackInfo( index ).Reset();
			}
		}
	}

	//	魔法詠唱開始
	void	Player::MagicChantStart( void )
	{
		//	押している間詠唱、一定時間経過で発動可能
		if ( inputManager->GetInputState( index, KEY_TYPE::A, KEY_STATE::STAY ) )
		{
			if ( pParam.frame >= MOTION_FRAME::MAGICCHANT_END )
			{
				SetMotion( PLAYER_MOTION::MAGIC_CHANT );
				gameParam->GetAttackInfo( index ).timer.Start( CHANT_TIME );
				gameParam->GetAttackInfo( index ).step = ATTACK_STEP::CHANT;
			}
		}
		else
		{
			//	移動に戻る（ パラメータリセット ）
			SetMode( MODE::MOVE );
			gameParam->GetAttackInfo( index ).Reset();
		}
	}

	//	ダメージ
	void	Player::Damage( void )
	{
		gameParam->GetLifeInfo( index ).active = false;
		SetMotion( PLAYER_MOTION::KNOCKBACK1 );

		if ( pParam.frame >= MOTION_FRAME::KNOCKBACK1_END )
		{
			gameParam->GetLifeInfo( index ).active = true;
			SetMode( MODE::MOVE );
		}
	}

	//	入力チェック
	void	Player::CheckInput( void )
	{
		//	剣攻撃入力受付
		if ( inputManager->GetInputState( index, KEY_TYPE::B, KEY_STATE::ENTER ) )
		{
			if ( SetMode( MODE::SWOADATTACK ) )
			{
				SetMotion( PLAYER_MOTION::ATTACK1 );
				return;
			}
		}

		//	魔法攻撃入力受付
		if ( inputManager->GetInputState( index, KEY_TYPE::A, KEY_STATE::ENTER ) )
		{
			if ( SetMode( MODE::MAGICATTACK ) )
			{
				SetMotion( PLAYER_MOTION::MAGIC_CHANT_START );
				return;
			}
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

