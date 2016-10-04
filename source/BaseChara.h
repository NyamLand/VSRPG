
#pragma once

//***************************************************************
//
//	BaseCharaクラス
//
//***************************************************************

//	include

//	class
class BaseChara
{
protected:
	//	モデル
	iex3DObj*	obj;

	//	パラメータ
	Vector3		pos;
	Vector3		move;
	float			angle;
	float			speed;
	float			scale;

public:
	//	初期化・解放
	BaseChara( void );
	virtual ~BaseChara( void );
	bool	Load( LPSTR filename );
	virtual bool Initialize( void ) = 0;
	
	//	更新・描画
	virtual void	Update( void );
	virtual void	Render( iexShader* shader = nullptr, LPSTR technique = nullptr );
	void	UpdateInfo( void );
	void	AddMove( void );

	//	動作関数
	void	AngleAdjust( const Vector3& moveVec, float adjustSpeed );
	void	AngleAdjustParent( const Vector3& direction, float adjustSpeed );

	//	情報設定
	void	SetPos( const Vector3& Pos );
	void	SetMove( const Vector3& Move );
	void	SetAngle( float Angle );
	void	SetScale( float Scale );
	void	SetMotion( int motion );

	//	情報取得
	Matrix	GetMatrix( void )const;
	Vector3	GetPos( void )const;
	Vector3	GetFront( void )const;
	Vector3	GetUp( void )const;
	Vector3	GetRight( void )const;
	float		GetAngle( void )const;
};
