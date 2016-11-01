
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"Camera.h"
#include	"BaseChara.h"

//***************************************************************
//
//	BaseCharaクラス
//
//***************************************************************

//	定数値
#define	MOVE_RESISTANCE	0.9f

//------------------------------------------------------------------------------------
//	グローバル
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	初期化・解放
//------------------------------------------------------------------------------------

	//	コンストラクタ
	BaseChara::BaseChara( void ) : obj( nullptr ),
		pos( 0.0f, 0.0f, 0.0f ), move( 0.0f, 0.0f, 0.0f ),
		angle( 0.0f ), scale( 1.0f ), speed( 0.0f ), 
		mode( 0 ), timer( 0 ), step( 0 ),
		initflag( false )
	{
		//	構造体初期化
		ZeroMemory( &attackInfo, sizeof( AttackInfo ) );
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

	//	解放

//------------------------------------------------------------------------------------
//	更新・描画
//------------------------------------------------------------------------------------

	//	更新
	void	BaseChara::Update( void )
	{
		//	各種処理
		AddMove();

		//	情報更新
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

	//	移動値加算
	void	BaseChara::AddMove( void )
	{
		//	移動値加算
		pos += move;
		
		//	抵抗値計算
		move *= MOVE_RESISTANCE;
	}

//------------------------------------------------------------------------------------
//	動作関数
//------------------------------------------------------------------------------------

	//	向き調整
	void	BaseChara::AngleAdjust( const Vector3& targetVec, float adjustSpeed )
	{
		//	カメラの前方方向を求める
		Vector3	vEye = mainView->GetTarget() - mainView->GetPos();
		float	viewAngle = atan2f( vEye.x, vEye.z );

		//	移動方向を求める
		float	moveAngle = atan2f( targetVec.x, targetVec.z );

		//	目標の角度を求める
		float	targetAngle = viewAngle + moveAngle;

		//	親に投げる
		AngleAdjustParent(
			Vector3( sinf( targetAngle ), 0.0f, cosf( targetAngle ) ),
			adjustSpeed );
	}

	//	向き調整（親）
	void	BaseChara::AngleAdjustParent( const Vector3& direction, float adjustSpeed )
	{
		//	現在の向きと目標の向きの差を求める
		float	targetAngle( atan2f( direction.x, direction.z ) );

		//	角度差を求める
		float	dAngle( targetAngle - GetAngle() );

		//	差の正規化
		if ( dAngle > 1.0f * D3DX_PI )		dAngle -= 2.0f * D3DX_PI;
		if ( dAngle < -1.0f * D3DX_PI )	dAngle += 2.0f * D3DX_PI;

		//	差をspeed分縮める
		if ( dAngle > 0.0f )
		{
			dAngle -= adjustSpeed;
			if ( dAngle < 0.0f )	dAngle = 0.0f;
		}
		else
		{
			dAngle += adjustSpeed;
			if ( dAngle > 0.0f )	dAngle = 0.0f;
		}

		//	向きに反映
		SetAngle( targetAngle - dAngle );

		//	キャラクターの向きがPI以上にならないようにする
		if ( GetAngle() >= 1.0f * D3DX_PI )	angle -= 2.0f * D3DX_PI;
		if ( GetAngle() <= -1.0f * D3DX_PI ) angle += 2.0f * D3DX_PI;
	}

//------------------------------------------------------------------------------------
//	情報設定
//------------------------------------------------------------------------------------

	//	座標設定
	void	BaseChara::SetPos( const Vector3& Pos )
	{
		pos = Pos;
	}

	//	移動値設定
	void	BaseChara::SetMove( const Vector3& Move )
	{
		move = Move;
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

	//	移動値取得
	Vector3	BaseChara::GetMove( void )const
	{
		return	move;
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

	//	モーション取得
	int			BaseChara::GetMotion( void )const
	{
		return	obj->GetMotion();
	}

