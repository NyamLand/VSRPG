
#pragma once

//****************************************************************
//
//	Magicクラス
//
//****************************************************************

//	include

//	class
class Magic
{
private:
	iexMesh*	obj;
	Vector3	pos;
	float			radius;
	float			angle;
	int			id;

public:
	//	初期化・解放
	Magic( void );
	~Magic( void );
	void	Initialize( iexMesh* org, int id, const Vector3& Pos, float Angle );
	
	//	更新・描画
	void	Update( void );
	void	Render( void );

	//	動作関数

	//	情報設定
	void	SetPos( const Vector3& pos );
	void	SetMesh( iexMesh* mesh );

	//	情報取得
	Vector3	GetPos( void )const;
	Vector3	GetFront( void )const;
	Vector3	GetRight( void )const;
	Vector3	GetUp( void )const;
	Matrix	GetMatrix( void )const;
	float			GetRadius( void )const;
	int			GetID( void )const;
};
