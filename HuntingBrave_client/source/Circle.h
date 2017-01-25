
#pragma once

//***************************************************************
//
//	ExpUIクラス
//
//***************************************************************

//	class
class Circle
{
private:
	LVERTEX		poligon[4];
	Vector3		c_pos;
	iex2DObj*	pic;
	Vector3		save_pos[4];
	float		angle;
	int			p_num;

	float		percentage;
	bool		renderflag;
	float		size;
public:
	//	初期化・解放
	Circle( int index );
	virtual	~Circle( void );

	//	更新・描画
	void	Update(void );
	void	Render( void );

	void	Spin( void );
	void	CalcVertex( );

	//	情報設定・取得
	void	PoligonSet( const Vector3& pos, float size );
	void	SetPos( Vector3 pos ) { this->c_pos = pos; }
	void	SetRender( bool flag );

};



