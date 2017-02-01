
#include	"iextreme.h"
#include	"GameParam.h"
#include	"PointManager.h"

//****************************************************************
//
//	PointManagerクラス
//
//****************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

//	実体
PointManager*	pointManager = nullptr;

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	PointManager::PointManager( void )
	{

	}

	//	デストラクタ
	PointManager::~PointManager( void )
	{

	}

//----------------------------------------------------------------------------------------------
//	動作関数
//----------------------------------------------------------------------------------------------

	//	ポイント計算
	void	PointManager::CalcPoint( int id, int point )
	{
		this->point[id] += point;

		if ( this->point[id] <= 0 )	this->point[id] = 0;
	}

	//	ポイント送信
	void	PointManager::SendPoint( int id )
	{
		SendPointData	sendPointData( id, point[id] );

		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			gameParam->send( p, ( LPSTR )&sendPointData, sizeof( sendPointData ) );
		}
	}

	//	討伐情報受信
	void	PointManager::ReceiveHuntInfo( int client, const LPSTR& data )
	{
		//	構造体宣言
		static	struct HuntInfo
		{
			char com;
			char infoType;
			char enemyType;
		} *huntInfo;
		
		//	変換
		huntInfo = ( HuntInfo* )data;

		//	計算、返信
		CalcPoint( client, 100 );
		SendPoint( client );
	}

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------


