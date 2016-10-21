
#include	<vector>
#include	<fstream>
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"Player.h"
#include	"CSVReader.h"
#include	"BaseEquipment.h"

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
#define	ANGLE_ADJUST_MOVE_SPEED	0.3f
#define	ANGLE_ADJUST_MAGIC_SPEED	0.05f
#define	MOVE_SPEED		0.5f

//	入力情報
#define	MIN_INPUT_STICK		0.3f

//------------------------------------------------------------------------------------
//	初期化・解放
//------------------------------------------------------------------------------------

	//	コンストラクタ
Player::Player(void) : texture(nullptr), hp(0)
	{
	
	}

	//	デストラクタ
	Player::~Player( void )
	{
		SafeDelete( texture );
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

		//	テクスチャテスト
		obj->SetTexture( 0, "DATA/CHR/Y2009/testTexture.png" );

		//	関数ポインタ
		ModeFunction[MODE::MOVE] = &Player::MoveMode;
		ModeFunction[MODE::SWOADATTACK] = &Player::ModeSwordAttack;
		ModeFunction[MODE::MAGICATTACK] = &Player::ModeMagicAttack;
		ModeFunction[MODE::AVOID] = &Player::ModeAvoid;

		//	情報更新
		UpdateInfo();

		//----------------仮-------------
		//std::fstream r("DATA\\test.csv", std::ios::in);

		//CSVReader csv(r);
		//vector<string> tokens;
		//while (!csv.Read(tokens))
		//{
		//	for (unsigned int i = 0; i<tokens.size(); i++)
		//	{
		//		if (tokens[0] == "HP")
		//		{
		//			hp = std::atoi(tokens[1].c_str());
		//		}
		//	}
		//}
		//csv.Close();
		//return 0;
		//---------------------------------


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

	void	Player::Render( iexShader* shader, LPSTR technique )
	{
		BaseChara::Render();

	}

//------------------------------------------------------------------------------------
//	動作関数
//------------------------------------------------------------------------------------

	//	移動モード動作
	void	Player::MoveMode( void )
	{
		//	スティックによる移動
		Move();
		if ( KEY_Get( KEY_A ) == 3 ) SetMode( MODE::SWOADATTACK );		//仮
		if ( KEY_Get( KEY_B ) == 3 ) SetMode( MODE::MAGICATTACK );
		if ( KEY_Get( KEY_C ) == 3 ) SetMode( MODE::AVOID );
	}

	void	Player::ModeSwordAttack( void )
	{
		bool param = SwordAttack();

		if(param)SetMode(MODE::MOVE);
	}

	void	Player::ModeMagicAttack( void )
	{
		bool param = MagicAttack();
		if(param)SetMode(MODE::MOVE);
	}


	void	Player::ModeAvoid(void)
	{
		bool param = Avoid();
		if(param)SetMode(MODE::MOVE);
	}

//------------------------------------------------------------------------------------
//	動作関数
//------------------------------------------------------------------------------------

	//	移動
	bool		Player::Move( void )
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
				ANGLE_ADJUST_MOVE_SPEED );

			//	移動
			SetMove( Vector3( sinf( angle ), 0.0f, cosf( angle ) ) * speed );
		}
		else
		{
			//	モーション設定
			SetMotion( MOTION::WAIT );	//	待機モーション
		}
		return false;
	}



	//剣攻撃
	bool		Player::SwordAttack(void)
	{
		SetMotion( MOTION::ATTACK );		//仮
		if (!initflag) initflag = true;

		//仮
		if (obj->GetFrame() == 413)
		{
			initflag = false;
			return true;	//攻撃動作が終われば
		}
		return false;
	}





	//魔法攻撃
	bool		Player::MagicAttack(void)
	{
		SetMotion(MOTION::ATTACK2);		//仮

		if (!initflag)
		{
			initflag = true;
			timer = 0;
			move = Vector3(0, 0, 0);
		}

		//	左スティックの入力チェック
		float	axisX = (float)input[0]->Get(KEY_AXISX);
		float	axisY = -(float)input[0]->Get(KEY_AXISY);
		float	length = sqrtf(axisX * axisX + axisY * axisY) * 0.001f;
		switch (step)
		{
		case 0:

			//	入力があれば
			if (length >= MIN_INPUT_STICK)
			{
				//	向き調整
				AngleAdjust(
					Vector3(axisX, 0.0f, axisY),
					ANGLE_ADJUST_MAGIC_SPEED);

				//if (axisX > 0)	angle += 0.1f; 
				//else			angle -= 0.1f;
			}


			if (KEY_Get(KEY_B) == 2) step++;
			break;
		case 1:
			timer++;		//硬直
			SetMotion(MOTION::RIGOR);
			if (timer > 100)
			{
				initflag = false;
				return true;
			}
		}
		return false;
	}


	//回避
	bool		Player::Avoid(void)
	{
		Vector3 front = GetFront();
		SetMotion(MOTION::AVOID);

		if (!initflag)
		{
			initflag = true;
			timer = 0;
			move.x += front.x * 1.1f;
			move.z += front.z * 1.1f;
		}

		timer++;

		if (timer > 30)
		{
			initflag = false;
			return true;
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
			step = 0;
			this->mode = mode;
		}
	}


//------------------------------------------------------------------------------------
//	情報取得
//------------------------------------------------------------------------------------

