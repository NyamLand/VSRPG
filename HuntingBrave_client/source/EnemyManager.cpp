
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
#define	COLLISION_DIST	2.0f
#define	ENEMY_MAX			5

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
		org[ENEMY_TYPE::SMALL_ENEMY] = new iex3DObj( "DATA/CHR/Enemy/zako.IEM" );
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
			bool isAlive = ( *it )->GetIsAlive();

			//	死亡していたらリストから削除
			if ( !isAlive )
			{
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

//-------------------------------------------------------------------------------------
//	動作関数
//-------------------------------------------------------------------------------------
	
	//	リストに追加
	void	EnemyManager::Append( const Vector3& pos,int type )
	{
		Enemy* enemy = nullptr;

		switch ( type )
		{
		case BIG_ENEMY:
			enemy = new BigEnemy();
			break;

		case SMALL_ENEMY:
			enemy = new SmallEnemy();
			break;

		default:
			return;
		}

		//	初期化
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
			Vector3	vec = enemy->GetPos() - ( *it )->GetPos();
			float		length = vec.Length();

			//	近い場合は離す
			if ( length < COLLISION_DIST )
			{
				//	ベクトル正規化
				vec.Normalize();

				//	離す
				( *it )->SetPos( enemy->GetPos() - vec * COLLISION_DIST );
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
			
			//	プレイヤーへのベクトルを求める
			Vector3	pPos = playerManager->GetPlayer( p )->GetPos();
			Vector3	vec = pPos - enemy->GetPos();
			float		length = vec.Length();
			
			//	近い場合は離す
			if ( length < COLLISION_DIST )
			{
				//	ベクトル正規化
				vec.Normalize();

				//	離す
				enemy->SetPos( pPos - vec * COLLISION_DIST );
			}
		}
	}

	//	一定時間ごとに敵を生成
	void	EnemyManager::AddRegularTimeIntervals( void )
	{
		if ( gameManager->GetTime() % APPEND_INTERVAL != 0 )
		{
			//	生成フラグをtrueにする
			appendOK = true;
			return;
		}

		if ( !appendOK )	return;

		//	出現座標の設定
		Vector3	appendPos = Vector3(
			random->GetFloat( -20.0f, 20.0f ),
			0.0f,
			random->GetFloat( -20.0f, 20.0f ) );
		
		//	リストに追加
		Append( appendPos, ENEMY_TYPE::BIG_ENEMY );

		//	生成フラグをfalseにする
		appendOK = false;
	}

//-------------------------------------------------------------------------------------
//	情報設定
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//	情報取得
//-------------------------------------------------------------------------------------
