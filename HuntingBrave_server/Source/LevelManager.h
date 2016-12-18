
#pragma once

//***************************************************************
//
//	LevelManagerƒNƒ‰ƒX
//
//***************************************************************

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
			BIG_ENEMY,
			SMALL_ENEMY,
			ENEMY_MAX
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
class LevelManager
{
private:
	LevelInfo	levelInfo[PLAYER_MAX];
	int	expData[ENEMY_EXP::ENEMY_MAX];

public:
	//	‰Šú‰»E‰ğ•ú
	LevelManager( void );
	~LevelManager( void );

	//	“®ìŠÖ”
	void	AddLevel( int id, char levelType );
	//void	CalcExp( int id, int exp );
	void	CalcExp( int id, char enemyType );
	void	SendLevel( int id, char levelType );
	void	SendExp( int id );
	void	SendClassChange( int id, char nextClass );

	//	î•ñæ“¾
	LevelInfo&	GetLevelInfo( int id );
	char	GetLevel( int id, char levelType )const;
	int	GetExp( int id )const;
};

extern	LevelManager*	levelManager;