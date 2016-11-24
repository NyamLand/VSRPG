
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
#define	ATTACK_RADIUS		0.5f

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
		RIGHT_HAND = 35
	};
}

//------------------------------------------------------------------------------------
//	初期化・解放
//------------------------------------------------------------------------------------

	//	コンストラクタ
	Player::Player( void ) : id( -1 )
	{
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

		//	攻撃情報設定
		SetAttackShape();

		//	更新
		BaseChara::Update();
	}

	void	Player::Render( iexShader* shader, LPSTR technique )
	{
		BaseChara::Render();	

		AttackInfo attackInfo= gameParam->GetAttackInfo( id );
		//drawShape->DrawCapsule( attackInfo.pos1, attackInfo.pos2, attackInfo.radius, 0xFFFFFFFF );
	}

//------------------------------------------------------------------------------------
//	動作関数
//------------------------------------------------------------------------------------

	//	移動
	bool	Player::Move( void )
	{
		return false;
	}

	//	剣攻撃
	void	Player::SetAttackShape( void )
	{
		//	仮、モーション番号でスキップ
		Vector3	pos1, pos2;

		switch ( playerParam.motion )
		{
		case MOTION_NUM::ATTACK1:
			gameParam->GetAttackInfo( id ).shape = SHAPE_TYPE::CAPSULE;
			gameParam->GetAttackInfo( id ).radius = ATTACK_RADIUS;
			gameParam->GetAttackInfo( id ).pos1 = GetBonePos( BONE_NUM::HAND );
			gameParam->GetAttackInfo( id ).pos2 = GetBonePos( BONE_NUM::SWORD );
			break;

		case MOTION_NUM::MAGIC_ACTUATION:
			gameParam->GetAttackInfo( id ).shape = SHAPE_TYPE::SPHERE;
			gameParam->GetAttackInfo( id ).pos1 = GetBonePos( BONE_NUM::RIGHT_HAND );
			break;

		default:
			printf( "default\n" );
		}

		//	攻撃情報送信
		gameParam->SendAttackParam();
	}

	//	テクスチャ設定
	void	Player::ChangeTexture( int colorNum )
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
