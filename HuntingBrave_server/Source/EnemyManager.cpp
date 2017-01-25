
#include	"iextreme.h"
#include	<vector>
#include	"Random.h"
#include	"GameParam.h"
#include	"EnemyManager.h"

//*****************************************************************************************************************************
//
//	EnemyManagerクラス
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

#define	ENEMY_MAX	5
#define	APPEND_INTERVAL	5
#define	PLAYER_RADIUS	1.5f

namespace
{
	namespace ENEMY_COMMAND
	{
		enum
		{
			ERASE_INFO = 10,
			APPEND_INFO
		};
	}

}

EnemyManager*	enemyManager = nullptr;

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	EnemyManager::EnemyManager( void ) : timer( nullptr )
	{
		enemyList.clear();
	}

	//	デストラクタ
	EnemyManager::~EnemyManager( void )
	{
		Release();
	}

	//	初期化
	bool	EnemyManager::Initialize( void )
	{
		enemyList.clear();
		if ( timer == nullptr )	timer = new Timer();
		timer->Start( APPEND_INTERVAL );
		return	true;
	}

	//	解放
	void	EnemyManager::Release( void )
	{
		for ( auto it = enemyList.begin(); it != enemyList.end(); )
		{
			it = enemyList.erase( it );
		}

		if ( timer != nullptr )
		{
			delete timer;
			timer = nullptr;
		}
	}
	
//----------------------------------------------------------------------------------------------
//	更新
//----------------------------------------------------------------------------------------------

	//	更新
	void	EnemyManager::Update( float deltaTime )
	{
		int	enemyNum = 0;
		for ( auto it = enemyList.begin(); it != enemyList.end(); )
		{
			//	インデックス
			char index = std::distance( enemyList.begin(), it );
			
			//	座標チェック
			PosCheck( *it );
			PlayerPosCheck( *it );

			//	更新
			( *it )->Update( index, deltaTime );

			enemyNum++;
			it++;
		}

		//	一定時間ごとに生成
		if ( timer == nullptr )		return;

		if ( timer->Update() )
		{
			//	追加
			if ( enemyNum < ENEMY_MAX )
				Append( Vector3( 0.0f, 0.0f, 50.0f ), 0.0f );

			timer->Start( APPEND_INTERVAL );
		}
	}

//----------------------------------------------------------------------------------------------
//	動作関数
//----------------------------------------------------------------------------------------------

	//	リストに追加
	void	EnemyManager::Append( const Vector3& pos, float angle )
	{
		//	初期化
		Enemy*	enemy = new Enemy();
		enemy->SetPos( pos );
		enemy->SetAngle( angle );

		
		//	追加情報送信
		SendAppend( pos, angle );
		
		//	リストに追加
		enemyList.push_back( enemy );
	}

	//	敵削除情報送信
	void	EnemyManager::SendErase( int index )
	{
		static	struct
		{
			char com;
			char enemyCom;
			int	index;
		} enemyInfo;

		enemyInfo.com = SEND_COMMAND::ENEMY_INFO;
		enemyInfo.enemyCom = ENEMY_COMMAND::ERASE_INFO;
		enemyInfo.index = index;

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			if( gameParam->GetPlayerActive( i ) == false )	continue;
			gameParam->send( i, ( char* )&enemyInfo, sizeof( enemyInfo ) );
		}
	}

	//	リスト追加情報送信
	void	EnemyManager::SendAppend( const Vector3& pos, float angle )
	{	
		static	struct
		{
			char com;
			char enemyCom;
			Vector3	pos;
			float			angle;
		} enemyInfo;

		enemyInfo.com = SEND_COMMAND::ENEMY_INFO;
		enemyInfo.enemyCom = ENEMY_COMMAND::APPEND_INFO;
		enemyInfo.pos = pos;
		enemyInfo.angle = angle;

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			if( gameParam->GetPlayerActive( i ) == false )	continue;
			gameParam->send( i, ( char* )&enemyInfo, sizeof( enemyInfo ) );
		}
	}

	//	座標チェック（ 近ければ遠ざける ）
	void	EnemyManager::PosCheck( Enemy* enemy )
	{
		for ( auto it = enemyList.begin(); it != enemyList.end(); it++ )
		{
			//	自分VS自分は除外
			if ( ( *it ) == enemy )	continue;

			//	自分→相手へのベクトル
			Vector3	vec = enemy->GetPos() - ( *it )->GetPos();
			vec.y = 0.0f;
			float		length = vec.Length();

			float collisionDist = enemy->GetCollisionInfo().radius + ( *it )->GetCollisionInfo().radius;
			
			//	近い場合は離す
			if ( length < collisionDist )
			{
				//	ベクトル正規化
				vec.Normalize();

				//	離す
				( *it )->SetPos( enemy->GetPos() - vec * collisionDist );
				( *it )->SendEnemyInfo();
			}
		}

	}

	//	プレイヤーとの座標チェック
	void	EnemyManager::PlayerPosCheck( Enemy* enemy )
	{
		//	自分→相手へのベクトル
		for (int p = 0; p < PLAYER_MAX; p++)
		{
			//	存在チェック
			if ( !gameParam->GetPlayerActive( p ) )	continue;
			PlayerParam		playerParam = gameParam->GetPlayerParam( p );

			//	プレイヤーへのベクトルを求める
			Vector3	pPos = playerParam.pos;
			Vector3	vec = pPos - enemy->GetPos();
			vec.y = 0.0f;
			float		length = vec.Length();

			float collisionDist = enemy->GetCollisionInfo().radius + PLAYER_RADIUS;
			
			//	近い場合は離す
			if ( length <  collisionDist )
			{
				//	ベクトル正規化
				vec.Normalize();

				//	離す
				enemy->SetPos( pPos - vec * collisionDist );
				enemy->SendEnemyInfo();
			}
		}
	}

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------------------
