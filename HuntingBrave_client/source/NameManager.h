
#pragma once

//***************************************************************
//
//	NameManagerクラス
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
	//	初期化・解放
	NameManager( void );
	~NameManager( void );
public:

	//	情報設定
	void	SetNameIndex( int id, char* name );

	//	情報取得
	void	GetNameIndex( int id, int& outX, int& outY );
	char*	GetName( int x, int y );
};

#define	nameManager ( NameManager::GetInstance() ) 