
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"UIManager.h"
#include	"EnemyManager.h"

//***************************************************************
//
//	PlayerManagerクラス
//
//***************************************************************

//-------------------------------------------------------------------------------------
//	グローバル
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//	初期化・解放
//-------------------------------------------------------------------------------------

//	コンストラクタ
EnemyManager::EnemyManager(void) 
{
	//リスト初期化
	enemylist.clear();
}

//	デストラクタ
EnemyManager::~EnemyManager(void)
{
	Release();
}

//	初期化
bool	EnemyManager::Initialize(void)
{
	//リスト初期化
	enemylist.clear();


	return	true;
}

//	解放
void	EnemyManager::Release(void)
{
	for (auto it = enemylist.begin(); it != enemylist.end();)
	{
		it = enemylist.erase(it);
	}
}

//-------------------------------------------------------------------------------------
//	更新・描画
//-------------------------------------------------------------------------------------

//	更新
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

//	描画
void	EnemyManager::Render(void)
{
	for (auto it = enemylist.begin(); it != enemylist.end();it++)
	{
		(*it)->Render();
	}
}

//-------------------------------------------------------------------------------------
//	動作関数
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
//	情報設定
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//	情報取得
//-------------------------------------------------------------------------------------

//	Enemy情報取得
//Enemy*	EnemyManager::GetEnemy(void)
//{
//	
//}
