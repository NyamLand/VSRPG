
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"Camera.h"

//***************************************************************
//
//	Camera�N���X
//
//***************************************************************

//----------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------

Camera* mainView = nullptr;

//	�萔
#define	MIN_INPUT_STICK	0.3f

//	HERFTOP_VIEW�p�����[�^�萔
#define HERFTOP_VIEW_DIST						20.0f
#define	HERFTOP_VIEW_HEIGHT				15.0f
#define	HERFTOP_VIEW_ROTATE_SPEED		D3DX_PI * 0.015f

//----------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------

	//	�R���X�g���N�^
	Camera::Camera( void ) : viewMode( VIEW_MODE::FIX_VIEW ),
		pos( 0.0f, 0.0f, 0.0f ), target( 0.0f, 0.0f, 0.0f ), rotateAngle( 0.0f )
	{
		//	�֐��|�C���^�̔z��ɐݒ�
		ViewUpdate[VIEW_MODE::FIX_VIEW] = &Camera::FixViewUpdate;
		ViewUpdate[VIEW_MODE::TRACKING_VIEW] = &Camera::TrackingViewUpdate;
		ViewUpdate[VIEW_MODE::THIRDPERSON_VIEW] = &Camera::ThirdPersonViewUpdate;
	}

	//	�f�X�g���N�^
	Camera::~Camera( void )
	{
		Release();
	}

	//	������
	bool Camera::Initialize( VIEW_MODE view_mode, const Vector3& Pos, const Vector3& Target )
	{
		//	�r���[���[�h�ۑ�
		viewMode = view_mode;

		//	���ۑ�
		pos = Pos;
		target = Target;
		
		//	���X�V
		UpdateInfo();

		return	true;
	}

	//	���
	void	Camera::Release( void )
	{

	}

//----------------------------------------------------------------------------------
//	�X�V�E�`��
//----------------------------------------------------------------------------------

	//	�X�V
	void	Camera::Update( const Vector3& Target )
	{
		//	�^�[�Q�b�g���W�ۑ�
		target = Target;

		//	�e�J��������
		( this->*ViewUpdate[ viewMode ] )();

		//	���X�V
		UpdateInfo();
	}

	//	���X�V
	void	Camera::UpdateInfo( void )
	{
		Set( pos, target );
	}
	
	//	�`��( ��Ƀf�o�b�O�p )
	void	Camera::Render( void )
	{

	}

//----------------------------------------------------------------------------------
//	�e�J�����X�V
//----------------------------------------------------------------------------------

	//	�Œ�J�����X�V
	void	Camera::FixViewUpdate( void )
	{
		//	�Œ�Ȃ̂ŉ������Ȃ�
		printf( "FixView\n" );
	}
	
	//	�ǐՃJ�����X�V( �n�[�t�g�b�v�r���[ )
	void	Camera::TrackingViewUpdate( void )
	{
		//	���̋����𗣂�
		pos = target + Vector3( 
			HERFTOP_VIEW_DIST * sinf( rotateAngle ), 
			HERFTOP_VIEW_HEIGHT, 
			HERFTOP_VIEW_DIST * -cosf( rotateAngle ) );

		//	��]
		HerfTopViewRotate();

		//	�p�x����
		AngleLimit();
	}

	//	�O�l�̃J�����X�V
	void	Camera::ThirdPersonViewUpdate( void )
	{

	}

//----------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------

	//	�J�����A���O������
	void	Camera::AngleLimit( void )
	{
		if ( rotateAngle > D3DX_PI * 2 )	rotateAngle = 0;
		else if ( rotateAngle < 0 )	rotateAngle = D3DX_PI * 2;
	}

	//	��]
	void	Camera::HerfTopViewRotate( void )
	{
		////	���͎擾
		//bool	pushR1 = UIPad[0]->GetR1Button( UIPad::BUTTON_STATE::STAY );
		//bool	pushL1 = UIPad[0]->GetL1Button( UIPad::BUTTON_STATE::STAY );

		////	��]
		//if ( pushR1 )
		//{
		//	rotateAngle -= HERFTOP_VIEW_ROTATE_SPEED;
		//}
		//else if ( pushL1 )
		//{
		//	rotateAngle += HERFTOP_VIEW_ROTATE_SPEED;
		//}
	}

	//	�U��
	void	Camera::Shake( void )
	{

	}
	
//----------------------------------------------------------------------------------
//	���ݒ�
//----------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
//	���擾
//----------------------------------------------------------------------------------

	//	���̎擾
	Camera*	Camera::GetInstance( void )
	{
		static Camera out;
		return	&out;
	}

	//	���W�擾
	Vector3	Camera::GetPos( void )const
	{
		return	pos;
	}

	//	�^�[�Q�b�g�擾
	Vector3	Camera::GetTarget( void )const 
	{
		return	target;
	}

	//	�s��擾
	Matrix	Camera::GetMatrix( void )const
	{
		return	this->matView;
	}
