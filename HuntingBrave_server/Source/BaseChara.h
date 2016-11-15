
#pragma once

//*****************************************************************************************************************************
//
//	BaseChara�N���X
//
//*****************************************************************************************************************************

//	include

//	enum
namespace MODE
{
	//	���[�h�ԍ�
	enum 
	{
		MOVE,
		SWOADATTACK,
		MAGICATTACK,
		AVOID,
		MODE_MAX
	};
}

//	class
class BaseChara
{
protected:
	Vector3	pos;
	float		angle;
	int			mode;
	int			motion;

public:
	//	�������E���
	BaseChara( void );
	virtual ~BaseChara( void );
	
	//	���ݒ�
	bool	SetMode( int nextMode );

	//	���擾
	Vector3	GetPos( void )const;
};
