
#pragma once

//***************************************************************
//
//	LevelManager�N���X
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
	//	�������E���
	LevelManager( void );
	~LevelManager( void );

	//	����֐�
	void	AddLevel( int id, char levelType );
	void	CalcExp( int id, char enemyType );
	void	CalcExpPlayer( int killer, int dead );
	void	SendLevel( int id, char levelType );
	void	SendExp( int id );
	void	SendClassChange( int id, char nextClass );
	void	SendAllStatus( int id );
	void	SendStatus( int id, char statusType, float status );

	//	��M�֐�
	void	ReceiveHuntInfo( int client, const LPSTR& data );

	//	���x�����̃X�e�[�^�X�v�Z
	void	CulcStatus( int id, char levelType );
	void	CulcPower( int id, char levelType );
	void	CulcDefense( int id, char levelType );
	void	CulcMagicAttack( int id, char levelType );
	void	CulcMagicDefense( int id, char levelType );
	void	CulcMaxLife( int id, char levelType );
	void	CulcSpeed( int id, char levelType );
	
	//	�X�e�[�^�X���M

	//	���擾
	LevelInfo&	GetLevelInfo( int id );
	char	GetLevel( int id, char levelType )const;
	int	GetTotalLevel( int id )const;
	int	GetExp( int id )const;
};

extern	LevelManager*	levelManager;