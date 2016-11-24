
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

	//	���ݒ�
	Vector3	GetPos( void )const;

	//	���擾
};
