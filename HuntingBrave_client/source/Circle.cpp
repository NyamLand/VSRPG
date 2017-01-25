
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"system\System.h"
#include	"GameParam.h"
#include	"Interpolation.h"
#include	"Circle.h"

//***************************************************************
//
//	Circle�N���X
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	�O���[�o��	
//---------------------------------------------------------------------------------------

namespace
{
	const float HEIGHT = 0.5f;
}

//---------------------------------------------------------------------------------------
//	�������E���
//---------------------------------------------------------------------------------------

//	�R���X�g���N�^
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

//	�f�X�g���N�^
Circle::~Circle(void)
{
	SafeDelete( pic );
}



//---------------------------------------------------------------------------------------
//	�X�V
//---------------------------------------------------------------------------------------

//	�X�V
void	Circle::Update(void)
{
	angle += D3DXToRadian(1);
	if (!renderflag) return;

	Interpolation::PercentageUpdate(percentage, 0.02);

	PoligonSet(gameParam->GetPlayerParam(p_num).pos, size * percentage);

	
}

//---------------------------------------------------------------------------------------
//	�`��
//---------------------------------------------------------------------------------------

//	�`��
void	Circle::Render(void)
{
	if (!renderflag) return;
	iexPolygon::Render3D(poligon, 2, pic, shader3D, "alpha");
}

//---------------------------------------------------------------------------------------
//	����֐�
//---------------------------------------------------------------------------------------

//	��]
void	Circle::Spin(void)
{
	
}


//---------------------------------------------------------------------------------------
//	���ݒ�
//---------------------------------------------------------------------------------------

//
void	Circle::SetRender( bool flag )
{
	percentage = 0.0f;
	renderflag = flag;
}


//	���_���ݒ�
void	Circle::PoligonSet(const Vector3& pos, float size )
{
	//	�L�����N�^�[���݂̃|�W�V����
	c_pos = pos;

	//	�ۑ�
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


	//	��]�E���_�Z�b�g
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

