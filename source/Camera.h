
#pragma once

//***************************************************************
//
//	Camera�N���X
//
//***************************************************************

//	include

//	class
class Camera : public iexView
{
public:
	//	�萔
	enum VIEW_MODE
	{
		FIX_VIEW,
		THIRDPERSON_VIEW,
		TRACKING_VIEW,
		MAX
	};

private:
	//	�p�����[�^
	VIEW_MODE viewMode;
	Vector3	pos;
	Vector3	target;
	float rotateAngle;

	//	�X�V�֐��|�C���^
	void( Camera::*ViewUpdate[MAX] )( void );

private:

public:
	//	�������E���
	Camera( void );
	~Camera( void );
	bool Initialize( VIEW_MODE view_mode, const Vector3& Pos, const Vector3& Target  );
	void Release( void );

	//	�X�V�E�`��
	void	Update( const Vector3& Taget );
	void	UpdateInfo( void );
	void	Render( void );

	//	�e�J��������֐�
	void	FixViewUpdate( void );
	void	TrackingViewUpdate( void );
	void	ThirdPersonViewUpdate( void );
	
	//	����֐�
	void	AngleLimit( void );
	void	HerfTopViewRotate( void );
	void	Shake( void );

	//	���ݒ�

	//	���擾
	static Camera* GetInstance( void );
	Vector3	GetPos( void )const;
	Vector3	GetTarget( void )const;
	Matrix	GetMatrix( void )const;
};

extern Camera* mainView;
