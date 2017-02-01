
#pragma once

//****************************************************************
//
//	Magic�N���X
//
//****************************************************************

//	include

//	class
class Magic
{
private:
	iexMesh*	obj;
	Vector3	pos;
	float			radius;
	float			angle;
	int			id;

public:
	//	�������E���
	Magic( void );
	~Magic( void );
	void	Initialize( iexMesh* org, int id, const Vector3& Pos, float Angle );
	
	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );

	//	����֐�

	//	���ݒ�
	void	SetPos( const Vector3& pos );
	void	SetMesh( iexMesh* mesh );

	//	���擾
	Vector3	GetPos( void )const;
	Vector3	GetFront( void )const;
	Vector3	GetRight( void )const;
	Vector3	GetUp( void )const;
	Matrix	GetMatrix( void )const;
	float			GetRadius( void )const;
	int			GetID( void )const;
};
