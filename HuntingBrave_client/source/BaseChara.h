
#pragma once

//***************************************************************
//
//	BaseCharaクラス
//
//***************************************************************

//	include
#include	"CharaInfo.h"
#include	"EnemyHp.h"
//	class
class BaseChara
{
protected:
	//	モデル
	iex3DObj*	obj;
	EnemyHpUI*	bar;

	//	パラメータ
	Vector3		pos;
	Vector3		move;
	float			angle;
	float			speed;
	float			scale;
	int				mode;
	CollisionInfo	collisionInfo;
	LifeInfo			lifeInfo;

	bool	effState;
	float	damageEffPercentage;

public:
	//	初期化・解放
	BaseChara( void );
	virtual ~BaseChara( void );
	bool	Load( LPSTR filename );
	virtual bool Initialize( void ){ return true; }
	
	//	更新・描画
	virtual void	Update( void );
	virtual void	Render( iexShader* shader = nullptr, LPSTR technique = nullptr );
	void	BarRender( void );
	void	UpdateInfo( void );
	void	DamageEffectUpdate( void );
	void	AddMove( void );

	//	動作関数
	virtual	void	AngleAdjust( const Vector3& moveVec, float adjustSpeed );
	void	AngleAdjustParent( const Vector3& direction, float adjustSpeed );

	//	情報設定
	void	SetCollisionShape( void );
	void	SetPos( const Vector3& Pos );
	void	SetMove( const Vector3& Move );
	void	SetAngle( float Angle );
	void	SetScale( float Scale );
	virtual void	SetMotion( int motion );
	bool	SetMode( int nextMode );
	void	SetObj( iex3DObj* obj );

	//	情報取得
	LifeInfo&		GetLifeInfo( void );
	CollisionInfo GetCollisionInfo( void )const;
	Matrix		GetMatrix( void )const;
	Vector3	GetBonePos( int boneNum )const;
	Vector3	GetPos( void )const;
	Vector3	GetMove( void )const;
	Vector3	GetFront( void )const;
	Vector3	GetUp( void )const;
	Vector3	GetRight( void )const;
	float			GetAngle( void )const;
	int			GetMotion( void )const;
	int			GetMode( void )const;
	int			GetFrame( void )const;
};
