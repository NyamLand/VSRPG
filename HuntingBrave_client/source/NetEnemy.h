
#pragma once

//****************************************************************
//
//	NetEnemyクラス
//
//****************************************************************

//	include
#include	"CharaInfo.h"

//	class
class NetEnemy
{
private:
	AttackInfo	attackInfo;
	iex3DObj*	obj;
	Vector3	pos;
	float			radius;
	float			angle;
	bool			isAlive;

public:
	//	初期化・解放
	NetEnemy( void );
	~NetEnemy( void );
	void	Initialize( iex3DObj* org, const Vector3& Pos, float Angle );
	
	//	更新・描画
	void	Update( void );
	void	Render( void );

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
	AttackInfo&	GetAttackInfo( void ){ return attackInfo; }
	Vector3	GetPos( void )const;
	bool			GetIsAlive( void ){ return isAlive; }
};
