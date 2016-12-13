
#pragma once

//***************************************************************
//
//	LevelManagerƒNƒ‰ƒX
//
//***************************************************************

//	include
#include	"Singleton.h"

//	define
namespace
{
	namespace LEVEL_TYPE
	{
		enum
		{
			ATTACK,
			MAGIC_ATTACK,
			DEFENSE,
			MAGIC_DEFENSE,
			SPEED,
			TYPE_MAX
		};
	}

	namespace ENEMY_EXP
	{
		enum
		{
			SMALL_ENEMY,
			BIG_ENEMY
		};
	}


}

//	struct
struct LevelInfo
{
	int	exp;
	char	level[LEVEL_TYPE::TYPE_MAX];
};

//class
class LevelManager : public Singleton<LevelManager>
{
	friend	Singleton<LevelManager>;
public:
	static	const int LEVEL_MAX = 6;

private:
	LevelInfo	levelInfo;

public:
	//	‰Šú‰»E‰ğ•ú
	LevelManager( void );
	~LevelManager( void );

	//	“®ìŠÖ”
	void	SendLevel( char levelType );

	//	î•ñİ’è
	void	SetExp( int exp );
	void	SetLevelInfo( char levelType, char level );

	//	î•ñæ“¾
	LevelInfo&	GetLevelInfo( void );
	char	GetLevel( char levelType )const;
	int	GetExp( void )const;
};

#define	levelManager ( LevelManager::GetInstance() ) 