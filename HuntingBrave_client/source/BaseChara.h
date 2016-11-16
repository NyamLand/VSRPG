
#pragma once

//***************************************************************
//
//	BaseChara�N���X
//
//***************************************************************

//	include
#include	"CharaInfo.h"

//	class
class BaseChara
{
protected:
	//	���f��
	iex3DObj*	obj;

	//	�p�����[�^
	Vector3		pos;
	Vector3		move;
	float			angle;
	float			speed;
	float			scale;
	int				mode;
	CollisionInfo	collisionInfo;
	AttackInfo		attackInfo;
	LifeInfo			lifeInfo;

public:
	//	�������E���
	BaseChara( void );
	virtual ~BaseChara( void );
	bool	Load( LPSTR filename );
	virtual bool Initialize( void ){ return true; }
	
	//	�X�V�E�`��
	virtual void	Update( void );
	virtual void	Render( iexShader* shader = nullptr, LPSTR technique = nullptr );
	void	UpdateInfo( void );
	void	AddMove( void );

	//	����֐�
	void	AngleAdjust( const Vector3& moveVec, float adjustSpeed );
	void	AngleAdjustParent( const Vector3& direction, float adjustSpeed );

	//	���ݒ�
	void	SetCollisionShape( void );
	void	SetPos( const Vector3& Pos );
	void	SetMove( const Vector3& Move );
	void	SetAngle( float Angle );
	void	SetScale( float Scale );
	void	SetMotion( int motion );
	bool	SetMode( int nextMode );
	void	SetObj( iex3DObj* obj );

	//	���擾
	AttackInfo	GetAttackInfo( void )const;
	LifeInfo&		GetLifeInfo( void );
	CollisionInfo GetCollisionInfo( void )const;
	Matrix		GetMatrix( void )const;
	Vector3	GetBonePos( int boneNum )const;
	Vector3	GetPos( void )const;
	Vector3	GetMove( void )const;
	Vector3	GetFront( void )const;
	Vector3	GetUp( void )const;
	Vector3	GetRight( void )const;
	float			GetAngle( void )const;
	int			GetMotion( void )const;
	int			GetMode( void )const;
	int			GetFrame( void )const;
};
