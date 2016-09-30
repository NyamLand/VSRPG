
#pragma once 

//**********************************************************************
//
//	DrawShapeクラス
//
//**********************************************************************

class DrawShape
{
private:
	LPD3DXMESH cube;
	LPD3DXMESH	sphere;

public:
	//	初期化・解放
	DrawShape( void );
	~DrawShape( void );
	bool	Initialize( void );
	void	Release( void );

	//---------------図形描画---------------//

	//	球描画
	void		DrawSphere( LPDIRECT3DDEVICE9 d3dd, CONST D3DXVECTOR3& p0, FLOAT r, D3DCOLOR c );
	void		DrawSphere( const Vector3& pos, float r, DWORD color );
	
	//	カプセル描画
	void		DrawCapsule( LPDIRECT3DDEVICE9 d3dd, CONST D3DXVECTOR3 &p0, CONST D3DXVECTOR3 &p1, FLOAT r, D3DCOLOR c );
	void		DrawCapsule( const Vector3& p1, const Vector3& p2, float r, DWORD color );
	
	//	線描画
	void		DrawLine( LPDIRECT3DDEVICE9 d3dd, CONST D3DXVECTOR3 &p0, CONST D3DXVECTOR3 &p1, D3DCOLOR c );
	void		DrawLine( const Vector3& p1, const Vector3& p2, DWORD color );

	//	球メッシュ描画
	void		DrawSphereMesh( LPDIRECT3DDEVICE9 d3dd, CONST D3DXVECTOR3& pos, FLOAT r, D3DCOLOR c );
	void		DrawSphereMesh( const Vector3& pos, float r, DWORD color );

	//	立方体描画
	void		DrawCubeMesh( LPDIRECT3DDEVICE9 d3dd, CONST D3DXVECTOR3& pos, CONST D3DXVECTOR3& size, D3DCOLOR c );
	void		DrawCubeMesh( const Vector3& pos, const Vector3& size, DWORD color );

	//	情報取得
	static DrawShape*	GetInstance( void );
};

#define	drawShape ( DrawShape::GetInstance() )