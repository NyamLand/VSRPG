
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameParam.h"
#include	<vector>
#include	"MagicManager.h"
#include	"Particle.h"


//***************************************************************
//
//	MagicManagerクラス
//
//***************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

namespace
{
	//	受信情報
	namespace MAGIC_INFO
	{
		enum
		{
			POS,
			APPEND,
			ERASE
		};
	}

	//	魔法攻撃情報
	struct ReceiveMagicData
	{
		char	com = RECEIVE_COMMAND::MAGIC_INFO;
		char infoType;
		int	index;
		Vector3	pos;
	};

	//	魔法発動情報
	struct ReceiveMagicAppend
	{
		char	com = RECEIVE_COMMAND::MAGIC_INFO;
		char infoType;
		int	id;
		Vector3	pos;
		float			angle;
	};

	//	魔法消去情報
	struct ReceiveMagicErase
	{
		char	com = RECEIVE_COMMAND::MAGIC_INFO;
		char infoType;
		int	index;
		ReceiveMagicErase(int index) : index(index){}
	};
}

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
		org->SetScale( 0.02f );
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
		for ( int i = 0; i < ( int )magicList.size(); i++ )
		{
			magicList[i]->Update();
			particle->Semicircle(magicList[i]->GetPos(), magicList[i]->GetFront(), magicList[i]->GetRight(), magicList[i]->GetUp(), magicList[i]->GetRadius(), 0.4f);
		}
	}

	//	描画
	void	MagicManager::Render( void )
	{
		for ( int i = 0; i < ( int )magicList.size(); i++ )
		{
			magicList[i]->Render();
		}
	}

//----------------------------------------------------------------------------------------------
//	動作関数
//----------------------------------------------------------------------------------------------

	//	情報受信
	void	MagicManager::Receive( const LPSTR& data )
	{
		switch ( data[1] )
		{
		case MAGIC_INFO::POS:
			{
				ReceiveMagicData	* receiveData = ( ReceiveMagicData* )data;
				SetPos( receiveData->index, receiveData->pos );
			}
			break;

		case MAGIC_INFO::APPEND:
			{
				ReceiveMagicAppend*	receiveData = ( ReceiveMagicAppend* )data;
				Append( receiveData->id, receiveData->pos, receiveData->angle );
			}
			break;

		case MAGIC_INFO::ERASE:
			{
				ReceiveMagicErase*	receiveMagicErase = ( ReceiveMagicErase* )data;
				Erase( receiveMagicErase->index );
			}
			break;

		default:
			break;
		}
	}

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