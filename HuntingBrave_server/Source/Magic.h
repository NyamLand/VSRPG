
#pragma once

//**************************************************************************
//
//	Magic�N���X
//
//**************************************************************************

//	include
#include	"Timer.h"

//	class
class Magic
{
private:
	Vector3	pos;
	Vector3	vec;
	Timer*		timer;
	float			speed;
	float			angle;
	float			radius;
	int			mode;
	int			id;
	bool			isHit;

public:
	//	�������E���
	Magic( void );
	~Magic( void );
	bool	Initialize( int id, const Vector3& pos, const Vector3& vec );

	//	�X�V
	bool	Update( void );

	//	����֐�
	void	Move( void );
	void	Scaling( void );

	//	���擾
	Vector3	GetPos( void )const;
	float			GetRadius( void )const;
	int			GetID( void )const;
};
