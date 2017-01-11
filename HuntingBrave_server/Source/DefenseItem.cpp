
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameParam.h"
#include	"DefenseItem.h"

//**************************************************************************
//
//	DefenseItemクラス
//
//**************************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

#define	EFFECTIVE_TIME		10.0f
#define	DOUBLE_PARAM		2.0f

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	DefenseItem::DefenseItem( int id ) : Item( id )
	{
	
	}

	//	デストラクタ
	DefenseItem::~DefenseItem( void )
	{

	}

//----------------------------------------------------------------------------------------------
//	更新
//----------------------------------------------------------------------------------------------

	//	更新
	void	DefenseItem::Update( void )
	{
		if ( timer->Update() )
		{
			//	無効中処理
			if ( state )
			{
				//	有効中処理
				gameParam->GetPlayerStatus( id ).defense =
					gameParam->GetPlayerStatus( id ).saveDefense;

				//	ステータスを無効
				state = false;

				//	送信
				SendStatusData sendData( SEND_STATUS::DEFENSE, ( float )gameParam->GetPlayerStatus( id ).defense );
				gameParam->send( id, ( LPSTR )&sendData, sizeof( sendData ) );
			}
		}
		else
		{
			//	有効中処理
			gameParam->GetPlayerStatus( id ).defense =
				( int )( gameParam->GetPlayerStatus( id ).saveDefense * DOUBLE_PARAM );

			//	送信
			SendStatusData sendData( SEND_STATUS::DEFENSE, ( float )gameParam->GetPlayerStatus( id ).defense );
			gameParam->send( id, ( LPSTR )&sendData, sizeof( sendData ) );
		}
	}

//----------------------------------------------------------------------------------------------
//	動作関数
//----------------------------------------------------------------------------------------------

	//	アイテム使用
	void	DefenseItem::UseItem( void )
	{
		timer->Start( EFFECTIVE_TIME );
		state = true;
	}

//----------------------------------------------------------------------------------------------
//	
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

