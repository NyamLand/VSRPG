
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"DrawShape.h"
#include	"Camera.h"
#include	"Collision.h"
#include	"Interpolation.h"
#include	"BaseChara.h"

//***************************************************************
//
//	BaseCharaクラス
//
//***************************************************************

//	定数値
#define	MOVE_RESISTANCE	0.9f
#define	DAMAGE_EFFECT_SPEED	0.05f

//------------------------------------------------------------------------------------
//	グローバル
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	初期化・解放
//------------------------------------------------------------------------------------

	//	コンストラクタ
	BaseChara::BaseChara(void) : obj(nullptr), bar(nullptr),
		pos( 0.0f, 0.0f, 0.0f ), move( 0.0f, 0.0f, 0.0f ),
		angle( 0.0f ), scale( 1.0f ), speed( 0.0f ), damageEffPercentage( 1.0f ),
		mode( 0 ), effState( false )
	{
		ZeroMemory( &lifeInfo, sizeof( LifeInfo ) );
		ZeroMemory( &collisionInfo, sizeof( CollisionInfo ) );
	}

	//	デストラクタ
	BaseChara::~BaseChara( void )
	{
		SafeDelete( obj );
		SafeDelete( bar );
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
		pos.y = collision->CheckDown(pos);
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

		//drawShape->DrawCapsule( collisionInfo.collisionShape.capsule.p1, collisionInfo.collisionShape.capsule.p2, collisionInfo.radius, 0xFFFFFFFF );
	}

	//	HPバー描画
	void	BaseChara::BarRender( void )
	{
		bar->Render( ( float )GetLifeInfo().life, GetPos(), GetUp() );
	}

	//	情報更新
	void	BaseChara::UpdateInfo( void )
	{
		if ( obj == nullptr )
		{
			printf( "obj == nullptr\n" );
			return;
		}

		//	当たり判定形状更新
		SetCollisionShape();

		//	モデル情報更新
		obj->SetPos( pos );
		obj->SetAngle( angle );
		obj->SetScale( scale );
		obj->Update();
		obj->Animation();
	}

	//	移動値加算
	void	BaseChara::AddMove( void )
	{
		//	移動値加算
		move.y = 0.0f;
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

	//	当たり判定用形状設定
	void	BaseChara::SetCollisionShape( void )
	{
		switch ( collisionInfo.collisionShape.shapeType )
		{
		case SHAPE_TYPE::SPHERE:
			collisionInfo.collisionShape.sphere = Sphere( 
					Vector3( pos.x, pos.y + collisionInfo.height, pos.z ), 
					collisionInfo.radius );
			break;

		case SHAPE_TYPE::CAPSULE:
			collisionInfo.collisionShape.capsule = Capsule(
					Vector3( pos.x, pos.y + collisionInfo.radius, pos.z ), 
					Vector3( pos.x, pos.y + collisionInfo.height + collisionInfo.radius, pos.z ), 
					collisionInfo.radius );
			break;
		}
	}

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

	//	モード設定( 新規モードが同じならfalseをかえす )
	bool	BaseChara::SetMode( int nextMode )
	{
		if ( mode != nextMode )
		{
			mode = nextMode;
			return	true;
		}
		return	false;
	}

	//	モデル設定
	void	BaseChara::SetObj(	iex3DObj* obj )
	{
		this->obj = obj;
	}

//------------------------------------------------------------------------------------
//	情報取得
//------------------------------------------------------------------------------------

	//	ライフ情報取得
	LifeInfo&		BaseChara::GetLifeInfo( void )
	{
		return	lifeInfo;
	}

	//	当たり判定用形状取得
	CollisionInfo	BaseChara::GetCollisionInfo( void )const
	{
		return	collisionInfo;
	}

	//	行列取得
	Matrix	BaseChara::GetMatrix( void )const
	{
		return	obj->TransMatrix;
	}

	//	ボーン座標取得
	Vector3	BaseChara::GetBonePos( int boneNum )const
	{
		Matrix boneMat = *obj->GetBone( boneNum ) * obj->TransMatrix;
		Vector3	bonePos = Vector3( boneMat._41, boneMat._42, boneMat._43 );
		return	bonePos;
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

	//	モード取得
	int			BaseChara::GetMode( void )const
	{
		return	mode;
	}

	//	フレーム取得
	int			BaseChara::GetFrame( void )const
	{
		return	obj->GetFrame();
	}