
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
	float			angle;
	int			id;

public:
	//	初期化・解放
	Magic( void );
	~Magic( void );
	void	Initialize( iexMesh* org, const Vector3& Pos, float Angle );
	
	//	更新・描画
	void	Update( void );
	void	Render( void );

	//	動作関数

	//	情報設定
	void	SetPos( const Vector3& pos );
	void	SetMesh( iexMesh* mesh );

	//	情報取得
};
