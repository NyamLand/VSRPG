
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
	void	SendMagicInfo( int index, const Vector3& pos );
	void	SendMagicEraseInfo( int index );
	void	SendMagicAppendInfo( int id, const Vector3& pos );

	//	���ݒ�

	//	���擾
	std::vector<Magic*>& GetList( void );

};

extern	MagicManager*	magicManager;