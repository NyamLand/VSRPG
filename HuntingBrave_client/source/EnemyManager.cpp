
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"UIManager.h"
#include	"EnemyManager.h"

//***************************************************************
//
//	PlayerManager�N���X
//
//***************************************************************

//-------------------------------------------------------------------------------------
//	�O���[�o��
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//	�������E���
//-------------------------------------------------------------------------------------

//	�R���X�g���N�^
EnemyManager::EnemyManager(void) 
{
	//���X�g������
	enemylist.clear();
}

//	�f�X�g���N�^
EnemyManager::~EnemyManager(void)
{
	Release();
}

//	������
bool	EnemyManager::Initialize(void)
{
	//���X�g������
	enemylist.clear();


	return	true;
}

//	���
void	EnemyManager::Release(void)
{
	for (auto it = enemylist.begin(); it != enemylist.end();)
	{
		it = enemylist.erase(it);
	}
}

//-------------------------------------------------------------------------------------
//	�X�V�E�`��
//-------------------------------------------------------------------------------------

//	�X�V
void	EnemyManager::Update(void)
{
	if(KEY_Get(KEY_A)==3)Append(Vector3(10, 0, 0), 0);
	for (auto it = enemylist.begin(); it != enemylist.end();)
	{
		(*it)->Update();
		bool active;
		it++;
	}
}

//	�`��
void	EnemyManager::Render(void)
{
	for (auto it = enemylist.begin(); it != enemylist.end();it++)
	{
		(*it)->Render();
	}
}

//-------------------------------------------------------------------------------------
//	����֐�
//-------------------------------------------------------------------------------------
void	EnemyManager::Append(const Vector3 &pos,int type)
{
	Enemy* enemy = nullptr;
	if (type == 0){
		enemy = new BigEnemy();
	}
	else{
		enemy = new SmallEnemy();
	}
	enemy->Initialize();
	enemy->SetPos(pos);
	enemylist.push_back(enemy);
}
//-------------------------------------------------------------------------------------
//	���ݒ�
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//	���擾
//-------------------------------------------------------------------------------------

//	Enemy���擾
//Enemy*	EnemyManager::GetEnemy(void)
//{
//	
//}
