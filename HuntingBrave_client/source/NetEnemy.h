
#pragma once

//****************************************************************
//
//	NetEnemyクラス
//
//****************************************************************

//	include
#include	"EnemyHp.h"
#include	"CharaInfo.h"

//	class
class NetEnemy
{
private:
	iex3DObj*	obj;
	Vector3	pos;
	EnemyHpUI*	bar;
	AttackInfo	attackInfo;
	float			radius;
	float			angle;
	bool			isAlive;
	int			life;
	int			index;

public:
	//	初期化・解放
	NetEnemy( void );
	~NetEnemy( void );
	void	Initialize( iex3DObj* org, const Vector3& Pos, float Angle );
	
	//	更新・描画
	void	Update( int index );
	void	Render( void );
	void	RenderHpBar( void );
	void	SendClientOK( void );
	
	//	動作関数
	void	Death( void );
	void	CheckAttackInfo( void );
	//	情報設定
	void	SetPos( const Vector3& pos );
	void	SetAngle( float angle );
	void	SetMotion( int motion );
	void	SetMesh( iex3DObj* mesh );
	void	SetDeath( void );

	//	情報取得
	Vector3	GetPos( void )const;
	bool			GetIsAlive( void ){ return isAlive; }
	int		GetLife( void )const{ return life; }
	Vector3	GetUp( void )const;
	AttackInfo&	GetAttackInfo( void ){ return attackInfo;  }
	Matrix	NetEnemy::GetMatrix( void )const;
};
