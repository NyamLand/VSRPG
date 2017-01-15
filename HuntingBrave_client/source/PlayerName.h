
#pragma once

//**************************************************************************
//
//	PlayerName�N���X
//
//**************************************************************************

//	include
struct NameInfo
{
	char	name[17];		//	���O
	int	nameIndex[4];	//	���O�C���f�b�N�X
};

//	class
class PlayerName
{
private:
	NameInfo	nameInfo[PLAYER_MAX];

public:
	//	�������E���
	PlayerName( void );
	~PlayerName( void );
	void	Initialize( void );

	//	����֐�
	char*	SrcCharFromIndex( int* nameIndex );
	void		SetName( int id, int* nameIndex );

	//	���擾
	int*		GetNameIndex( int id );
	char*	GetName( int id );
};