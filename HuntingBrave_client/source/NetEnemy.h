
#pragma once

//****************************************************************
//
//	NetEnemy�N���X
//
//****************************************************************

//	include

//	class
class NetEnemy
{
private:
	iex3DObj*	obj;
	Vector3	pos;
	float			radius;
	float			angle;
	bool			isAlive;

public:
	//	�������E���
	NetEnemy( void );
	~NetEnemy( void );
	void	Initialize( iex3DObj* org, const Vector3& Pos, float Angle );
	
	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );

	//	����֐�

	//	���ݒ�
	void	SetPos( const Vector3& pos );
	void	SetAngle( float angle );
	void	SetMotion( int motion );
	void	SetMesh( iex3DObj* mesh );

	//	���擾
	Vector3	GetPos( void )const;
	bool			GetIsAlive( void ){ return isAlive; }
};
