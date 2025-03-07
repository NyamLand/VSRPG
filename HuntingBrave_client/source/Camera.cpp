
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"InputManager.h"
#include	"Camera.h"

//***************************************************************
//
//	Cameraクラス
//
//***************************************************************

//----------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------

Camera* mainView = nullptr;

//	定数
#define	MIN_INPUT_STICK	0.3f

//	HERFTOP_VIEWパラメータ定数
#define HERFTOP_VIEW_DIST						20.0f
#define	HERFTOP_VIEW_HEIGHT				15.0f
#define	HERFTOP_VIEW_ROTATE_SPEED		D3DX_PI * 0.015f

namespace
{
	const float	rotateInit[] =
	{
		PI, 
		PI * 1.5f, 
		0.0f,
		PI * 0.5f
	};
}

//----------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------

	//	コンストラクタ
	Camera::Camera( void ) : viewMode( VIEW_MODE::FIX_VIEW ),
		pos( 0.0f, 0.0f, 0.0f ), target( 0.0f, 0.0f, 0.0f ), rotateAngle( 0.0f )
	{
		//	関数ポインタの配列に設定
		ViewUpdate[VIEW_MODE::FIX_VIEW] = &Camera::FixViewUpdate;
		ViewUpdate[VIEW_MODE::TRACKING_VIEW] = &Camera::TrackingViewUpdate;
		ViewUpdate[VIEW_MODE::THIRDPERSON_VIEW] = &Camera::ThirdPersonViewUpdate;
	}

	//	デストラクタ
	Camera::~Camera( void )
	{
		Release();
	}

	//	初期化
	bool Camera::Initialize( VIEW_MODE view_mode, const Vector3& Pos, const Vector3& Target )
	{
		//	ビューモード保存
		viewMode = view_mode;

		//	情報保存
		pos = Pos;
		target = Target;
		
		//	情報更新
		UpdateInfo();

		return	true;
	}

	//	回転初期化
	void	Camera::AngleInit( int index )
	{
		rotateAngle = rotateInit[index];
	}

	//	解放
	void	Camera::Release( void )
	{

	}

//----------------------------------------------------------------------------------
//	更新・描画
//----------------------------------------------------------------------------------

	//	更新
	void	Camera::Update( const Vector3& Target )
	{
		//	ターゲット座標保存
		target = Target;

		//	各カメラ動作
		( this->*ViewUpdate[ viewMode ] )();

		//	情報更新
		UpdateInfo();
	}

	//	情報更新
	void	Camera::UpdateInfo( void )
	{
		Set( pos, target );
	}
	
	//	描画( 主にデバッグ用 )
	void	Camera::Render( void )
	{

	}

//----------------------------------------------------------------------------------
//	各カメラ更新
//----------------------------------------------------------------------------------

	//	固定カメラ更新
	void	Camera::FixViewUpdate( void )
	{
		//	固定なので何もしない
		printf( "FixView\n" );
	}
	
	//	追跡カメラ更新( ハーフトップビュー )
	void	Camera::TrackingViewUpdate( void )
	{
		//	一定の距離を離す
		pos = target + Vector3( 
			HERFTOP_VIEW_DIST * sinf( rotateAngle ), 
			HERFTOP_VIEW_HEIGHT, 
			HERFTOP_VIEW_DIST * -cosf( rotateAngle ) );

		//	回転
		HerfTopViewRotate();

		//	角度制限
		AngleLimit();
	}

	//	三人称カメラ更新
	void	Camera::ThirdPersonViewUpdate( void )
	{

	}

//----------------------------------------------------------------------------------
//	動作関数
//----------------------------------------------------------------------------------

	//	カメラアングル制限
	void	Camera::AngleLimit( void )
	{
		if ( rotateAngle > D3DX_PI * 2 )	rotateAngle = 0;
		else if ( rotateAngle < 0 )	rotateAngle = D3DX_PI * 2;
	}

	//	回転
	void	Camera::HerfTopViewRotate( void )
	{
		//	入力取得
		float	axisX, axisY;
		inputManager->GetStickInputRight( axisX, axisY );

		//	回転
		if ( abs( axisX ) >= MIN_INPUT_STICK )
		{
			if ( axisX < 0.0f )
				rotateAngle += HERFTOP_VIEW_ROTATE_SPEED;
			else
				rotateAngle -= HERFTOP_VIEW_ROTATE_SPEED;	
		}
	}

	//	振動
	void	Camera::Shake( void )
	{

	}
	
//----------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------

	//	カメラ方向設定
	void	Camera::SetRotateAngle( float rotateAngle )
	{
		this->rotateAngle = rotateAngle;
	}

	//	座標設定
	void	Camera::SetPos( const Vector3& pos )
	{
		this->pos = pos;
	}

//----------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------

	//	実体取得
	Camera*	Camera::GetInstance( void )
	{
		static Camera out;
		return	&out;
	}

	//	座標取得
	Vector3	Camera::GetPos( void )const
	{
		return	pos;
	}

	//	ターゲット取得
	Vector3	Camera::GetTarget( void )const 
	{
		return	target;
	}

	//	行列取得
	Matrix	Camera::GetMatrix( void )const
	{
		return	this->matView;
	}
