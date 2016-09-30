
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"BaseChara.h"

//***************************************************************
//
//	BaseChara�N���X
//
//***************************************************************

//------------------------------------------------------------------------------------
//	�O���[�o��
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	�������E���
//------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	BaseChara::BaseChara( void ) : obj( nullptr ),
		pos( 0.0f, 0.0f, 0.0f ), 
		angle( 0.0f ), scale( 1.0f )
	{
	
	}

	//	�f�X�g���N�^
	BaseChara::~BaseChara( void )
	{
		SafeDelete( obj );
	}

	//	�ǂݍ���
	bool	BaseChara::Load( LPSTR filename )
	{
		obj = new iex3DObj( filename );

		if ( obj == nullptr )
		{
			printf( "�ǂݍ��ݎ��s\n" );
			return false;
		}
		return	true;
	}

	//	������

	//	���

//------------------------------------------------------------------------------------
//	�X�V�E�`��
//------------------------------------------------------------------------------------

	//	�X�V
	void	BaseChara::Update( void )
	{
		UpdateInfo();
	}

	//	�`��
	void	BaseChara::Render( iexShader* shader, LPSTR technique )
	{
		if ( shader == nullptr || technique == nullptr )
		{
			obj->Render();
		}
		else
		{
			obj->Render( shader, technique );
		}
	}

	//	���X�V
	void	BaseChara::UpdateInfo( void )
	{
		if ( obj == nullptr )
		{
			printf( "obj == nullptr\n" );
			return;
		}

		obj->Animation();
		obj->SetPos( pos );
		obj->SetAngle( angle );
		obj->SetScale( scale );
		obj->Update();
	}

//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	���ݒ�
//------------------------------------------------------------------------------------

	//	���W�ݒ�
	void	BaseChara::SetPos( const Vector3& Pos )
	{
		pos = Pos;
	}

	//	�����ݒ�
	void	BaseChara::SetAngle( float Angle )
	{
		angle = Angle;
	}

	//	�X�P�[���ݒ�
	void	BaseChara::SetScale( float Scale )
	{
		scale = Scale;
	}

	//	���[�V�����ݒ�
	void	BaseChara::SetMotion( int motion )
	{
		if ( obj->GetMotion() != motion )
		{
			obj->SetMotion( motion );
		}
	}

//------------------------------------------------------------------------------------
//	���擾
//------------------------------------------------------------------------------------

	//	�s��擾
	Matrix	BaseChara::GetMatrix( void )const
	{
		return	obj->TransMatrix;
	}

	//	���W�擾
	Vector3	BaseChara::GetPos( void )const
	{
		return	pos;
	}

	//	�O���擾
	Vector3	BaseChara::GetFront( void )const
	{
		Matrix mat = GetMatrix();
		Vector3	front = Vector3( mat._31, mat._32, mat._33 );
		front.Normalize();
		return	front;
	}

	//	����擾
	Vector3	BaseChara::GetUp( void )const
	{
		Matrix mat = GetMatrix();
		Vector3	up = Vector3( mat._21, mat._22, mat._23 );
		up.Normalize();
		return	up;
	}

	//	�E���擾
	Vector3	BaseChara::GetRight( void )const
	{
		Matrix mat = GetMatrix();
		Vector3	right = Vector3( mat._11, mat._12, mat._13 );
		right.Normalize();
		return	right;
	}

	//	�����ݒ�
	float		BaseChara::GetAngle( void )const
	{
		return	angle;
	}

