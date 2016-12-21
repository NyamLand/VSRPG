
#pragma once

//***************************************************************
//
//	NameManager�N���X
//
//***************************************************************

//	include
#include	"Singleton.h"

//class
class NameManager : public Singleton<NameManager>
{
	friend	Singleton<NameManager>;
private:
	std::map<char*, int>	nameMap;
	int	nameIndexX[PLAYER_MAX][NAME_MAX];
	int	nameIndexY[PLAYER_MAX][NAME_MAX];
	int	nameIndex[PLAYER_MAX][NAME_MAX];
	//	�������E���
	NameManager( void );
	~NameManager( void );
public:

	//	���ݒ�
	void	SetNameIndex( int id, char* name );

	//	���擾
	void	GetNameIndex( int id, int& outX, int& outY );
	char*	GetName( int x, int y );
};

#define	nameManager ( NameManager::GetInstance() ) 