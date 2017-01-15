
#pragma once

//***************************************************************
//
//	LevelManager�N���X
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

	//	�������E���
	LevelManager( void );
	~LevelManager( void );
public:
	//	�������E���
	bool	Initialize( void );

	//	����֐�
	void	SendLevel( char levelType );

	//	���ݒ�
	void	SetExp( int exp );
	void	SetLevelInfo( char levelType, char level );

	//	�X�e�[�^�X�ݒ�
	void	CulcAllStatus( const LPSTR& data );
	void	CulcAllStatus( const ReceiveAllStatusData& statusData );
	void	CulcStatus( const LPSTR& data );
	void	CulcPower( const LPSTR& data );
	void	CulcDefense( const LPSTR& data );
	void	CulcMagicAttack( const LPSTR& data );
	void	CulcMagicDefense( const LPSTR& data );
	void	CulcSpeed( const LPSTR& data );

	//	���擾
	LevelInfo&	GetLevelInfo( void );
	char	GetLevel( char levelType )const;
	int	GetExp( void )const;
};

#define	levelManager ( LevelManager::GetInstance() ) 