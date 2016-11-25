
#pragma once

//****************************************************************
//
//	MagicManager�N���X
//
//****************************************************************

//	include
#include	"Singleton.h"
#include	"Magic.h"

//	class
class MagicManager : public Singleton<MagicManager>
{
	friend	class Singleton<MagicManager>;
private:
	iexMesh*	org;
	std::vector<Magic*>	magicList;

private:
	//	�������E���
	MagicManager( void );
	~MagicManager( void )override;

public:
	//	�������E���
	bool	Initialize( void )override;
	void	Release( void )override;

	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );

	//	����֐�
	void	Erase( int index );
	void	Append( int id, const Vector3& pos, float angle );

	//	���ݒ�
	void	SetPos( int index, const Vector3& pos );

	//	���擾
	std::vector<Magic*>&		GetList( void );

};

#define	magicManager ( MagicManager::GetInstance() )