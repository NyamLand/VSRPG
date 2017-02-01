
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameParam.h"
#include	"DrawShape.h"
#include	"Magic.h"

//***************************************************************
//
//	Magicクラス
//
//***************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

#define	MAGIC_RADIUS	2.5f

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	Magic::Magic( void ) : obj( nullptr ),
		pos( 0.0f, 0.0f, 0.0f ), 
		angle( 0.0f ), radius( MAGIC_RADIUS )
	{
	
	}

	//	デストラクタ
	Magic::~Magic( void )
	{
		//SafeDelete( obj );
	}

	//	初期化
	void	Magic::Initialize( iexMesh* org, int id, const Vector3& Pos, float Angle )
	{
		this->pos = Pos;
		this->angle = Angle;
		this->id = id;
		obj = org;
		obj->SetPos( pos );
		obj->SetAngle( angle );
		obj->Update();
	}

//----------------------------------------------------------------------------------------------
//	更新・描画
//----------------------------------------------------------------------------------------------

	//	更新
	void	Magic::Update( void )
	{
		obj->SetPos( pos );
		obj->Update();
	}

	//	描画
	void	Magic::Render( void )
	{
		obj->Render();
	}

//----------------------------------------------------------------------------------------------
//	動作関数
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

	//	座標設定
	void	Magic::SetPos( const Vector3& pos )
	{
		this->pos = pos;
	}

	//	メッシュ設定
	void	Magic::SetMesh( iexMesh*	mesh )
	{
		obj = mesh;
	}

//----------------------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------------------

	//	座標取得
	Vector3	Magic::GetPos( void )const
	{
		return	pos;
	}

	//	半径取得
	float			Magic::GetRadius( void )const
	{
		return	radius;
	}

	//	ID取得
	int			Magic::GetID( void )const
	{
		return	id;
	}

	//	行列取得
	Matrix	Magic::GetMatrix(void)const
	{
		return	obj->TransMatrix;
	}


	//	前方取得
	Vector3	Magic::GetFront(void)const
	{
		Matrix mat = GetMatrix();
		Vector3	front = Vector3(mat._31, mat._32, mat._33);
		front.Normalize();
		return	front;
	}

	//	上方取得
	Vector3	Magic::GetUp(void)const
	{
		Matrix mat = GetMatrix();
		Vector3	up = Vector3(mat._21, mat._22, mat._23);
		up.Normalize();
		return	up;
	}

	//	右方取得
	Vector3	Magic::GetRight(void)const
	{
		Matrix mat = GetMatrix();
		Vector3	right = Vector3(mat._11, mat._12, mat._13);
		right.Normalize();
		return	right;
	}