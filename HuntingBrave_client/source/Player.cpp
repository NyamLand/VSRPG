
#include	<vector>
#include	<fstream>
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"DrawShape.h"
#include	"GameParam.h"
#include	"CSVReader.h"
#include	"Sound.h"
#include	"BaseEquipment.h"
#include	"EffectManager.h"
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
#define	KNIGHT_SCALE	0.08f
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
		LEFT_HAND = 15,
		HAND = 27,
		SWORD,
		RIGHT_HAND = 35
	};

	//	表情
	namespace FACE_TYPE
	{
		enum
		{
			NORMAL,
			DAMAGE,
			ATTACK
		};
	}

	namespace
	{
		const LPSTR fileName[] =
		{
			"DATA/CHR/suppin/Suppin.IEM",
			"DATA/CHR/Fighter/Fighter.IEM",
			"DATA/CHR/Magician/Magician.IEM",
			"DATA/CHR/Knight/Knight.IEM",
			"DATA/CHR/Prist/prist.IEM",
			"DATA/CHR/Assasin/assasin.IEM"
		};

		//	通常顔
		const LPSTR	normalFaceFile[] =
		{
			"DATA/CHR/suppin/face.png",
			"DATA/CHR/Fighter/face.png",
			"DATA/CHR/Magician/face.png",
			"DATA/CHR/Knight/face.png",
			"DATA/CHR/Prist/face2.png",
			"DATA/CHR/Assasin/face.png"
		};

		//	ダメージ顔
		const LPSTR	damageFaceFile[] =
		{
			"DATA/CHR/suppin/face_damage.png",
			"DATA/CHR/Fighter/face_damage.png",
			"DATA/CHR/Magician/face_damage.png",
			"DATA/CHR/Knight/face_damage.png",
			"DATA/CHR/Prist/face_damage.png",
			"DATA/CHR/Assasin/face_damage.png"
		};

		//	攻撃顔
		const LPSTR attackFaceFile[] = 
		{
			"DATA/CHR/suppin/face_koueki.png",
			"DATA/CHR/Fighter/face_koueki.png",
			"DATA/CHR/Magician/face_koueki.png",
			"DATA/CHR/Knight/face_koueki.png",
			"DATA/CHR/Prist/face_koueki.png",
			"DATA/CHR/Assasin/face_koueki.png"
		};
	}
	
	namespace 
	{
		const LPSTR bodyTexFileName[] =
		{
			"DATA/CHR/suppin/body_",
			"DATA/CHR/Fighter/body_",
			"DATA/CHR/Magician/body_",
			"DATA/CHR/Knight/body_",
			"DATA/CHR/Prist/body_",
			"DATA/CHR/Assasin/body_"
		};
	}

	namespace
	{
		int shotBone[] =
		{
			BONE_NUM::RIGHT_HAND,
			BONE_NUM::LEFT_HAND,
			BONE_NUM::LEFT_HAND,
			BONE_NUM::LEFT_HAND,
			BONE_NUM::RIGHT_HAND,
			BONE_NUM::RIGHT_HAND,
		};
	}
}

//------------------------------------------------------------------------------------
//	初期化・解放
//------------------------------------------------------------------------------------

	//	コンストラクタ
	Player::Player( void ) : id( -1 ), curClass( CLASS_TYPE::NORMAL )
	{
		for ( int i = 0; i < CLASS_TYPE::CLASS_MAX; i++ )
		{
			org[i] = nullptr;
		}
	}

	//	デストラクタ
	Player::~Player( void )
	{
		ZeroMemory( &playerParam, sizeof( PlayerParam ) );

		for ( int i = 0; i < CLASS_TYPE::CLASS_MAX; i++ )
		{
			SafeDelete( org[i] );
		}
		
		obj = nullptr;
	}

	//	初期化
	bool	Player::Initialize( int id )
	{
		this->id = id;

		//	モデル読み込み
		Load();
		obj = org[CLASS_TYPE::NORMAL];

		//	情報設定
		SetPos( Vector3( 0.0f, 0.0f, 0.0f ) );
		SetAngle( 0.0f );
		SetScale( PLAYER_SCALE );
		SetMode( MODE::MOVE );
		SetMotion(MOTION_NUM::POSUTURE );
		lifeInfo.Initialize( MAX_LIFE );

		//	当たり判定形状設定
		collisionInfo.Set( SHAPE_TYPE::CAPSULE, PLAYER_HEIGHT, PLAYER_RADIUS );

		//	変数初期化
		speed = MOVE_SPEED;
		lifeInfo.active = true;
		lifeInfo.isAlive = true;

		//	情報更新
		UpdateInfo();

		//	バー初期化
		bar = new EnemyHpUI();
		bar->Initilaize( HPUI_TYPE::PLAYER, gameParam->GetPlayerStatus().maxLife );
		bar->SetId( id );

		if ( obj == nullptr )	return	false;
		return	true;
	}

	//	読み込み
	void	Player::Load( void )
	{
		for ( int i = 0; i < CLASS_TYPE::CLASS_MAX; i++ )
		{
			if ( org[i] == nullptr )
			{ 
				org[i] = new iex3DObj( fileName[i] );
				org[i]->SetScale( PLAYER_SCALE );
				org[i]->SetPos( 0.0f, 0.0f, 0.0f );
				org[i]->SetAngle( 0.0f );
				org[i]->SetMotion( MOTION_NUM::POSUTURE );
				ChangeTexture( org[i], ( char)i, id );
				org[i]->Update();
			}
		}
	}

	//	テクスチャ設定
	void	Player::ChangeTexture( iex3DObj*& model, char classType, int id )
	{
		//	ファイル設定
		char str[50] = "";
		sprintf_s( str, bodyTexFileName[classType] );
		
		//	プレイヤー番号設定
		char pNum[10] = "";
		sprintf_s( pNum, "%d.png", id + 1 );

		//	連結
		strcat_s( str, pNum );
		if ( classType == CLASS_TYPE::ASSASSIN )
		{
			model->SetTexture( 1, str );
		}
		else model->SetTexture( 0, str );

		if ( classType == CLASS_TYPE::FIGHTER )
		{
			sprintf_s( str, "" );
			sprintf_s( str, "DATA/CHR/Fighter/toumeitachi_%d.png", id + 1 );
			model->SetTexture( 3, str );
		}
	}

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


		//	魔法詠唱中なら描画
		if (obj->GetMotion() == MOTION_NUM::MAGIC_CHANT)
		{
			effectManager->SetCircleRender(id);
		}

		//	無敵状態チェック
		CheckUnrivaled();
		
		//	更新
		BaseChara::Update();
	}

	//	描画
	void	Player::Render( iexShader* shader, LPSTR technique )
	{
		shader->SetValue( "effParam", 1.0f - gameParam->GetPlayerParam( id ).effParam );

		//	モデル描画
		BaseChara::Render( shader, technique );	
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

		case MOTION_NUM::ATTACK2:
			gameParam->GetAttackInfo(id).shape = SHAPE_TYPE::CAPSULE;
			gameParam->GetAttackInfo(id).radius = ATTACK_RADIUS;
			gameParam->GetAttackInfo(id).vec1 = GetBonePos(BONE_NUM::HAND);
			gameParam->GetAttackInfo(id).vec2 = GetBonePos(BONE_NUM::SWORD);
			break;

		case MOTION_NUM::MAGIC_ACTUATION:
			gameParam->GetAttackInfo( id ).shape = SHAPE_TYPE::SPHERE;
			gameParam->GetAttackInfo( id ).radius = ATTACK_RADIUS;
			gameParam->GetAttackInfo( id ).vec1 = GetBonePos( shotBone[curClass] );
			gameParam->GetAttackInfo( id ).vec2 = GetFront();
			break;

		default:
			return;
		}

		//	情報送信
		gameParam->SendAttackParam();
	}

	//	モーション切り換え時のSE設定
	void	Player::PlaySE( int motion )
	{
		switch ( motion )
		{
			case MOTION_NUM::ATTACK1:
			case MOTION_NUM::ATTACK2:
				sound->PlaySE( SE::ATTACK );
				break;

			case MOTION_NUM::STEP:
				sound->PlaySE(SE::STEP);
				break;

			/*case MOTION_NUM::LEVEL_UP:
				sound->PlaySE(SE::LVUP);
				break;*/

			case MOTION_NUM::DEAD:
				sound->PlaySE(SE::PLAYER_DEAD);
				break;

			case MOTION_NUM::MAGIC_CHANT:
				sound->PlaySE(SE::MAGIC_CHARGE);
				break;

			//　メニュー開く音源がない　
			case MOTION_NUM::MENU:
				sound->PlaySE(SE::OK);
				break;

			default:
				break;
		}
	
	}

	//	モデルチェンジ
	void	Player::ChangeModel( char nextClass )
	{
		//	クラス設定
		curClass = nextClass;

		//	情報移動
		obj = org[curClass];
		
		SetPos( pos );
		SetAngle( angle );
		SetMotion( gameParam->GetPlayerParam( id ).motion );
		SetScale( PLAYER_SCALE );
		sound->PlaySE(SE::MAX_UPGRADE);
		if (curClass == CLASS_TYPE::KNIGHT)	SetScale(KNIGHT_SCALE);
		if (curClass == CLASS_TYPE::ASSASSIN)	SetScale(KNIGHT_SCALE);
		obj->Update();
	}

	//	表情変更
	void	Player::ChangeFaceTexture( char faceType )
	{
		switch ( faceType )
		{
		case FACE_TYPE::NORMAL:
			if (curClass == CLASS_TYPE::FIGHTER || curClass == CLASS_TYPE::MAGICIAN)
				obj->SetTexture( 2, normalFaceFile[curClass] );
			else if (curClass == CLASS_TYPE::ASSASSIN)
			{
				obj->SetTexture( 0, normalFaceFile[curClass] );
				//obj->SetTexture( 2, normalFaceFile[curClass] );
			}
			else
				obj->SetTexture( 1, normalFaceFile[curClass] );
			break;

		case FACE_TYPE::DAMAGE:
			if (curClass == CLASS_TYPE::FIGHTER || curClass == CLASS_TYPE::MAGICIAN)
				obj->SetTexture( 2, damageFaceFile[curClass] );
			else if (curClass == CLASS_TYPE::ASSASSIN)
			{
				obj->SetTexture( 0, damageFaceFile[curClass]);
				//obj->SetTexture( 2, damageFaceFile[curClass] );
			}
			else
				obj->SetTexture( 1, damageFaceFile[curClass] );
			break;

		case FACE_TYPE::ATTACK:
			if ( curClass == CLASS_TYPE::FIGHTER || curClass == CLASS_TYPE::MAGICIAN )
				obj->SetTexture( 2, attackFaceFile[curClass] );
			else if (curClass == CLASS_TYPE::ASSASSIN)
			{
				obj->SetTexture( 0, attackFaceFile[curClass] );
				//obj->SetTexture( 2, attackFaceFile[curClass] );
			}
			else
				obj->SetTexture(1, attackFaceFile[curClass]);
			break;

		default:
			break;
		}
	}

	//	モーションに対応した表情変更
	void	Player::ChangeFaceType( int motion )
	{
		switch ( motion )
		{
			//	ダメージ顔
		case MOTION_NUM::KNOCKBACK1:
		case MOTION_NUM::KNOCKBACK2:
		case MOTION_NUM::DEAD:
		case MOTION_NUM::FALL:
			ChangeFaceTexture( FACE_TYPE::DAMAGE );
			break;

			//	攻撃顔
		case MOTION_NUM::ATTACK1:
		case MOTION_NUM::ATTACK2:
		case MOTION_NUM::MAGIC_ACTUATION:
			ChangeFaceTexture( FACE_TYPE::ATTACK );
			break;

		default:
			ChangeFaceTexture( FACE_TYPE::NORMAL );
			break;
		}
	}

	//	無敵状態チェック
	void	Player::CheckUnrivaled( void )
	{
		switch ( obj->GetMotion() )
		{
		case MOTION_NUM::KNOCKBACK1:
		case MOTION_NUM::FALL:
		case MOTION_NUM::DEAD:
			lifeInfo.active = false;
			break;

		default:
			if ( gameParam->GetPlayerParam( id ).effParam < 1.0f )
			{
				lifeInfo.active = false;
			}
			else lifeInfo.active = true;
		}

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

	//	モーション設定
	void	Player::SetMotion( int motion )
	{
		if ( obj->GetMotion() != motion )
		{
			obj->SetMotion( motion );
			PlaySE( motion );
			ChangeFaceType( motion );
		}
	}

//------------------------------------------------------------------------------------
//	情報取得
//------------------------------------------------------------------------------------
