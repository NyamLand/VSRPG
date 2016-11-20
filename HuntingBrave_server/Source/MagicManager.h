
#pragma once

//**************************************************************************
//
//	MagicManager�N���X
//
//**************************************************************************

//	include
#include	"Magic.h"

//	class
class MagicManager
{
private:
	std::vector<Magic*>	magicList;

public:
	//	�������E���
	MagicManager( void );
	~MagicManager( void );

	//	�X�V
	void	Update( void );

	//	����֐�
	void	Append( int id, const Vector3& pos, const Vector3& vec );

	//	���ݒ�

	//	���擾

};

extern	MagicManager*	magicManager;