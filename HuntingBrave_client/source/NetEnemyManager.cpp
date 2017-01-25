
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	<vector>
#include	"NetEnemyManager.h"

//***************************************************************
//
//	NetEnemyManagerクラス
//
//***************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

namespace ENEMY_COMMAND
{
	enum
	{
		ENEMY_INFO,
		ERASE_INFO,
		APPEND_INFO,
	};
}

#define	MINOTAURUS_SCALE	0.02f

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	NetEnemyManager::NetEnemyManager( void ) : org( nullptr )
	{
		Initialize();
	}

	//	デストラクタ
	NetEnemyManager::~NetEnemyManager( void )
	{
		//Release();
	}

	//	初期化
	bool	NetEnemyManager::Initialize( void )
	{
		if ( org == nullptr )
		{
			org = new iex3DObj( "DATA/CHR/Enemy/minotaurus.IEM" );
			org->SetScale( MINOTAURUS_SCALE );
			org->Update();
		}

		enemyList.clear();
		return	true;
	}

	//	解放
	void	NetEnemyManager::Release( void )
	{
		for ( auto it = enemyList.begin(); it != enemyList.end(); )
		{
			it = enemyList.erase( it );
		}

		SafeDelete( org );
	}

//----------------------------------------------------------------------------------------------
//	更新・描画
//----------------------------------------------------------------------------------------------
	
	//	更新
	void	NetEnemyManager::Update( void )
	{
		for ( int i = 0; i < enemyList.size(); i++)
		{
			enemyList[i]->Update();
		}
	}

	//	描画
	void	NetEnemyManager::Render( void )
	{
		for ( int i = 0; i < enemyList.size(); i++ )
		{
			enemyList[i]->Render();
		}
	}

	//	HP描画
	void	NetEnemyManager::RenderHp(void)
	{
		for (auto it = enemyList.begin(); it != enemyList.end(); it++)
		{
			(*it)->RenderHpBar();
		}
	}

//----------------------------------------------------------------------------------------------
//	動作関数
//----------------------------------------------------------------------------------------------

	//	リストに追加
	void	NetEnemyManager::Append( const Vector3& pos, float angle )
	{
		//	実体
		NetEnemy*	enemy = new NetEnemy();

		//	初期化
		enemy->Initialize( org->Clone(), pos, angle );

		//	リストに追加
		enemyList.push_back( enemy );
	}

	//	リストから削除
	void	NetEnemyManager::Erase( int index )
	{
		enemyList.erase( enemyList.begin() + index );
	}

//----------------------------------------------------------------------------------------------
//	受信関数
//----------------------------------------------------------------------------------------------

	//	受信
	void	NetEnemyManager::Receive( const LPSTR& data )
	{
		switch ( data[1] )
		{
		case ENEMY_COMMAND::ENEMY_INFO:
			if ( enemyList.empty() )	break;
			ReceiveEnemyInfo( data );
			break;

		case ENEMY_COMMAND::ERASE_INFO:
			if ( enemyList.empty() )	break;
			ReceiveEraseInfo( data );
			break;

		case ENEMY_COMMAND::APPEND_INFO:
			ReceiveAppendInfo( data );
			break;

		default:
			break;
		}
	}

	//	敵情報受信
	void	NetEnemyManager::ReceiveEnemyInfo( const LPSTR& data )
	{
		struct EnemyInfo
		{
			char com;
			char enemyCom;
			int	index;
			Vector3	pos;
			float			angle;
			int			motion;
		}* enemyInfo = ( EnemyInfo* )data;

		SetInfo( enemyInfo->index, 
			enemyInfo->pos, 
			enemyInfo->angle, 
			enemyInfo->motion );
	}

	//	敵消去情報受信
	void	NetEnemyManager::ReceiveEraseInfo( const LPSTR& data )
	{
		//	変換
		struct EnemyInfo
		{
			char com;
			char enemyCom;
			int	index;
		}* enemyInfo = ( EnemyInfo* )data;

		//	削除
		Erase( enemyInfo->index );
	}

	//	敵追加情報受信
	void	NetEnemyManager::ReceiveAppendInfo( const LPSTR& data )
	{
		//	変換
		struct EnemyInfo
		{
			char com;
			char enemyCom;
			Vector3	pos;
			float			angle;
		}* enemyInfo = ( EnemyInfo* )data;

		Append( enemyInfo->pos, enemyInfo->angle );
	}

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

	//	受信情報設定
	void	NetEnemyManager::SetInfo( int index, const Vector3& pos, float angle, int motion )
	{
		enemyList[index]->SetPos( pos );
		enemyList[index]->SetAngle( angle );
		enemyList[index]->SetMotion( motion );
	}

//----------------------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------------------

	//	リスト取得
	std::vector<NetEnemy*>&		NetEnemyManager::GetList( void )
	{
		return	enemyList;
	}