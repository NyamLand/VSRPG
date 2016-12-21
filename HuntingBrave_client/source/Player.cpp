
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

//	ライフ設定
#define MAX_LIFE	5


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
	Player::Player( void ) : nextObj( nullptr ),
		id( -1 )
	{
		
	}

	//	デストラクタ
	Player::~Player( void )
	{
		SafeDelete( nextObj );
	}

	//	初期化
	bool	Player::Initialize( int id )
	{
		//	情報設定
		SetPos( Vector3( 0.0f, 0.0f, 0.0f ) );
		SetAngle( 0.0f );
		SetScale( PLAYER_SCALE );
		SetMotion( MOTION_NUM::POSUTURE );
		SetMode( MODE::MOVE );
		lifeInfo.Initialize( MAX_LIFE );

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

		//	バー初期化
		bar = new EnemyHpUI();
		bar->Initilaize( HPUI_TYPE::PLAYER, GetLifeInfo().maxLife );
		bar->SetId( id );

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
		//	情報取得
		playerParam = gameParam->GetPlayerParam( id );

		//	攻撃情報設定
		SetAttackShape();

		//	当たり判定形状設定
		SetCollisionShape( playerParam );

		//	サーバーからの情報を反映
		SetPlayerParam( playerParam );

		//	更新
		BaseChara::Update();
	}

	//	描画
	void	Player::Render( iexShader* shader, LPSTR technique )
	{
		BaseChara::Render();	
	}

//------------------------------------------------------------------------------------
//	動作関数
//------------------------------------------------------------------------------------

	//	剣攻撃
	void	Player::SetAttackShape( void )
	{
		//	仮、モーション番号でスキップ
		switch ( playerParam.motion )
		{
		case MOTION_NUM::ATTACK1:
			gameParam->GetAttackInfo( id ).shape = SHAPE_TYPE::CAPSULE;
			gameParam->GetAttackInfo( id ).radius = ATTACK_RADIUS;
			gameParam->GetAttackInfo( id ).vec1 = GetBonePos( BONE_NUM::HAND );
			gameParam->GetAttackInfo( id ).vec2 = GetBonePos( BONE_NUM::SWORD );
			break;

		case MOTION_NUM::MAGIC_ACTUATION:
			gameParam->GetAttackInfo( id ).shape = SHAPE_TYPE::SPHERE;
			gameParam->GetAttackInfo( id ).radius = ATTACK_RADIUS;
			gameParam->GetAttackInfo( id ).vec1 = GetBonePos( BONE_NUM::RIGHT_HAND );
			gameParam->GetAttackInfo( id ).vec2 = GetFront();
			break;

		default:
			return;
		}

		//	情報送信
		gameParam->SendAttackParam();
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
		lifeInfo.life = ( playerParam.life );
	}

	//	コリジョン形状設定
	void	Player::SetCollisionShape( const PlayerParam& playerParam )
	{
		collisionInfo.collisionShape.capsule = Capsule(
			Vector3( playerParam.pos.x, playerParam.pos.y + collisionInfo.radius, playerParam.pos.z ),
			Vector3( playerParam.pos.x, playerParam.pos.y + collisionInfo.height + collisionInfo.radius, playerParam.pos.z ),
			collisionInfo.radius );
	}

//------------------------------------------------------------------------------------
//	情報取得
//------------------------------------------------------------------------------------
