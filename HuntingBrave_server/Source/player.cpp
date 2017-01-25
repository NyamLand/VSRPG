
#include	"iextreme.h"
#include	<vector>
#include	<map>
#include	"GameParam.h"
#include	"GameManager.h"
#include	"InputManager.h"
#include	"MagicManager.h"
#include	"Collision.h"
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
#define	CHANT_TIME	1.0f
#define	DEATH_TIME	3.0f
#define	STEP_DRAG		0.97f

//	入力情報
#define	MIN_INPUT_STICK		0.3f

//	動作スピード
#define	ANGLE_ADJUST_MOVE_SPEED		0.3f
#define	MOVE_SPEED		0.2f
#define	STEP_SPEED		0.5f

namespace
{
	namespace SUPPIN_FRAME
	{
		const int SWORDATTACK_HIT_START = 140;
		const int SWORDATTACK_HIT_END = 150;
		const int SWORDATTACK1_END = 160;
		const int STEP_END = 260;
		const int MAGICCHANT_END = 290;
		const int MAGICACTIVATION = 340;
		const int MAGICATTACK_END = 370;
		const int KNOCKBACK1_END = 405;
		const int FALL_END = 493;
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
	namespace
	{
		namespace FRAME_TYPE
		{
			enum
			{
				ATTACK_HIT_START,
				ATTACK_HIT_END,
				ATTACK_END,
				STEP_END,
				MAGIC_CHANT_END,
				MAGIC_ATTACK_START,
				MAGIC_ATTACK_END,
				DAMAGE1_END,
				DAMAGE2_END,
				FALL_END,
				TYPE_MAX

			};
		}

		namespace  PLAYER_TYPE
		{
			enum
			{
				NORMAL,
				FIGHTER,	//	ファイター
				MAGICIAN,	//	マジシャン
				KNIGHT,		//	ナイト
				PRIEST,		//	プリースト
				ASSASSIN,	//	アサシン
				MODEL_MAX
			};
		}

		const int motionFrame[][FRAME_TYPE::TYPE_MAX] =
		{
			//すっぴん
			{
				140,// 攻撃判定開始
				150,// 攻撃判定終了
				160,// 攻撃終了
				260,// ステップ終了
				290,// 魔法詠唱終了
				340,// 魔法攻撃開始
				370,// 魔法攻撃終章
				409,// ノックバック(ダメージ)1
				438,// ノックバック(ダメージ)2
				494// 死にモーション終了
			},
			//ファイター
			{
				107,// 攻撃判定開始
				119,// 攻撃判定終了
				130,// 攻撃終了
				260,// ステップ終了
				290,// 魔法詠唱終了
				340,// 魔法攻撃開始
				370,// 魔法攻撃終章
				409,// ノックバック(ダメージ)1
				438,// ノックバック(ダメージ)2
				494// 死にモーション終了
			},
			//マジシャン
			{
				108,// 攻撃判定開始
				115,// 攻撃判定終了
				132,// 攻撃終了
				200,// ステップ終了
				258,// 魔法詠唱終了
				275,// 魔法攻撃開始
				287,// 魔法攻撃終章
				316,// ノックバック(ダメージ)1
				345,// ノックバック(ダメージ)2
				404// 死にモーション終了
			},
			//ナイト
			{
				127,// 攻撃判定開始
				140,// 攻撃判定終了
				152,// 攻撃終了
				220,// ステップ終了
				278,// 魔法詠唱終了
				295,// 魔法攻撃開始
				307,// 魔法攻撃終章
				336,// ノックバック(ダメージ)1
				365,// ノックバック(ダメージ)2
				424// 死にモーション終了
			},
			//プリースト
			{
				126,// 攻撃判定開始
				136,// 攻撃判定終了
				152,// 攻撃終了
				220,// ステップ終了
				278,// 魔法詠唱終了
				295,// 魔法攻撃開始
				307,// 魔法攻撃終章
				336,// ノックバック(ダメージ)1
				365,// ノックバック(ダメージ)2
				424// 死にモーション終了
			},
			//アサシン(仮)
			{
				127,// 攻撃判定開始
				140,// 攻撃判定終了
				155,// 攻撃終了
				260,// ステップ終了
				281,// 魔法詠唱終了
				333,// 魔法攻撃開始
				310,// 魔法攻撃終章
				339,// ノックバック(ダメージ)1
				368,// ノックバック(ダメージ)2
				1000// モーション終了
			},
		};
	}
}

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------
	
	//	コンストラクタ
	Player::Player( int id ) : timer( nullptr ),
		stepSpeed(0.0f), charType(PLAYER_TYPE::NORMAL),
		index( id )
	{
		ZeroMemory( &pParam, sizeof( PlayerParam ) );

		//	関数ポインタ設定
		ModeFunction[MODE::MOVE] = &Player::ModeMove;
		ModeFunction[MODE::SWOADATTACK] = &Player::ModeSwordAttack;
		ModeFunction[MODE::DAMAGE] = &Player::ModeDamage;
		ModeFunction[MODE::MAGICATTACK] = &Player::ModeMagicAttack;
		ModeFunction[MODE::DEATH] = &Player::ModeDeath;
		ModeFunction[MODE::STEP] = &Player::ModeStep;
		ModeFunction[MODE::MENU] = &Player::ModeMenu;

		timer = new Timer();
	}

	//	デストラクタ
	Player::~Player( void )
	{
		if ( timer != nullptr )
		{
			delete timer;
			timer = nullptr;
		}
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

	//	死亡
	void	Player::ModeDeath( void )
	{
		//	情報保存
		int motion = gameParam->GetPlayerParam( index ).motion;
		int frame = gameParam->GetPlayerParam( index ).frame;

		//	倒れるモーション時
		if ( motion == PLAYER_MOTION::FALL )
		{
			if ( frame >= motionFrame[charType][FRAME_TYPE::FALL_END] )
			{ 
				SetMotion( PLAYER_MOTION::DEAD );
				timer->Start( DEATH_TIME );
			}
		}
		else if ( motion == PLAYER_MOTION::DEAD )
		{
			if ( timer->Update() )
			{
				gameParam->InitializePlayer( index );
				SetMode( MODE::MOVE );
			}
		}
	}

	//	ステップ
	void	Player::ModeStep( void )
	{
		//	非アクティブにする
		gameParam->GetLifeInfo( index ).active = false;

		//	移動値加算
		Vector3	move = Vector3( sinf( pParam.angle ), 0.0f, cosf( pParam.angle ) ) * stepSpeed;
		AddMove( move );

		//	徐々に減速
		stepSpeed *= STEP_DRAG;

		//	モーションが終了すれば移動に戻る
		if ( pParam.frame >= motionFrame[charType][FRAME_TYPE::STEP_END])
		{
			SetMode( MODE::MOVE );
			gameParam->GetLifeInfo( index ).active = true;
		}
	}

	//	メニューモード
	void	Player::ModeMenu( void )
	{
		if ( inputManager->GetInputState( index, KEY_TYPE::START, KEY_STATE::ENTER ) ||
			inputManager->GetInputState( index, KEY_TYPE::A, KEY_STATE::ENTER ) )
		{
			SetMode( MODE::MOVE );
		}
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
			Vector3 move = Vector3( sinf( pParam.angle ), GRAVITY, cosf( pParam.angle ) ) * MOVE_SPEED;
			AddMove( move );

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
		if ( pParam.frame >= motionFrame[charType][FRAME_TYPE::ATTACK_HIT_START] &&
			pParam.frame <= motionFrame[charType][FRAME_TYPE::ATTACK_HIT_END])
		{
			gameParam->GetAttackInfo( index ).attackParam = AttackInfo::ATTACK1;
		}
		else
		{
			gameParam->GetAttackInfo( index ).attackParam = AttackInfo::NO_ATTACK;
		}

		// 一定以上のフレームに達すると移動に戻す
		if (pParam.frame >= motionFrame[charType][FRAME_TYPE::ATTACK_END])
		{
			SetMode( MODE::MOVE );
			gameParam->GetAttackInfo( index ).Reset();
		}
	}

	//	魔法攻撃
	void	Player::MagicAttack( void )
	{
		if (pParam.frame == motionFrame[charType][FRAME_TYPE::MAGIC_ATTACK_START])
		{
			magicManager->Append( index, 
				gameParam->GetAttackInfo( index ).vec1,
				gameParam->GetAttackInfo( index ).vec2 );
		}

		if (pParam.frame >= motionFrame[charType][FRAME_TYPE::MAGIC_ATTACK_END])
		{
			SetMode( MODE::MOVE );
			gameParam->GetAttackInfo( index ).Reset();
		}
	}

	//	魔法詠唱
	void	Player::MagicChant( void )
	{
		//	離したとき発動可能状態なら発動、発動不可なら移動に戻る
		if ( inputManager->GetInputState( index, KEY_TYPE::X, KEY_STATE::UP ) )
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

		//	詠唱中回転
		MagicChantRoll();
	}

	//	詠唱中回転
	void	Player::MagicChantRoll( void )
	{
		float axisX = inputManager->GetInput( index ).axisX;
		float axisZ = inputManager->GetInput( index ).axisY;
		float length = sqrtf( axisX * axisX + axisZ * axisZ );

		//	入力があれば移動処理
		if ( length < MIN_INPUT_STICK )		return;
		{
			//	向き調整
			AngleAdjust(
				Vector3( axisX, 0.0f, axisZ ),
				ANGLE_ADJUST_MOVE_SPEED );
		}
	}

	//	魔法詠唱開始
	void	Player::MagicChantStart( void )
	{
		//	押している間詠唱、一定時間経過で発動可能
		if ( inputManager->GetInputState( index, KEY_TYPE::X, KEY_STATE::STAY ) )
		{
			if (pParam.frame >= motionFrame[charType][FRAME_TYPE::MAGIC_CHANT_END])
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

		if (pParam.frame >= motionFrame[charType][FRAME_TYPE::DAMAGE1_END])
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
		if ( inputManager->GetInputState( index, KEY_TYPE::X, KEY_STATE::ENTER ) )
		{
			if ( SetMode( MODE::MAGICATTACK ) )
			{
				SetMotion( PLAYER_MOTION::MAGIC_CHANT_START );
				return;
			}
		}

		//	回避入力受付
		if ( inputManager->GetInputState( index, KEY_TYPE::A, KEY_STATE::ENTER ) )
		{
			if ( SetMode( MODE::STEP ) )
			{
				SetMotion( PLAYER_MOTION::STEP );
				stepSpeed = STEP_SPEED;
				return;
			}
		}

		//	メニュー入力受付
		if ( inputManager->GetInputState( index, KEY_TYPE::START, KEY_STATE::ENTER ) )
		{
			if ( SetMode( MODE::MENU ) )
			{
				SetMotion( PLAYER_MOTION::MENU );
				return;
			}
		}
	}

	//	移動値加算
	void	Player::AddMove( Vector3& move )
	{
		collision->CheckWall( pParam.pos, move, 100.0f );
		collision->CheckDown( pParam.pos, move );
		pParam.pos += move;
	}

	//	向き調整
	void	Player::AngleAdjust( const Vector3& targetVec, float adjustSpeed )
	{
		//	移動方向を求める
		float	moveAngle = atan2f( targetVec.x, targetVec.z );

		//	カメラの前方方向を求める
		float	cameraAngle = gameParam->GetPlayerParam( index ).cameraAngle;

		//	入力方向を求める
		float inputAngle = atan2f( targetVec.x, targetVec.z );

		//	目標の角度を求める
		float	targetAngle = cameraAngle + inputAngle;

		//	親に投げる
		AngleAdjustParent(
			Vector3( sinf( targetAngle ), 0.0f, cosf( targetAngle ) ),
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

	//	座標設定
	void	Player::SetPos( const Vector3& pos )
	{
		pParam.pos = pos;
	}

	//	死亡設定
	void	Player::SetDeath( void )
	{
		SetMode( MODE::DEATH );
		gameParam->GetPlayerParam( index ).motion = PLAYER_MOTION::FALL;
		gameParam->GetLifeInfo( index ).active = false;
	}
