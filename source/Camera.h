
#pragma once

//***************************************************************
//
//	Cameraクラス
//
//***************************************************************

//	include

//	class
class Camera : public iexView
{
public:
	//	定数
	enum VIEW_MODE
	{
		FIX_VIEW,
		THIRDPERSON_VIEW,
		TRACKING_VIEW,
		MAX
	};

private:
	//	パラメータ
	VIEW_MODE viewMode;
	Vector3	pos;
	Vector3	target;
	float rotateAngle;

	//	更新関数ポインタ
	void( Camera::*ViewUpdate[MAX] )( void );

private:

public:
	//	初期化・解放
	Camera( void );
	~Camera( void );
	bool Initialize( VIEW_MODE view_mode, const Vector3& Pos, const Vector3& Target  );
	void Release( void );

	//	更新・描画
	void	Update( const Vector3& Taget );
	void	UpdateInfo( void );
	void	Render( void );

	//	各カメラ動作関数
	void	FixViewUpdate( void );
	void	TrackingViewUpdate( void );
	void	ThirdPersonViewUpdate( void );
	
	//	動作関数
	void	AngleLimit( void );
	void	HerfTopViewRotate( void );
	void	Shake( void );

	//	情報設定

	//	情報取得
	static Camera* GetInstance( void );
	Vector3	GetPos( void )const;
	Vector3	GetTarget( void )const;
	Matrix	GetMatrix( void )const;
};

extern Camera* mainView;
