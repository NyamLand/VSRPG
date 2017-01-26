
#pragma once

//***************************************************************
//
//	LevelManagerクラス
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
			WOLF,
			MOFFU,
			BIG,
			PLAYER,
			ENEMY_MAX
		};
	}

}

//	struct
struct LevelInfo
{
	int	exp;
	int total_level;
	char	level[LEVEL_TYPE::TYPE_MAX];
};

//class
class LevelManager
{
private:
	LevelInfo	levelInfo[PLAYER_MAX];
	int	expData[ENEMY_EXP::ENEMY_MAX];

public:
	//	初期化・解放
	LevelManager( void );
	~LevelManager( void );

	//	動作関数
	void	AddLevel( int id, char levelType );
	void	CalcExp( int id, char enemyType );
	void	CalcExpPlayer( int killer, int dead );
	void	SendLevel( int id, char levelType );
	void	SendExp( int id );
	void	SendClassChange( int id, char nextClass );
	void	SendAllStatus( int id );
	void	SendStatus( int id, char statusType, float status );

	//	受信関数
	void	ReceiveHuntInfo( int client, const LPSTR& data );

	//	レベル毎のステータス計算
	void	CulcStatus( int id, char levelType );
	void	CulcPower( int id, char levelType );
	void	CulcDefense( int id, char levelType );
	void	CulcMagicAttack( int id, char levelType );
	void	CulcMagicDefense( int id, char levelType );
	void	CulcMaxLife( int id, char levelType );
	void	CulcSpeed( int id, char levelType );
	
	//	ステータス送信

	//	情報取得
	LevelInfo&	GetLevelInfo( int id );
	char	GetLevel( int id, char levelType )const;
	int	GetTotalLevel( int id )const;
	int	GetExp( int id )const;
};

extern	LevelManager*	levelManager;