
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"BaseChara.h"

//***************************************************************
//
//	BaseCharaクラス
//
//***************************************************************

//------------------------------------------------------------------------------------
//	グローバル
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	初期化・解放
//------------------------------------------------------------------------------------

	//	コンストラクタ
	BaseChara::BaseChara( void ) : obj( nullptr ),
		pos( 0.0f, 0.0f, 0.0f ), 
		angle( 0.0f ), scale( 1.0f )
	{
	
	}

	//	デストラクタ
	BaseChara::~BaseChara( void )
	{
		SafeDelete( obj );
	}

	//	読み込み
	bool	BaseChara::Load( LPSTR filename )
	{
		obj = new iex3DObj( filename );

		if ( obj == nullptr )
		{
			printf( "読み込み失敗\n" );
			return false;
		}
		return	true;
	}

	//	初期化

	//	解放

//------------------------------------------------------------------------------------
//	更新・描画
//------------------------------------------------------------------------------------

	//	更新
	void	BaseChara::Update( void )
	{
		UpdateInfo();
	}

	//	描画
	void	BaseChara::Render( iexShader* shader, LPSTR technique )
	{
		if ( shader == nullptr || technique == nullptr )
		{
			obj->Render();
		}
		else
		{
			obj->Render( shader, technique );
		}
	}

	//	情報更新
	void	BaseChara::UpdateInfo( void )
	{
		if ( obj == nullptr )
		{
			printf( "obj == nullptr\n" );
			return;
		}

		obj->Animation();
		obj->SetPos( pos );
		obj->SetAngle( angle );
		obj->SetScale( scale );
		obj->Update();
	}

//------------------------------------------------------------------------------------
//	動作関数
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	情報設定
//------------------------------------------------------------------------------------

	//	座標設定
	void	BaseChara::SetPos( const Vector3& Pos )
	{
		pos = Pos;
	}

	//	向き設定
	void	BaseChara::SetAngle( float Angle )
	{
		angle = Angle;
	}

	//	スケール設定
	void	BaseChara::SetScale( float Scale )
	{
		scale = Scale;
	}

	//	モーション設定
	void	BaseChara::SetMotion( int motion )
	{
		if ( obj->GetMotion() != motion )
		{
			obj->SetMotion( motion );
		}
	}

//------------------------------------------------------------------------------------
//	情報取得
//------------------------------------------------------------------------------------

	//	行列取得
	Matrix	BaseChara::GetMatrix( void )const
	{
		return	obj->TransMatrix;
	}

	//	座標取得
	Vector3	BaseChara::GetPos( void )const
	{
		return	pos;
	}

	//	前方取得
	Vector3	BaseChara::GetFront( void )const
	{
		Matrix mat = GetMatrix();
		Vector3	front = Vector3( mat._31, mat._32, mat._33 );
		front.Normalize();
		return	front;
	}

	//	上方取得
	Vector3	BaseChara::GetUp( void )const
	{
		Matrix mat = GetMatrix();
		Vector3	up = Vector3( mat._21, mat._22, mat._23 );
		up.Normalize();
		return	up;
	}

	//	右方取得
	Vector3	BaseChara::GetRight( void )const
	{
		Matrix mat = GetMatrix();
		Vector3	right = Vector3( mat._11, mat._12, mat._13 );
		right.Normalize();
		return	right;
	}

	//	向き設定
	float		BaseChara::GetAngle( void )const
	{
		return	angle;
	}

