
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"Camera.h"
#include	"BaseChara.h"

//***************************************************************
//
//	BaseChara�N���X
//
//***************************************************************

//	�萔�l
#define	MOVE_RESISTANCE	0.9f

//------------------------------------------------------------------------------------
//	�O���[�o��
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	�������E���
//------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	BaseChara::BaseChara( void ) : obj( nullptr ),
		pos( 0.0f, 0.0f, 0.0f ), move( 0.0f, 0.0f, 0.0f ),
		angle(0.0f), scale(1.0f), speed(0.0f), mode(0), timer(0), step(0),
		initflag(false)
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

	//	���

//------------------------------------------------------------------------------------
//	�X�V�E�`��
//------------------------------------------------------------------------------------

	//	�X�V
	void	BaseChara::Update( void )
	{
		//	�e�폈��
		AddMove();

		//	���X�V
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

	//	�ړ��l���Z
	void	BaseChara::AddMove( void )
	{
		//	�ړ��l���Z
		pos += move;
		
		//	��R�l�v�Z
		move *= MOVE_RESISTANCE;
	}

//------------------------------------------------------------------------------------
//	����֐�
//------------------------------------------------------------------------------------

	//	��������
	void	BaseChara::AngleAdjust( const Vector3& targetVec, float adjustSpeed )
	{
		//	�J�����̑O�����������߂�
		Vector3	vEye = mainView->GetTarget() - mainView->GetPos();
		float	viewAngle = atan2f( vEye.x, vEye.z );

		//	�ړ����������߂�
		float	moveAngle = atan2f( targetVec.x, targetVec.z );

		//	�ڕW�̊p�x�����߂�
		float	targetAngle = viewAngle + moveAngle;

		//	�e�ɓ�����
		AngleAdjustParent(
			Vector3( sinf( targetAngle ), 0.0f, cosf( targetAngle ) ),
			adjustSpeed );
	}

	//	���������i�e�j
	void	BaseChara::AngleAdjustParent( const Vector3& direction, float adjustSpeed )
	{
		//	���݂̌����ƖڕW�̌����̍������߂�
		float	targetAngle( atan2f( direction.x, direction.z ) );

		//	�p�x�������߂�
		float	dAngle( targetAngle - GetAngle() );

		//	���̐��K��
		if ( dAngle > 1.0f * D3DX_PI )		dAngle -= 2.0f * D3DX_PI;
		if ( dAngle < -1.0f * D3DX_PI )	dAngle += 2.0f * D3DX_PI;

		//	����speed���k�߂�
		if ( dAngle > 0.0f )
		{
			dAngle -= adjustSpeed;
			if ( dAngle < 0.0f )	dAngle = 0.0f;
		}
		else
		{
			dAngle += adjustSpeed;
			if ( dAngle > 0.0f )	dAngle = 0.0f;
		}

		//	�����ɔ��f
		SetAngle( targetAngle - dAngle );

		//	�L�����N�^�[�̌�����PI�ȏ�ɂȂ�Ȃ��悤�ɂ���
		if ( GetAngle() >= 1.0f * D3DX_PI )	angle -= 2.0f * D3DX_PI;
		if ( GetAngle() <= -1.0f * D3DX_PI ) angle += 2.0f * D3DX_PI;
	}

//------------------------------------------------------------------------------------
//	���ݒ�
//------------------------------------------------------------------------------------

	//	���W�ݒ�
	void	BaseChara::SetPos( const Vector3& Pos )
	{
		pos = Pos;
	}

	//	�ړ��l�ݒ�
	void	BaseChara::SetMove( const Vector3& Move )
	{
		move = Move;
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

