
#pragma once

//*****************************************************************************************************************************
//
//	BaseChara�N���X
//
//*****************************************************************************************************************************

//	include

//	class
class BaseChara
{
protected:
	Vector3	pos;
	float		angle;
	int			motion;

public:
	//	�������E���
	BaseChara( void );
	virtual ~BaseChara( void );
	
	//	�X�V

	//	���擾
	Vector3	GetPos( void )const;
};
