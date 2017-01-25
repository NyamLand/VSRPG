
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameParam.h"
#include	"DrawShape.h"
#include	"NetEnemy.h"

//***************************************************************
//
//	NetEnemy�N���X
//
//***************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------
#define INIT_LIFE	20
//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
NetEnemy::NetEnemy(void) : obj(nullptr), bar(nullptr),
		pos( 0.0f, 0.0f, 0.0f ), 
		angle( 0.0f ),
		life(0),
		isAlive( false )
	{
		ZeroMemory( &attackInfo, sizeof( attackInfo ) );
	}

	//	�f�X�g���N�^
	NetEnemy::~NetEnemy( void )
	{
		//SafeDelete( obj );
		SafeDelete(bar);
	}

	//	������
	void	NetEnemy::Initialize( iex3DObj* org, const Vector3& Pos, float Angle )
	{
		life = INIT_LIFE;
		this->pos = Pos;
		this->angle = Angle;
		obj = org;
		obj->SetPos( pos );
		obj->SetAngle( angle );
		obj->Update();
		bar = new EnemyHpUI();
		bar->Initilaize(HPUI_TYPE::ENEMY, GetLife());
	}

//----------------------------------------------------------------------------------------------
//	�X�V�E�`��
//----------------------------------------------------------------------------------------------

	//	�X�V
	void	NetEnemy::Update( void )
	{
		obj->SetPos( pos );
		obj->SetAngle( angle );
		obj->Update();
		obj->Animation();
	}

	//	�`��
	void	NetEnemy::Render( void )
	{
		obj->Render();
	}

	//	HP�o�[�`��
	void	NetEnemy::RenderHpBar(void)
	{
		bar->Render((float)GetLife(), GetPos(), GetUp());
	}

//----------------------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------------------

	//	���W�ݒ�
	void	NetEnemy::SetPos( const Vector3& pos )
	{
		this->pos = pos;
	}

	//	�����ݒ�
	void	NetEnemy::SetAngle( float angle )
	{
		this->angle = angle;
	}

	//	���[�V�����ݒ�
	void	NetEnemy::SetMotion( int motion )
	{
		if ( obj->GetMotion() != motion )
		{
			obj->SetMotion( motion );
		}
	}

	//	���b�V���ݒ�
	void	NetEnemy::SetMesh( iex3DObj*	mesh )
	{
		obj = mesh;
	}

//----------------------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------------------

	//	���W�擾
	Vector3	NetEnemy::GetPos( void )const
	{
		return	pos;
	}

	//	����擾
	Vector3	NetEnemy::GetUp(void)const
	{
		Matrix mat = GetMatrix();
		Vector3	up = Vector3(mat._21, mat._22, mat._23);
		up.Normalize();
		return	up;
	}

	//	�s��擾
	Matrix	NetEnemy::GetMatrix(void)const
	{
		return	obj->TransMatrix;
	}