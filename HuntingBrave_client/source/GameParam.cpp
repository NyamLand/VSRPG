
#include	"iextreme.h"
#include	"GameData.h"
#include	"PlayerManager.h"
#include	"GameParam.h"

//*****************************************************************************************************************************
//
//	GameParamクラス
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

GameParam*	gameParam = nullptr;

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	GameParam::GameParam( void )
	{
		//	プレイヤーデータ初期化
		for( int id = 0 ; id < PLAYER_MAX ; id++ ) playerInfo[id].active = false;
	}

	//	デストラクタ
	GameParam::~GameParam( void )
	{
		CloseClient();
	}
	
	//	クライアント初期化
	bool GameParam::InitializeClient( char* addr, int nPort, char* name )
	{
		//	クライアント初期化
		InitializeUDP( nPort, addr );

		//	タイプと名前の送信
		NET_IN netIn;
		netIn.com = COMMANDS::SIGN_UP;
		strcpy( netIn.name, name );
		send( ( char* )&netIn, sizeof( netIn ) );

		//	個人ID取得
		if( receive( ( char* )&netIn, sizeof( netIn ) ) <= 0 ) return false;
		myIndex = netIn.id;

		return true;
	}

	//	脱退
	void GameParam::CloseClient( void )
	{
		//	脱退メッセージ送信
		NET_OUT	netOut;
		netOut.com = COMMANDS::SIGN_OUT;
		netOut.id = myIndex;
		send( ( LPSTR )&netOut, sizeof( NET_OUT ) );
	}

//----------------------------------------------------------------------------------------------
//	データ送受信
//----------------------------------------------------------------------------------------------

	//	データ受信
	void GameParam::Receive( void )
	{
		//	全データ受信
		for(;;)
		{
			//	受信
			char	data[256];
			int size = receive( data, 256 );
			if( size <= 0 ) break;
		
			//	データ終端判定
			if( data[COMMAND] == NO_COMMAND ) break;

			//	先頭バイト（コマンド）による処理分岐
			switch( data[COMMAND] )
			{
				case COMMANDS::CHARA_INFO:	//	移動情報
					{
						NET_CHARA*	netChara = ( NET_CHARA* )&data;
						SetPlayerParam( netChara->id, netChara->pos );
					}
					break;

				case COMMANDS::SIGN_UP:		//	参加情報
					{
						NET_IN*	netIn = ( NET_IN* )data;
						SetPlayerInfo( netIn->id, netIn->name ); 
					}
					break;

				case COMMANDS::SIGN_OUT:		//	脱退情報
					RemovePlayerInfo( ( ( NET_OUT* )data )->id ); 
					break;
			}
		}
	}

	//	データ送信
	void GameParam::Update( void )
	{
		//	全データ受信
		Receive();

		//	移動データ送信
		NET_CHARA	netChara;
		netChara.com = COMMANDS::CHARA_INFO;
		netChara.id = myIndex;
		netChara.pos = playerManager->GetPlayer()->GetPos();
		send( ( char*)&netChara, sizeof( netChara ) );
	}

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

	//	プレイヤー情報設定
	void GameParam::SetPlayerInfo( int id, char* name )
	{
		playerInfo[id].active = true;
		strcpy( playerInfo[id].name, name );
	}

	//	プレイヤー脱退
	void GameParam::RemovePlayerInfo( int id )
	{
		playerInfo[id].active = false;
	}

	//	プレイヤーパラメータ設定
	void GameParam::SetPlayerParam( int id, Vector3& pos )
	{
		playerParam[id].pos    = pos;
		playerParam[id].angle  = 0.0f;
	}

	//	プレイヤーパラメータ設定
	void GameParam::SetPlayerParam( int id, PlayerParam& param )
	{
		playerParam[id].pos    = param.pos;
		playerParam[id].angle  = param.angle;
	}
