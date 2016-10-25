
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"DrawShape.h"

//**********************************************************************
//
//	DrawShapeクラス
//
//**********************************************************************

//-------------------------------------------------------------------------
//	初期化・解放
//-------------------------------------------------------------------------

	//	コンストラクタ
	DrawShape::DrawShape( void ) : cube( NULL ), sphere( NULL ) 
	{
		Initialize();
	}

	//	デストラクタ
	DrawShape::~DrawShape( void )
	{
		Release();
	}

	//	初期化
	bool	DrawShape::Initialize( void )
	{
		//	sphere作成
		D3DXCreateSphere( iexSystem::GetDevice(), 1.0f, 32, 16, &sphere, NULL );

		//	cube作成
		D3DXCreateBox( iexSystem::GetDevice(), 1.0f, 1.0f, 1.0f, &cube, NULL );

		return	true;
	}

	//	解放
	void	DrawShape::Release( void )
	{
		sphere->Release();
		cube->Release();
	}

//-------------------------------------------------------------------------
//	図形描画
//-------------------------------------------------------------------------

	//	球描画
	void	DrawShape::DrawSphere( LPDIRECT3DDEVICE9 d3dd, CONST D3DXVECTOR3 &p0, FLOAT r, D3DCOLOR c )
	{
		CONST INT N = 36;

		static _VB vb(d3dd, sizeof(D3DXVECTOR3)* (N + 1));
		for (int n = 0; n < 3; n++)
		{
			D3DXVECTOR3 *p;
			vb->Lock(0, 0, (void **)&p, 0);
			for (int i = 0; i < N; i++)
			{
				switch (n)
				{
				case 0: p[i] = r * D3DXVECTOR3(sinf(360.0f / N * 0.01745f * i), cosf(360.0f / N * 0.01745f * i), 0) + p0; break;
				case 1: p[i] = r * D3DXVECTOR3(sinf(360.0f / N * 0.01745f * i), 0, cosf(360.0f / N * 0.01745f * i)) + p0; break;
				case 2: p[i] = r * D3DXVECTOR3(0, sinf(360.0f / N * 0.01745f * i), cosf(360.0f / N * 0.01745f * i)) + p0; break;
				}
			}
			p[N] = p[0];
			vb->Unlock();

			D3DMATERIAL9 m = { 0 };
			m.Diffuse = m.Ambient = D3DXCOLOR(c);
			d3dd->SetMaterial(&m);

			d3dd->SetFVF(D3DFVF_XYZ);
			d3dd->SetStreamSource(0, vb, 0, sizeof(D3DXVECTOR3));
			d3dd->SetTransform(D3DTS_WORLD, &D3DXMATRIX(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
			d3dd->DrawPrimitive(D3DPT_LINESTRIP, 0, N);
		}
	}

	void	DrawShape::DrawSphere( const Vector3& pos, float r, DWORD color )
	{
		iexSystem::GetDevice()->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		DrawSphere(iexSystem::GetDevice(), D3DXVECTOR3(pos.x, pos.y, pos.z), r, color);
		iexSystem::GetDevice()->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	}

	//	カプセル描画
	void	DrawShape::DrawCapsule( LPDIRECT3DDEVICE9 d3dd, CONST D3DXVECTOR3 &p0, CONST D3DXVECTOR3 &p1, FLOAT r, D3DCOLOR c )
	{
		CONST INT N = 36;
		CONST INT L0 = 0;
		CONST INT L1 = N + 1;
		CONST INT L2 = L1 + N + 1;

		CONST INT L3 = L2 + N * 2;
		CONST INT L4 = L3 + N + 1;
		CONST INT L5 = L4 + N + 1;
		CONST INT L6 = L5 + N + 1;

		static _VB vb(d3dd, sizeof(D3DXVECTOR3)* ((N + 1) * 2 + N * 2 + (N + 1) * 4));
		D3DXVECTOR3 *p;
		vb->Lock(0, 0, (void **)&p, 0);
		D3DXVECTOR3 up = p0 - p1;
		CONST FLOAT L = D3DXVec3Length(&up);
		for (int i = 0; i < N; i++)
		{
			p[L0 + i] = D3DXVECTOR3(r * sinf(360.0f / N * 0.01745f * i), L / 2.0f, r * cosf(360.0f / N * 0.01745f * i));
			p[L1 + i] = D3DXVECTOR3(r * sinf(360.0f / N * 0.01745f * i), -L / 2.0f, r * cosf(360.0f / N * 0.01745f * i));
			if (i % (N / 4) == 0)
			{
				p[L2 + 2 * i] = p[L0 + i];
				p[L2 + 2 * i + 1] = p[L1 + i];
			}
			p[L3 + i] = D3DXVECTOR3(r * cosf(180.0f / N * 0.01745f * i), r * sinf(180.0f / N * 0.01745f * i) + L / 2.0f, 0);
			p[L4 + i] = D3DXVECTOR3(0, r * sinf(180.0f / N * 0.01745f * i) + L / 2.0f, r * cosf(180.0f / N * 0.01745f * i));
			p[L5 + i] = D3DXVECTOR3(r * cosf(180.0f / N * 0.01745f * i), -r * sinf(180.0f / N * 0.01745f * i) - L / 2.0f, 0);
			p[L6 + i] = D3DXVECTOR3(0, -r * sinf(180.0f / N * 0.01745f * i) - L / 2.0f, r * cosf(180.0f / N * 0.01745f * i));
		}
		p[L0 + N] = p[L0];
		p[L1 + N] = p[L1];
		p[L3 + N] = D3DXVECTOR3(-r, L / 2.0f, 0);
		p[L4 + N] = D3DXVECTOR3(0, L / 2.0f, -r);
		p[L5 + N] = D3DXVECTOR3(-r, L / 2.0f, 0);
		p[L6 + N] = D3DXVECTOR3(0, L / 2.0f, -r);

		vb->Unlock();

		D3DXVECTOR3 axis;
		D3DXVec3Cross(&axis, &D3DXVECTOR3(0, 1, 0), &up);
		D3DXVec3Normalize(&axis, &axis);
		FLOAT angle = acosf(D3DXVec3Dot(&up, &D3DXVECTOR3(0, 1, 0)) / D3DXVec3Length(&up));
		D3DXMATRIX M;
		D3DXMatrixRotationAxis(&M, &axis, angle);
		D3DXVECTOR3 g = (p0 + p1) / 2;
		M._41 = g.x;
		M._42 = g.y;
		M._43 = g.z;

		D3DMATERIAL9 m = { 0 };
		m.Diffuse = m.Ambient = D3DXCOLOR(c);
		d3dd->SetMaterial(&m);

		d3dd->SetFVF(D3DFVF_XYZ);
		d3dd->SetStreamSource(0, vb, 0, sizeof(D3DXVECTOR3));
		d3dd->SetTransform(D3DTS_WORLD, &M);
		d3dd->DrawPrimitive(D3DPT_LINESTRIP, L0, N);
		d3dd->DrawPrimitive(D3DPT_LINESTRIP, L1, N);
		d3dd->DrawPrimitive(D3DPT_LINELIST, L2, N);
		d3dd->DrawPrimitive(D3DPT_LINESTRIP, L3, N);
		d3dd->DrawPrimitive(D3DPT_LINESTRIP, L4, N);
		d3dd->DrawPrimitive(D3DPT_LINESTRIP, L5, N);
		d3dd->DrawPrimitive(D3DPT_LINESTRIP, L6, N);
	}

	void	DrawShape::DrawCapsule( const Vector3& p1, const Vector3& p2, float r, DWORD color )
	{
		iexSystem::GetDevice()->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		DrawCapsule(iexSystem::GetDevice(), D3DXVECTOR3(p1.x, p1.y, p1.z), D3DXVECTOR3(p2.x, p2.y, p2.z), r, color);
		iexSystem::GetDevice()->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	}

	//	線描画
	void DrawShape::DrawLine( LPDIRECT3DDEVICE9 d3dd, CONST D3DXVECTOR3 &p0, CONST D3DXVECTOR3 &p1, D3DCOLOR c )
	{
		static _VB vb(d3dd, sizeof(D3DXVECTOR3)* 2);

		D3DXVECTOR3 *p;
		vb->Lock(0, 0, (void **)&p, 0);
		p[0] = p0;
		p[1] = p1;
		vb->Unlock();

		D3DMATERIAL9 m = { 0 };
		m.Diffuse = m.Ambient = D3DXCOLOR(c);
		d3dd->SetMaterial(&m);

		d3dd->SetFVF(D3DFVF_XYZ);
		d3dd->SetStreamSource(0, vb, 0, sizeof(D3DXVECTOR3));
		d3dd->SetTransform(D3DTS_WORLD, &D3DXMATRIX(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
		d3dd->DrawPrimitive(D3DPT_LINELIST, 0, 1);
	}

	void	DrawShape::DrawLine( const Vector3& p1, const Vector3& p2, DWORD color )
	{
		iexSystem::GetDevice()->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		DrawLine(iexSystem::GetDevice(), D3DXVECTOR3(p1.x, p1.y, p1.z), D3DXVECTOR3(p2.x, p2.y, p2.z), color);
		iexSystem::GetDevice()->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	}

	//	球メッシュ描画
	void	DrawShape::DrawSphereMesh( LPDIRECT3DDEVICE9 d3dd, CONST D3DXVECTOR3& pos, FLOAT r, D3DCOLOR c )
	{
		//	変数準備
		D3DMATERIAL9 m = { 0 };
		D3DXMATRIX M, T, S;

		//	マテリアル設定
		d3dd->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID );
		m.Ambient = m.Diffuse = D3DXCOLOR( c );
		d3dd->SetMaterial( &m );
		
		//	スケール設定
		D3DXMatrixScaling( &S, r, r, r );

		//	座標設定
		D3DXMatrixTranslation( &T, pos.x, pos.y, pos.z );

		//	合成
		M = S * T;

		//	ワールド変換
		d3dd->SetTransform( D3DTS_WORLD, &M );

		//	描画
		sphere->DrawSubset( 0 );
	}

	//	球メッシュ描画
	void	DrawShape::DrawSphereMesh( const Vector3& pos, float r, DWORD color )
	{
		DrawSphereMesh( iexSystem::Device, D3DXVECTOR3( pos.x, pos.y, pos.z ), r, color );
	}

	//	キューブメッシュ描画
	void	DrawShape::DrawCubeMesh( LPDIRECT3DDEVICE9 d3dd, CONST D3DXVECTOR3& pos, CONST D3DXVECTOR3& size, D3DCOLOR c )
	{
		//	変数準備
		D3DMATERIAL9 m = { 0 };
		D3DXMATRIX M, T, R, S;

		//	マテリアル設定
		d3dd->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
		m.Ambient = m.Diffuse = D3DXCOLOR( c );
		d3dd->SetMaterial( &m );

		//	スケール設定
		D3DXMatrixScaling( &S, size.x, size.y, size.z );
		
		//	座標設定
		D3DXMatrixTranslation( &T, pos.x, pos.y, pos.z );

		//	合成
		M = S * T;
		
		//	ワールド変換
		d3dd->SetTransform( D3DTS_WORLD, &M );

		//	描画
		cube->DrawSubset( 0 );
	}

	//	キューブメッシュ描画
	void	DrawShape::DrawCubeMesh( const Vector3& pos, const Vector3& size, DWORD color )
	{
		DrawCubeMesh( iexSystem::Device, D3DXVECTOR3( pos.x, pos.y, pos.z ), D3DXVECTOR3( size.x, size.y, size.z ), color );
	}
