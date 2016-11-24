
#pragma once

//***************************************************************
//
//	EnemyManager�N���X
//
//***************************************************************

//	include
#include	"Singleton.h"
#include	<list>
#include	"BigEnemy.h"
#include	"SmallEnemy.h"

//	class
class EnemyManager : public Singleton<EnemyManager>
{
	friend class Singleton<EnemyManager>;

public:
	enum ENEMY_TYPE
	{
		BIG_ENEMY,
		SMALL_ENEMY,
		TYPE_MAX,
	};

private:
	//	�p�����[�^
	std::list<Enemy*> enemylist;
	iex3DObj*	org[ENEMY_TYPE::TYPE_MAX];
	bool		appendOK;

	//	�������E���
	EnemyManager( void );
	~EnemyManager( void )override;

public:
	//	�������E���
	bool	Initialize( void )override;
	void	Release( void )override;
	void	Load( void );

	//	�X�V�E�`��
	void	Update( void );
	void	Render( void );

	//	����֐�
	void	Append( const Vector3& pos, int type );
	void	PosCheck( Enemy*	enemy );
	void	PlayerPosCheck( Enemy*	eneny );
	void	AddRegularTimeIntervals( void );

	//	���ݒ�

	//	���擾
	std::list<Enemy*>&	GetList( void );
};

#define	enemyManager ( EnemyManager::GetInstance() )
