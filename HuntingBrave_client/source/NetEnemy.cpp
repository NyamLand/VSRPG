
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
		//SafeDelete( obj );
		SafeDelete(bar);
	}

	//	初期化
	void	NetEnemy::Initialize( iex3DObj* org, const Vector3& Pos, float Angle )
	{
		life = INIT_LIFE;
		this->pos = Pos;
		this->angle = Angle;
		obj = org;
		obj->SetPos( pos );
		obj->SetAngle( angle );
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
		obj->SetPos( pos );
		obj->SetAngle( angle );
		obj->Update();
		obj->Animation();
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

//----------------------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------------------

	//	座標取得
	Vector3	NetEnemy::GetPos( void )const
	{
		return	pos;
	}

	//	上方取得
	Vector3	NetEnemy::GetUp(void)const
	{
		Matrix mat = GetMatrix();
		Vector3	up = Vector3(mat._21, mat._22, mat._23);
		up.Normalize();
		return	up;
	}

	//	行列取得
	Matrix	NetEnemy::GetMatrix(void)const
	{
		return	obj->TransMatrix;
	}