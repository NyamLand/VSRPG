
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameParam.h"
#include	"DrawShape.h"
#include	"Magic.h"

//***************************************************************
//
//	Magic�N���X
//
//***************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

#define	MAGIC_RADIUS	2.5f

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	Magic::Magic( void ) : obj( nullptr ),
		pos( 0.0f, 0.0f, 0.0f ), 
		angle( 0.0f ), radius( MAGIC_RADIUS )
	{
	
	}

	//	�f�X�g���N�^
	Magic::~Magic( void )
	{
		//SafeDelete( obj );
	}

	//	������
	void	Magic::Initialize( iexMesh* org, int id, const Vector3& Pos, float Angle )
	{
		this->pos = Pos;
		this->angle = Angle;
		this->id = id;
		obj = org;
		obj->SetPos( pos );
		obj->SetAngle( angle );
		obj->Update();
	}

//----------------------------------------------------------------------------------------------
//	�X�V�E�`��
//----------------------------------------------------------------------------------------------

	//	�X�V
	void	Magic::Update( void )
	{
		obj->SetPos( pos );
		obj->Update();
	}

	//	�`��
	void	Magic::Render( void )
	{
		obj->Render();
	}

//----------------------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------------------

	//	���W�ݒ�
	void	Magic::SetPos( const Vector3& pos )
	{
		this->pos = pos;
	}

	//	���b�V���ݒ�
	void	Magic::SetMesh( iexMesh*	mesh )
	{
		obj = mesh;
	}

//----------------------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------------------

	//	���W�擾
	Vector3	Magic::GetPos( void )const
	{
		return	pos;
	}

	//	���a�擾
	float			Magic::GetRadius( void )const
	{
		return	radius;
	}

	//	ID�擾
	int			Magic::GetID( void )const
	{
		return	id;
	}

	//	�s��擾
	Matrix	Magic::GetMatrix(void)const
	{
		return	obj->TransMatrix;
	}


	//	�O���擾
	Vector3	Magic::GetFront(void)const
	{
		Matrix mat = GetMatrix();
		Vector3	front = Vector3(mat._31, mat._32, mat._33);
		front.Normalize();
		return	front;
	}

	//	����擾
	Vector3	Magic::GetUp(void)const
	{
		Matrix mat = GetMatrix();
		Vector3	up = Vector3(mat._21, mat._22, mat._23);
		up.Normalize();
		return	up;
	}

	//	�E���擾
	Vector3	Magic::GetRight(void)const
	{
		Matrix mat = GetMatrix();
		Vector3	right = Vector3(mat._11, mat._12, mat._13);
		right.Normalize();
		return	right;
	}