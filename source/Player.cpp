
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"Player.h"

//***************************************************************
//
//	Playerクラス
//
//***************************************************************

//------------------------------------------------------------------------------------
//	グローバル
//------------------------------------------------------------------------------------

//	モデル情報
#define	Y2009_SCALE	0.02f

//	動作スピード
#define	ANGLE_ADJUST_SPEED	0.3f
#define	MOVE_SPEED		0.5f

//	入力情報
#define	MIN_INPUT_STICK		0.3f

//------------------------------------------------------------------------------------
//	初期化・解放
//------------------------------------------------------------------------------------

	//	コンストラクタ
	Player::Player( void )
	{
	
	}

	//	デストラクタ
	Player::~Player( void )
	{

	}

	//	初期化
	bool	Player::Initialize( void )
	{
		//	読み込み
		Load( "DATA/CHR/Y2009/Y2009.IEM" );

		SetPos( Vector3( 0.0f, 0.0f, 0.0f ) );
		SetAngle( 0.0f );
		SetScale( Y2009_SCALE );
		SetMotion( 1 );	//	数値仮
		speed = MOVE_SPEED;
		SetMode(MODE::MOVE);

		//	関数ポインタ
		ModeFunction[MODE::MOVE] = &Player::MoveMode;
		//ModeFunction[MODE::MOVE] = &Player::PostureMode;
		ModeFunction[MODE::SWOADATTACK] = &Player::ModeSwordAttack;
		ModeFunction[MODE::MAGICATTACK] = &Player::ModeMagicAttack;

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
	void	Player::Update( void )
	{
		//	各モードに応じた動作関数
		( this->*ModeFunction[mode] )();

		//	更新
		BaseChara::Update();
	}

//------------------------------------------------------------------------------------
//	動作関数
//------------------------------------------------------------------------------------

	//	移動モード動作
	void	Player::MoveMode( void )
	{
		//	スティックによる移動
		Move();
		if (KEY_Get(KEY_A) == 3) SetMode(MODE::SWOADATTACK);		//仮
		if (KEY_Get(KEY_B) == 3) SetMode(MODE::MAGICATTACK);	
	}

	void	Player::ModeSwordAttack( void )
	{
		int param = SwordAttack();

		switch (param)
		{
		case 1:
			SetMode(MODE::MOVE);
			break;
		case 2:
			break;
		}
	}

	void	Player::ModeMagicAttack( void )
	{
		int param = MagicAttack();

		switch (param)
		{
		case 1:
			SetMode(MODE::MOVE);
			break;
		case 2:
			break;
		}
	}

//------------------------------------------------------------------------------------
//	動作関数
//------------------------------------------------------------------------------------

	//	移動
	int		Player::Move( void )
	{
		//	左スティックの入力チェック
		float	axisX = ( float )input[0]->Get( KEY_AXISX );
		float	axisY = -( float )input[0]->Get( KEY_AXISY );
		float	length = sqrtf( axisX * axisX + axisY * axisY ) * 0.001f;

		//	入力があれば移動処理
		if ( length >= MIN_INPUT_STICK )
		{
			//	モーション設定
			SetMotion( MOTION::MOVE );	//	走りモーション

			//	向き調整
			AngleAdjust( 
				Vector3( axisX, 0.0f, axisY ), 
				ANGLE_ADJUST_SPEED );

			//	移動
			SetMove( Vector3( sinf( angle ), 0.0f, cosf( angle ) ) * speed );
		}
		else
		{
			//	モーション設定
			SetMotion( MOTION::WAIT );	//	待機モーション
		}
		return 1;
	}

	//剣攻撃
	int		Player::SwordAttack(void)
	{
		SetMotion( MOTION::ATTACK );


		//仮
		if (obj->GetFrame() == 413)return 1;	//攻撃動作が終われば

		return false;
	}


	//魔法攻撃
	int		Player::MagicAttack(void)
	{
		SetMotion(MOTION::ATTACK2);

		move = Vector3(0, 0, 0);

		//	左スティックの入力チェック
		float	axisX = (float)input[0]->Get(KEY_AXISX);
		float	axisY = -(float)input[0]->Get(KEY_AXISY);
		float	length = sqrtf(axisX * axisX + axisY * axisY) * 0.001f;

		//	入力があれば移動処理
		if (length >= MIN_INPUT_STICK)
		{
			angle += 0.1f; //☆作業途中
		}

		return false;
	}

//------------------------------------------------------------------------------------
//	情報設定
//------------------------------------------------------------------------------------

	void	Player::SetMode(int mode)
	{
		if (this->mode != mode)
		{
			this->mode = mode;
		}
	}


//------------------------------------------------------------------------------------
//	情報取得
//------------------------------------------------------------------------------------

