
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameParam.h"
#include	<vector>
#include	<algorithm>
#include	"PointManager.h"

//***************************************************************
//
//	PointManagerクラス
//
//***************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

	namespace
	{
		//	点数情報
		struct ReceivePointData
		{
			char	com = RECEIVE_COMMAND::POINT_INFO;
			int		id;
			int		point;
		};
	}

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	PointManager::PointManager( void )
	{
		pointList.clear();
	}

	//	デストラクタ
	PointManager::~PointManager( void )
	{
		Release();
	}

	//	初期化
	bool	PointManager::Initialize( void )
	{
		pointList.clear();

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			PointInfo	pointInfo{ i, 0 };
			pointList.push_back( pointInfo );
		}
		return	true;
	}

	//	解放
	void	PointManager::Release( void )
	{
		pointList.clear();
	}

//----------------------------------------------------------------------------------------------
//	更新・描画
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	動作関数
//----------------------------------------------------------------------------------------------

	//	受信
	void	PointManager::Receive( const LPSTR& data )
	{
		ReceivePointData*	receivePointData = ( ReceivePointData* )data;

		Sort();
		int index = GetRank( receivePointData->id );
		pointList[index].point = receivePointData->point;
	}

	//	ソート
	void	PointManager::Sort( void )
	{
		std::sort( pointList.begin(), pointList.end() );
	}

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------------------

	//	プレイヤーランク取得( 順位を指定して、その順位のプレイヤー番号を取得 )
	int	PointManager::GetRank( int player )
	{
		//	条件に合うイテレータを取得
		auto	result = std::find( pointList.begin(), pointList.end(), player );

		//	インデックスを取得
		int	index = std::distance( pointList.begin(), result );

		return	index;
	}

	//	点数取得
	int	PointManager::GetPoint( int player )
	{
		int index = GetRank( player );
		int point = pointList[index].point;
		return	point;
	}

	//	指定したランクのプレイヤー取得
	int	PointManager::GetPlayer( int rank )
	{
		//	ソートかける
		Sort();
		
		//	指定したランクのID取得
		int index = pointList[rank].id;
		return	index;
	}