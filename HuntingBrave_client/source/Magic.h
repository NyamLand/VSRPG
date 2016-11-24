
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
	float			angle;
	int			id;

public:
	//	�������E���
	Magic( void );
	~Magic( void );
	void	Initialize( iexMesh* org, const Vector3& Pos, float Angle );
	
	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );

	//	����֐�

	//	���ݒ�
	void	SetPos( const Vector3& pos );
	void	SetMesh( iexMesh* mesh );

	//	���擾
};
