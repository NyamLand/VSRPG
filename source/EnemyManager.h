
#pragma once

//***************************************************************
//
//	PlayerManager�N���X
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

private:
	//	�p�����[�^
	std::list<Enemy*> enemylist;


	//	�������E���
	EnemyManager(void);
	~EnemyManager(void)override;

public:
	//	�������E���
	bool	Initialize(void)override;
	void	Release(void)override;

	//	�X�V�E�`��
	void	Update(void);
	void	Render(void);

	//	����֐�
	void	Append(const Vector3& pos,int type);
	void	DistCheck(int n);

	//	���擾
	//Enemy*	GetEnemy(void);

	
};

#define	enemyManager ( EnemyManager::GetInstance() )
