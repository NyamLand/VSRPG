
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"system\System.h"
#include	"GameParam.h"
#include	"Interpolation.h"
#include	"Circle.h"

//***************************************************************
//
//	Circleクラス
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	グローバル	
//---------------------------------------------------------------------------------------

namespace
{
	const float HEIGHT = 0.5f;
}

//---------------------------------------------------------------------------------------
//	初期化・解放
//---------------------------------------------------------------------------------------

//	コンストラクタ
Circle::Circle( int index ) : c_pos( 0.0f, 0.0f, 0.0f ), angle( 0.0f ), p_num( index ), size( 3.0f ),
								renderflag(false)
{
	pic = new iex2DObj("DATA/Effect/magic/MagicEffect01.png");
	PoligonSet(Vector3(0.0f, 0.0f, 0.0f), 0);
	for (int i = 0; i < 4; i++)
	{
		save_pos[i] = Vector3(0.0f, 0.0f, 0.0f);
	}
}

//	デストラクタ
Circle::~Circle(void)
{
	SafeDelete( pic );
}



//---------------------------------------------------------------------------------------
//	更新
//---------------------------------------------------------------------------------------

//	更新
void	Circle::Update(void)
{
	angle += D3DXToRadian(1);
	if (!renderflag) return;

	Interpolation::PercentageUpdate(percentage, 0.02);

	PoligonSet(gameParam->GetPlayerParam(p_num).pos, size * percentage);

	
}

//---------------------------------------------------------------------------------------
//	描画
//---------------------------------------------------------------------------------------

//	描画
void	Circle::Render(void)
{
	if (!renderflag) return;
	iexPolygon::Render3D(poligon, 2, pic, shader3D, "alpha");
}

//---------------------------------------------------------------------------------------
//	動作関数
//---------------------------------------------------------------------------------------

//	回転
void	Circle::Spin(void)
{
	
}


//---------------------------------------------------------------------------------------
//	情報設定
//---------------------------------------------------------------------------------------

//
void	Circle::SetRender( bool flag )
{
	percentage = 0.0f;
	renderflag = flag;
}


//	頂点情報設定
void	Circle::PoligonSet(const Vector3& pos, float size )
{
	//	キャラクター現在のポジション
	c_pos = pos;

	//	保存
	save_pos[0].x		= -size		+ pos.x;
	save_pos[0].y		= HEIGHT	+ pos.y;
	save_pos[0].z		= size		+ pos.z;

	save_pos[1].x		= size		+ pos.x;
	save_pos[1].y		= HEIGHT	+ pos.y;
	save_pos[1].z		= size		+ pos.z;
	
	save_pos[2].x		= -size		+ pos.x;
	save_pos[2].y		= HEIGHT	+ pos.y;
	save_pos[2].z		= -size		+ pos.z;


	save_pos[3].x		= size		+ pos.x;
	save_pos[3].y		= HEIGHT	+ pos.y;
	save_pos[3].z		= -size		+ pos.z;


	//	回転・頂点セット
	poligon[0].x		= sinf(angle) * (save_pos[0].x - c_pos.x) - cosf(angle) * (save_pos[0].z - c_pos.z) + c_pos.x;
	poligon[0].y		= save_pos[0].y;
	poligon[0].z		= cosf(angle) * (save_pos[0].x - c_pos.x) + sinf(angle) * (save_pos[0].z - c_pos.z) + c_pos.z;
	poligon[0].tu		= 0.0f;			
	poligon[0].tv		= 0.0f;			
	poligon[0].color	= 0xFFFFFFFF;	
										
	poligon[1].x		= sinf(angle) * (save_pos[1].x - c_pos.x) - cosf(angle) * (save_pos[1].z - c_pos.z) + c_pos.x;
	poligon[1].y		= save_pos[1].y;
	poligon[1].z		= cosf(angle) * (save_pos[1].x - c_pos.x) + sinf(angle) * (save_pos[1].z - c_pos.z) + c_pos.z;
	poligon[1].tu		= 1.0f;			
	poligon[1].tv		= 0.0f;			
	poligon[1].color	= 0xFFFFFFFF;	
										
										
	poligon[2].x		= sinf(angle) * (save_pos[2].x - c_pos.x) - cosf(angle) * (save_pos[2].z - c_pos.z) + c_pos.x;
	poligon[2].y		= save_pos[2].y;
	poligon[2].z		= cosf(angle) * (save_pos[2].x - c_pos.x) + sinf(angle) * (save_pos[2].z - c_pos.z) + c_pos.z;
	poligon[2].tu		= 0.0f;			
	poligon[2].tv		= 1.0f;			
	poligon[2].color	= 0xFFFFFFFF;	
										
										
	poligon[3].x		= sinf(angle) * (save_pos[3].x - c_pos.x) - cosf(angle) * (save_pos[3].z - c_pos.z) + c_pos.x;
	poligon[3].y		= save_pos[3].y;
	poligon[3].z		= cosf(angle) * (save_pos[3].x - c_pos.x) + sinf(angle) * (save_pos[3].z - c_pos.z) + c_pos.z;
	poligon[3].tu		= 1.0f;
	poligon[3].tv		= 1.0f;
	poligon[3].color	= 0xFFFFFFFF;

}

