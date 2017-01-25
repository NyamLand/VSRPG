
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameParam.h"
#include	"DrawShape.h"
#include	"NetEnemy.h"

//***************************************************************
//
//	NetEnemyクラス
//
//***************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------
#define INIT_LIFE	20
#define HALK_RADIUS	2.0f
#define	HALK_HEIGHT	4.0f
#define	DEAD_MOTION_END		960

namespace
{
	namespace MOTION_NUM
	{
		enum
		{
			POSTURE,
			POSTURE1,
			MOVE,
			ATTACK_1,
			ATTACK_2,
			ATTACK_3,
			NAZO,
			WAVE,
			DEAD
		};
	}

	namespace MOTION_FRAME
	{
		const int ATTACK_ONE_START = 348;
		const int ATTACK_ONE_END = 375;
		const int ATTACK_TWO_START = 440;
		const int ATTACK_TWO_END = 500;
		const int ATTACK_THREE_START = 530;
		const int ATTACK_THREE_END = 575;
	}
}
//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
NetEnemy::NetEnemy(void) : obj(nullptr), bar(nullptr),
		pos( 0.0f, 0.0f, 0.0f ), 
		angle( 0.0f ),
		life(0),
		isAlive( false )
	{
		ZeroMemory( &attackInfo, sizeof( attackInfo ) );
	}

	//	デストラクタ
	NetEnemy::~NetEnemy( void )
	{
		SafeDelete( obj );
		SafeDelete(bar);
	}

	//	初期化
	void	NetEnemy::Initialize( iex3DObj* org, const Vector3& Pos, float Angle )
	{
		life = INIT_LIFE;
		this->pos = Pos;
		this->angle = Angle;
		this->isAlive = true;
		obj = org;
		obj->SetPos( pos );
		obj->SetAngle( angle );
		org->SetScale( 0.015f );
		obj->Update();
		bar = new EnemyHpUI();
		bar->Initilaize(HPUI_TYPE::ENEMY, GetLife());
	}

//----------------------------------------------------------------------------------------------
//	更新・描画
//----------------------------------------------------------------------------------------------

	//	更新
	void	NetEnemy::Update( void )
	{
		//	死亡モーション時
		if ( obj->GetMotion() == MOTION_NUM::DEAD )
			Death();

		obj->SetPos( pos );
		obj->SetAngle( angle );
		obj->Update();
		obj->Animation();

		CheckAttackInfo();
	}

	//	描画
	void	NetEnemy::Render( void )
	{
		obj->Render();
	}

	//	HPバー描画
	void	NetEnemy::RenderHpBar(void)
	{
		bar->Render((float)GetLife(), GetPos(), GetUp());
	}

//----------------------------------------------------------------------------------------------
//	動作関数
//----------------------------------------------------------------------------------------------

	//	死亡
	void	NetEnemy::Death( void )
	{
		//	フレーム取得
		int frame = obj->GetFrame();

		//	フレーム制御
		if ( frame >= DEAD_MOTION_END )
		{
			//	透過開始
			isAlive = false;
		}
	}

	//	フレーム情報から攻撃情報を設定
	void	NetEnemy::CheckAttackInfo( void )
	{
		int motion = obj->GetMotion();
		int frame = obj->GetFrame();
		if ( motion != MOTION_NUM::ATTACK_1 &&
			motion != MOTION_NUM::ATTACK_2 &&
			motion != MOTION_NUM::ATTACK_3 )	return;

		//	攻撃モーション管理
		if ( frame >= MOTION_FRAME::ATTACK_ONE_START && frame <= MOTION_FRAME::ATTACK_ONE_END )
		{
			//	攻撃状態を有効にする
			attackInfo.Set( SHAPE_TYPE::CAPSULE, HALK_RADIUS, pos, pos + Vector3( 0.0f, HALK_HEIGHT, 0.0f ) );
			attackInfo.attackParam = ATTACK_PARAM::ATTACK1;
		}
		else
		{
			//	攻撃状態を無効にする
			attackInfo.attackParam = ATTACK_PARAM::NO_ATTACK;

			//	通常モードへ移行
			if ( frame >= 420 )
			{
				SetMotion( MOTION_NUM::POSTURE );
			}
		}
	}

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

	//	座標設定
	void	NetEnemy::SetPos( const Vector3& pos )
	{
		this->pos = pos;
	}

	//	方向設定
	void	NetEnemy::SetAngle( float angle )
	{
		this->angle = angle;
	}

	//	モーション設定
	void	NetEnemy::SetMotion( int motion )
	{
		if ( obj->GetMotion() != motion )
		{
			obj->SetMotion( motion );
		}
	}

	//	メッシュ設定
	void	NetEnemy::SetMesh( iex3DObj*	mesh )
	{
		obj = mesh;
	}

	//	死亡させる
	void	NetEnemy::SetDeath( void )
	{
		SetMotion( MOTION_NUM::DEAD );
	}

//----------------------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------------------

	//	座標取得
	Vector3	NetEnemy::GetPos( void )const
	{
		return	pos;
	}

	//	上方取得
	Vector3	NetEnemy::GetUp( void )const
	{
		Matrix mat = GetMatrix();
		Vector3	up = Vector3(mat._21, mat._22, mat._23);
		up.Normalize();
		return	up;
	}

	//	行列取得
	Matrix	NetEnemy::GetMatrix( void )const
	{
		return	obj->TransMatrix;
	}