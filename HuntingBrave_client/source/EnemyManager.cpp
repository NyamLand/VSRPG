
#include	"iextreme.h"
#include	"Random.h"
#include	"GameData.h"
#include	"GlobalFunction.h"
#include	"GameParam.h"
#include	"PlayerManager.h"
#include	"UIManager.h"
#include	"EnemyManager.h"

//***************************************************************
//
//	EnemyManagerクラス
//
//***************************************************************

//-------------------------------------------------------------------------------------
//	グローバル
//-------------------------------------------------------------------------------------

//	定数
#define	APPEND_INTERVAL		3
#define	ENEMY_MAX			5
#define APPEND_RADIUS		15.0f	

namespace
{

}

//-------------------------------------------------------------------------------------
//	初期化・解放
//-------------------------------------------------------------------------------------

	//	コンストラクタ
	EnemyManager::EnemyManager( void ) : appendOK( true )
	{
		//リスト初期化
		enemylist.clear();

		//	オブジェクト初期化
		for ( int i = 0; i < ENEMY_TYPE::TYPE_MAX; i++ )
		{
			org[i] = nullptr;
		}
	}

	//	デストラクタ
	EnemyManager::~EnemyManager( void )
	{
		Release();
	}

	//	初期化
	bool	EnemyManager::Initialize( void )
	{
		//リスト初期化
		enemylist.clear();

		//	モデル読み込み
		Load();
		
		

		return	true;
	}

	//	解放
	void	EnemyManager::Release( void )
	{
		for ( auto it = enemylist.begin(); it != enemylist.end(); )
		{
			it = enemylist.erase( it );
		}

		for ( int i = 0; i < ENEMY_TYPE::TYPE_MAX; i++ )
		{
			SafeDelete( org[i] );
		}
	}

	//	オブジェクト読み込み
	void	EnemyManager::Load( void )
	{
		org[ENEMY_TYPE::BIG_ENEMY] = new iex3DObj( "DATA/CHR/Enemy/minotaurus.IEM" );
		org[ENEMY_TYPE::SMALL_ENEMY] = new iex3DObj( "DATA/CHR/Enemy/mofumofu/moffu.IEM" );
	}

//-------------------------------------------------------------------------------------
//	更新・描画
//-------------------------------------------------------------------------------------

	//	更新
	void	EnemyManager::Update( void )
	{
		int		enemyNum = 0;

		for ( auto it = enemylist.begin(); it != enemylist.end(); )
		{
			//	座標チェック
			PosCheck( *it );
			PlayerPosCheck( *it );

			//	更新
			( *it )->Update();
		
			//	生存チェック
			bool isAlive = ( *it )->GetLifeInfo().isAlive;

			//	死亡していたらリストから削除
			if ( !isAlive )
			{
				gameParam->SendHuntInfo((*it)->GetEnemyType());
				it = enemylist.erase( it );
				continue;
			}

			//	敵数加算
			enemyNum++;

			//	次へ
			it++;
		}

		//	一定時間ごとに敵を生成
		if ( enemyNum < ENEMY_MAX )	AddRegularTimeIntervals();
	}

	//	描画
	void	EnemyManager::Render( void )
	{
		for ( auto it = enemylist.begin(); it != enemylist.end(); it++ )
		{
			( *it )->Render();
		}
	}

	//	HP描画
	void	EnemyManager::RenderHp( void )
	{
		for ( auto it = enemylist.begin(); it != enemylist.end(); it++ )
		{
			( *it )->BarRender();
		}
	}

//-------------------------------------------------------------------------------------
//	動作関数
//-------------------------------------------------------------------------------------
	
	//	リストに追加
	void	EnemyManager::Append( const Vector3& pos, char type )
	{
		Enemy* enemy = nullptr;

		switch ( type )
		{
		case BIG_ENEMY:
			enemy = new BigEnemy();
			//enemy->GetLifeInfo().maxLife = 80.0f;
			break;

		case SMALL_ENEMY:
			enemy = new SmallEnemy();
			//enemy->GetLifeInfo().maxLife = 20.0f;
			break;

		default:
			return;
		}

		//	初期化
		enemy->SetEnemyType( type );
		enemy->SetObj( org[type]->Clone() );
		enemy->Initialize();
		enemy->SetPos( pos );
		

		//	リストに追加
		enemylist.push_back( enemy );
	}

	//	座標チェック（ 近ければ遠ざける ）
	void	EnemyManager::PosCheck( Enemy* enemy )
	{
		for ( auto it = enemylist.begin(); it != enemylist.end(); it++ )
		{
			//	自分VS自分は除外
			if ( ( *it ) == enemy )	continue;
			

				//	自分→相手へのベクトル
				Vector3	vec = enemy->GetPos() - (*it)->GetPos();
				float		length = vec.Length();

				float collisionDist = enemy->GetCollisionInfo().radius + (*it)->GetCollisionInfo().radius;
				//	近い場合は離す
				if (length < collisionDist)
				{
					//	ベクトル正規化
					vec.Normalize();

					//	離す
					(*it)->SetPos(enemy->GetPos() - vec * collisionDist);
				}
			}
		
	}

	//	プレイヤーとの座標チェック
	void	EnemyManager::PlayerPosCheck( Enemy* enemy )
	{
		//	自分→相手へのベクトル
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	存在チェック
			if( !gameParam->GetPlayerActive( p ) )	continue;
			if (enemy->GetMode() == 4)continue;
			//	プレイヤーへのベクトルを求める
			Vector3	pPos = playerManager->GetPlayer( p )->GetPos();
			Vector3	vec = pPos - enemy->GetPos();
			float		length = vec.Length();
			
			float collisionDist = enemy->GetCollisionInfo().radius + playerManager->GetPlayer( p )->GetCollisionInfo().radius;
			//	近い場合は離す
			if ( length <  collisionDist )
			{
				//	ベクトル正規化
				vec.Normalize();

				//	離す
				enemy->SetPos( pPos - vec * collisionDist );
			}
		}
	}

	//	一定時間ごとに敵を生成
	void	EnemyManager::AddRegularTimeIntervals( void )
	{

		int id = gameParam->GetMyIndex();

		if ( ( int )gameManager->GetTime() % APPEND_INTERVAL != 0 )
		{
			//	生成フラグをtrueにする
			appendOK = true;
			return;
		}

		if ( !appendOK )	return;

		//	出現座標の設定
		float randX = random->GetFloat( -APPEND_RADIUS, APPEND_RADIUS );
		float randZ = random->GetFloat( -APPEND_RADIUS, APPEND_RADIUS );
		Vector3	appendPos = gameParam->GetPlayerParam(id).pos + Vector3( randX, 0.0f, randZ );
			
		//	リストに追加
		Append( appendPos, random->GetInt( BIG_ENEMY, SMALL_ENEMY ) );
		
		//	生成フラグをfalseにする
		appendOK = false;
	}

//-------------------------------------------------------------------------------------
//	情報設定
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//	情報取得
//-------------------------------------------------------------------------------------

	//	リスト取得
	list<Enemy*>&	EnemyManager::GetList( void )
	{
		return	enemylist;
	}
