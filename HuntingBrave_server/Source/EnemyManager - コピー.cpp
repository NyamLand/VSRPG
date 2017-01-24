
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
#define	APPEND_INTERVAL	10

namespace
{
	namespace ENEMY_COMMAND
	{
		enum
		{
			ENEMY_INFO,
			ERASE_INFO,
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
		if ( timer == nullptr )	timer = new Timer();
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
	void	EnemyManager::Update( void )
	{
		int	enemyNum = 0;
		for ( auto it = enemyList.begin(); it != enemyList.end(); )
		{
			//	更新
			( *it )->Update();

			//	敵情報送信
			int index = std::distance( enemyList.begin(), it );
			SendEnemyInfo( index, ( *it )->GetEnemyParam() );

			enemyNum++;
			it++;
		}

		//	一定時間ごとに生成
		if ( timer != nullptr )		return;

		if ( timer->Update() )
		{
			//	追加
			if ( enemyNum < ENEMY_MAX )
				Append( Vector3( 0.0f, 0.0f, 0.0f ), 0.0f );

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
		enemy->Update();
		
		//	リストに追加
		enemyList.push_back( enemy );

		//	追加情報送信
		SendAppend();
	}

	//	敵情報送信
	void	EnemyManager::SendEnemyInfo( int index, const EnemyParam& enemyParam )
	{
		//	構造体宣言
		static	struct
		{
			char com;
			char enemyCom;
			int	index;
			Vector3	pos;
			float			angle;
			int			motion;
		} enemyInfo;

		//	情報設定
		enemyInfo.com = SEND_COMMAND::ENEMY_INFO;
		enemyInfo.enemyCom = ENEMY_COMMAND::ENEMY_INFO;
		enemyInfo.index = index;
		enemyInfo.pos = enemyParam.pos;
		enemyInfo.angle = enemyParam.angle;
		enemyInfo.motion = enemyParam.motion;
		
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			if( gameParam->GetPlayerActive( i ) == false )	continue;
			gameParam->send( i, ( char* )&enemyInfo, sizeof( enemyInfo ) );
		}
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
	void	EnemyManager::SendAppend( void )
	{	
		static	struct
		{
			char com;
			char enemyCom;
		} enemyInfo;

		enemyInfo.com = SEND_COMMAND::ENEMY_INFO;
		enemyInfo.enemyCom = ENEMY_COMMAND::APPEND_INFO;

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			if( gameParam->GetPlayerActive( i ) == false )	continue;
			gameParam->send( i, ( char* )&enemyInfo, sizeof( enemyInfo ) );
		}
	}

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------------------
