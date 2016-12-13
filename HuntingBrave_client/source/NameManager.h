
#pragma once

//***************************************************************
//
//	NameManagerƒNƒ‰ƒX
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
	//	‰Šú‰»E‰ğ•ú
	NameManager( void );
	~NameManager( void );
public:

	//	î•ñİ’è
	void	SetNameIndex( int id, char* name );

	//	î•ñæ“¾
	void	GetNameIndex( int id, int& outX, int& outY );
	char*	GetName( int x, int y );
};

#define	nameManager ( NameManager::GetInstance() ) 