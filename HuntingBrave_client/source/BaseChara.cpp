
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"DrawShape.h"
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
		angle( 0.0f ), scale( 1.0f ), speed( 0.0f ),
		mode( 0 )
	{
		//	�\���̏�����
		ZeroMemory( &attackInfo, sizeof( AttackInfo ) );
		ZeroMemory( &lifeInfo, sizeof( LifeInfo ) );
		ZeroMemory( &collisionInfo, sizeof( CollisionInfo ) );
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

		//drawShape->DrawCapsule( collisionInfo.collisionShape.capsule.p1, collisionInfo.collisionShape.capsule.p2, collisionInfo.radius, 0xFFFFFFFF );
	}

	//	���X�V
	void	BaseChara::UpdateInfo( void )
	{
		if ( obj == nullptr )
		{
			printf( "obj == nullptr\n" );
			return;
		}

		//	�����蔻��`��X�V
		SetCollisionShape();

		//	���f�����X�V
		obj->SetPos( pos );
		obj->SetAngle( angle );
		obj->SetScale( scale );
		obj->Update();
		obj->Animation();
		//obj->Animation();
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

	//	�����蔻��p�`��ݒ�
	void	BaseChara::SetCollisionShape( void )
	{
		switch ( collisionInfo.collisionShape.shapeType )
		{
		case SHAPE_TYPE::SPHERE:
			collisionInfo.collisionShape.SetSphere( 
				Sphere( 
					Vector3( pos.x, pos.y + collisionInfo.height, pos.z ), 
					collisionInfo.radius ) );
			break;

		case SHAPE_TYPE::CAPSULE:
			collisionInfo.collisionShape.SetCapsule(
				Capsule(
					Vector3( pos.x, pos.y + collisionInfo.radius, pos.z ), 
					Vector3( pos.x, pos.y + collisionInfo.height + collisionInfo.radius, pos.z ), 
					collisionInfo.radius ) );
			break;
		}
	}

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

	//	���[�h�ݒ�( �V�K���[�h�������Ȃ�false�������� )
	bool	BaseChara::SetMode( int nextMode )
	{
		if ( mode != nextMode )
		{
			mode = nextMode;
			return	true;
		}
		return	false;
	}

	//	���f���ݒ�
	void	BaseChara::SetObj( iex3DObj*	obj )
	{
		this->obj = obj;
	}

//------------------------------------------------------------------------------------
//	���擾
//------------------------------------------------------------------------------------

	//	�U�����擾
	AttackInfo	BaseChara::GetAttackInfo( void )const
	{
		return	attackInfo;
	}

	//	���C�t���擾
	LifeInfo&		BaseChara::GetLifeInfo( void )
	{
		return	lifeInfo;
	}

	//	�����蔻��p�`��擾
	CollisionInfo	BaseChara::GetCollisionInfo( void )const
	{
		return	collisionInfo;
	}

	//	�s��擾
	Matrix	BaseChara::GetMatrix( void )const
	{
		return	obj->TransMatrix;
	}

	//	�{�[�����W�擾
	Vector3	BaseChara::GetBonePos( int boneNum )const
	{
		Matrix boneMat = *obj->GetBone( boneNum ) * obj->TransMatrix;
		Vector3	bonePos = Vector3( boneMat._41, boneMat._42, boneMat._43 );
		return	bonePos;
	}

	//	���W�擾
	Vector3	BaseChara::GetPos( void )const
	{
		return	pos;
	}

	//	�ړ��l�擾
	Vector3	BaseChara::GetMove( void )const
	{
		return	move;
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

	//	���[�V�����擾
	int			BaseChara::GetMotion( void )const
	{
		return	obj->GetMotion();
	}

	//	���[�h�擾
	int			BaseChara::GetMode( void )const
	{
		return	mode;
	}

	//	�t���[���擾
	int			BaseChara::GetFrame( void )const
	{
		return	obj->GetFrame();
	}