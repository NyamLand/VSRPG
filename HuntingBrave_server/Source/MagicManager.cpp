
#include	"iextreme.h"
#include	<vector>
#include	"GameParam.h"
#include	"MagicManager.h"

//**************************************************************************
//
//	MagicManagerクラス
//
//**************************************************************************

//------------------------------------------------------------------------------------------
//	グローバル
//------------------------------------------------------------------------------------------

MagicManager*	magicManager = nullptr;

//------------------------------------------------------------------------------------------
//	初期化・解放
//------------------------------------------------------------------------------------------

	//	コンストラクタ
	MagicManager::MagicManager( void )
	{
		magicList.clear();
	}

	//	デストラクタ
	MagicManager::~MagicManager( void )
	{
		for ( auto it = magicList.begin(); it != magicList.end(); )
		{
			it = magicList.erase( it );
		}
	}

//------------------------------------------------------------------------------------------
//	更新
//------------------------------------------------------------------------------------------
	
	//	更新
	void	MagicManager::Update( void )
	{
		for ( auto it = magicList.begin(); it != magicList.end(); )
		{
			bool	isAlive = ( *it )->Update();
			int	index = std::distance( magicList.begin(), it );

			if ( !isAlive )	//	消滅しているときリストから削除し、削除情報送信
			{
				it = magicList.erase( it );
				SendMagicEraseInfo( index );
				continue;
			}
			else	//	生存しているとき座標情報送信
			{
				SendMagicInfo( index, ( *it )->GetPos() );
			}

			//	次へ
			it++;
		}
	}

//------------------------------------------------------------------------------------------
//	動作関数
//------------------------------------------------------------------------------------------

	//	追加
	void	MagicManager::Append( int id, const Vector3& pos, const Vector3& vec )
	{
		//	初期化
		Magic*	magic = new Magic();
		magic->Initialize( id, pos, vec );

		//	リストに追加
		magicList.push_back( magic );

		//	リスト追加情報送信
		SendMagicAppendInfo( id, pos );
	}

	//	座標送信
	void	MagicManager::SendMagicInfo( int index, const Vector3& pos )
	{
		//	情報設定
		SendMagicData sendMagicData( index, pos );
		
		//	情報送信
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			gameParam->send( p, ( LPSTR )&sendMagicData, sizeof( sendMagicData ) );
		}
	}

	//	削除情報送信
	void	MagicManager::SendMagicEraseInfo( int index )
	{
		//	情報設定
		SendMagicErase	sendMagicErase( index );

		//	情報送信
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			gameParam->send( p, ( LPSTR )&sendMagicErase, sizeof( sendMagicErase ) );
		}
	}

	//	リスト追加情報送信
	void	MagicManager::SendMagicAppendInfo( int id, const Vector3& pos )
	{
		//	情報設定
		SendMagicAppend	sendMagicAppend( id, pos, gameParam->GetPlayerParam( id ).angle );
		
		//	情報送信
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			gameParam->send( p, ( LPSTR )&sendMagicAppend, sizeof( sendMagicAppend ) );
		}
	}

//------------------------------------------------------------------------------------------
//	情報設定
//------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------
//	情報取得
//------------------------------------------------------------------------------------------

	//	リスト取得
	std::vector<Magic*>&		MagicManager::GetList( void )
	{
		return	magicList;
	}