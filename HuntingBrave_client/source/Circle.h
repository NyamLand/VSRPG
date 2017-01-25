
#pragma once

//***************************************************************
//
//	ExpUI�N���X
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
	//	�������E���
	Circle( int index );
	virtual	~Circle( void );

	//	�X�V�E�`��
	void	Update(void );
	void	Render( void );

	void	Spin( void );
	void	CalcVertex( );

	//	���ݒ�E�擾
	void	PoligonSet( const Vector3& pos, float size );
	void	SetPos( Vector3 pos ) { this->c_pos = pos; }
	void	SetRender( bool flag );

};



