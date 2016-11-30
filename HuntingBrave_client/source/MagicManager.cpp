
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	<vector>
#include	"MagicManager.h"

//***************************************************************
//
//	MagicManagerクラス
//
//***************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	MagicManager::MagicManager( void ) : org( nullptr )
	{

	}

	//	デストラクタ
	MagicManager::~MagicManager( void )
	{
		//Release();
	}

	//	初期化
	bool	MagicManager::Initialize( void )
	{
		if ( org == nullptr )
			org = new iexMesh( "DATA/Effect/magic/MagicBullet/magic-Bullet.IMO" );
		org->SetScale( 0.01f );
		org->Update();
		magicList.clear();
		return	true;
	}

	//	解放
	void	MagicManager::Release( void )
	{
		for ( auto it = magicList.begin(); it != magicList.end(); )
		{
			it = magicList.erase( it );
		}

		SafeDelete( org );
	}

//----------------------------------------------------------------------------------------------
//	更新・描画
//----------------------------------------------------------------------------------------------
	
	//	更新
	void	MagicManager::Update( void )
	{
		for ( auto it = magicList.begin(); it != magicList.end(); it++ )
		{
			( *it )->Update();
		}
	}

	//	描画
	void	MagicManager::Render( void )
	{
		for ( auto it = magicList.begin(); it != magicList.end(); it++ )
		{
			( *it )->Render();
		}
	}

//----------------------------------------------------------------------------------------------
//	動作関数
//----------------------------------------------------------------------------------------------

	//	リストに追加
	void	MagicManager::Append( int id, const Vector3& pos, float angle )
	{
		//	実体
		Magic*	magic = new Magic();

		//	初期化
		magic->Initialize( org->Clone(), id, pos, angle );

		//	リストに追加
		magicList.push_back( magic );
	}

	//	リストから削除
	void	MagicManager::Erase( int index )
	{
		magicList.erase( magicList.begin() + index );
	}

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

	//	座標設定
	void	MagicManager::SetPos( int index, const Vector3& pos )
	{
		magicList[index]->SetPos( pos );
	}

//----------------------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------------------

	//	リスト取得
	std::vector<Magic*>&		MagicManager::GetList( void )
	{
		return	magicList;
	}