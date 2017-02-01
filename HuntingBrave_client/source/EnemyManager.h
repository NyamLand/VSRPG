
#pragma once

//***************************************************************
//
//	EnemyManager�N���X
//
//***************************************************************

//	include
#include	"Singleton.h"
#include	<list>
#include	"Timer.h"
#include	"Wolf.h"
#include	"Moffu.h"
#include	"shadow.h"

//	class
class EnemyManager : public Singleton<EnemyManager>
{
	friend class Singleton<EnemyManager>;

public:
	enum ENEMY_TYPE
	{
		WOLF,
		MOFFU,
		SHADOW,
		TYPE_MAX,
	};

private:
	//	�p�����[�^
	std::list<Enemy*> enemylist;
	iex3DObj*	org[ENEMY_TYPE::TYPE_MAX];
	bool		appendOK;

	std::vector<Enemy*>	netList;

	int lifeUpParam[ENEMY_TYPE::TYPE_MAX];

	Timer*	timer;

	//	�������E���
	EnemyManager( void );
	~EnemyManager( void )override;

public:
	//	�������E���
	bool	Initialize( void );
	void	Release( void );
	void	Load( void );

	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );
	void	RenderHp( void );

	//	����֐�
	void	Append( const Vector3& pos, char type );
	void	PosCheck( Enemy*	enemy );
	void	PlayerPosCheck( Enemy*	eneny );
	void	AddRegularTimeIntervals( void );
	void	LifeUP( void );

	//	���ݒ�

	//	���擾
	std::list<Enemy*>&	GetList( void );
};

#define	enemyManager ( EnemyManager::GetInstance() )
