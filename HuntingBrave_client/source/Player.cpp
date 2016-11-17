
#include	<vector>
#include	<fstream>
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"DrawShape.h"
#include	"GameParam.h"
#include	"CSVReader.h"
#include	"BaseEquipment.h"
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
#define	PLAYER_SCALE	0.2f
#define	PLAYER_HEIGHT		2.5f
#define	PLAYER_RADIUS		1.5f

//	動作スピード
#define	ANGLE_ADJUST_MOVE_SPEED	0.3f
#define	ANGLE_ADJUST_MAGIC_SPEED	0.05f
#define	MOVE_SPEED		0.1f

//	入力情報
#define	MIN_INPUT_STICK		0.3f

//	定数関連
namespace
{
	//	ボーン番号
	enum BONE_NUM
	{
		HAND = 27,
		SWORD,
	};
}

//------------------------------------------------------------------------------------
//	初期化・解放
//------------------------------------------------------------------------------------

	//	コンストラクタ
	Player::Player( void ) : id( -1 )
	{
		//	関数ポインタ
		ModeFunction[MODE::MOVE] = &Player::MoveMode;
		ModeFunction[MODE::SWOADATTACK] = &Player::ModeSwordAttack;
		ModeFunction[MODE::MAGICATTACK] = &Player::ModeMagicAttack;
		ModeFunction[MODE::AVOID] = &Player::ModeAvoid;
	}

	//	デストラクタ
	Player::~Player( void )
	{
		
	}

	//	初期化
	bool	Player::Initialize( int id )
	{
		//	読み込み
		Load( "DATA/CHR/suppin/Suppin.IEM" );

		//	情報設定
		SetPos( Vector3( 0.0f, 0.0f, 0.0f ) );
		SetAngle( 0.0f );
		SetScale( PLAYER_SCALE );
		SetMotion( MOTION_NUM::POSUTURE );
		SetMode( MODE::MOVE );

		//	当たり判定形状設定
		collisionInfo.Set( SHAPE_TYPE::CAPSULE, PLAYER_HEIGHT, PLAYER_RADIUS );

		//	変数初期化
		this->id = id;
		speed = MOVE_SPEED;
		attackInfo.power = 1;
		lifeInfo.active = true;
		lifeInfo.isAlive = true;

		//	テクスチャ書き換え
		ChangeTexture( id );
		
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
	void	Player::Update( PlayerParam& playerParam )
	{
		//	サーバーからの情報を反映
		this->playerParam = playerParam;
		SetPlayerParam( playerParam );

		//	剣攻撃
		SwordAttack();

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
		//	移動モーション設定
		Move();
	}

	void	Player::ModeSwordAttack( void )
	{
		bool param = SwordAttack();

		if( param )	SetMode( MODE::MOVE );
	}

	void	Player::ModeMagicAttack( void )
	{
		bool param = MagicAttack();
		if( param )SetMode( MODE::MOVE );
	}

	void	Player::ModeAvoid( void )
	{
		bool param = Avoid();
		if( param )SetMode( MODE::MOVE );
	}

//------------------------------------------------------------------------------------
//	動作関数
//------------------------------------------------------------------------------------

	//	移動
	bool		Player::Move( void )
	{
		//float x, y, length;
		//length = gameParam->GetStickInput( x, y );

		//if ( length >= MIN_INPUT_STICK )	SetMotion( MOTION_NUM::RUN );
		//else SetMotion( MOTION_NUM::POSUTURE );
		return false;
	}

	//剣攻撃
	bool		Player::SwordAttack( void )
	{
		//	攻撃モーション以外ならスキップ
		if ( GetMotion() != MOTION_NUM::ATTACK1 )
		{
			attackInfo.Reset();
			return false;
		}

		//	攻撃情報設定
		int	frame = obj->GetFrame();

		if ( frame >= 170 && frame <= 180 )
		{
			attackInfo.attackParam = ATTACK_PARAM::ATTACK1;
		}
		else
		{
			attackInfo.attackParam = ATTACK_PARAM::NO_ATTACK;
		}
		
		//	ボーンの座標取得、当たり判定用構造体にセット
		Vector3	handPos = GetBonePos( BONE_NUM::HAND );
		Vector3	swordPos = GetBonePos( BONE_NUM::SWORD );
		attackInfo.collisionShape.SetCapsule( Capsule( handPos, swordPos, 1.0f ) );

		return false;
	}

	//魔法攻撃
	bool		Player::MagicAttack( void )
	{
		SetMotion( MOTION_NUM::MAGIC_CHANT );		//仮

		if ( !attackInfo.initFlag )
		{
			attackInfo.initFlag = true;
			attackInfo.timer = 0;
			move = Vector3( 0, 0, 0 );
		}

		//	左スティックの入力チェック
		float	axisX = ( float )input[0]->Get( KEY_AXISX );
		float	axisY = -( float )input[0]->Get( KEY_AXISY );
		float	length = sqrtf( axisX * axisX + axisY * axisY ) * 0.001f;
		switch ( attackInfo.step )
		{
		case 0:

			//	入力があれば
			if ( length >= MIN_INPUT_STICK )
			{
				//	向き調整
				AngleAdjust(
					Vector3( axisX, 0.0f, axisY ),
					ANGLE_ADJUST_MAGIC_SPEED );

				//if (axisX > 0)	angle += 0.1f; 
				//else			angle -= 0.1f;
			}


			if ( KEY_Get( KEY_B ) == 2 ) attackInfo.step++;
			break;
		case 1:
			attackInfo.timer++;		//硬直
			SetMotion( MOTION_NUM::MAGIC_CHANT );
			if (attackInfo.timer > 100)
			{
				attackInfo.initFlag = false;
				return true;
			}
		}
		return false;
	}

	//回避
	bool		Player::Avoid( void )
	{
		Vector3 front = GetFront();
		SetMotion( MOTION_NUM::STEP );

		if ( !attackInfo.initFlag )
		{
			attackInfo.initFlag = true;
			attackInfo.timer = 0;
			move.x += front.x * 1.1f;
			move.z += front.z * 1.1f;
		}

		attackInfo.timer++;

		if (attackInfo.timer > 30)
		{
			attackInfo.initFlag = false;
			return true;
		}


		return false;
	}

	//	テクスチャ設定
	void		Player::ChangeTexture( int colorNum )
	{
		//	ファイル設定
		char	fileName[256] = "DATA/CHR/suppin/s_body_";
		char playerNum[8] = "";
		sprintf_s( playerNum, "%d.png", colorNum );
		strcat_s( fileName, playerNum );
		obj->SetTexture( 0, fileName );
	}

//------------------------------------------------------------------------------------
//	情報設定
//------------------------------------------------------------------------------------

	//	パラメータ設定
	void	Player::SetPlayerParam( const PlayerParam& playerParam )
	{
		pos = playerParam.pos;
		angle = playerParam.angle;
		SetMotion( playerParam.motion );
	}

//------------------------------------------------------------------------------------
//	情報取得
//------------------------------------------------------------------------------------
