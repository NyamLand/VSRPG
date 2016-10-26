
#include	"iextreme.h"
#include	"GameData.h"
#include	"PlayerManager.h"
#include	"GameParam.h"

//***************************************************************
//
//	GameParamクラス
//
//***************************************************************

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
		for ( int id = 0; id < PLAYER_MAX; id++ )
		{
			ZeroMemory( &playerInfo[id], sizeof( PlayerInfo ) );
			ZeroMemory( &playerParam[id], sizeof( PlayerParam ) );
		}
	}

	//	デストラクタ
	GameParam::~GameParam( void )
	{
		CloseClient();
	}
	
	//	クライアント初期化
	bool	GameParam::InitializeClient( char* addr, int nPort, char* name )
	{
		//	クライアント初期化
		InitializeUDP( nPort, addr );

		//	タイプと名前の送信
		NET_IN netIn( -1, name );
		send( ( char* )&netIn, sizeof( netIn ) );

		//	個人ID取得
		if( receive( ( char* )&netIn, sizeof( netIn ) ) <= 0 ) return false;
		myIndex = netIn.id;

		//	初期座標取得
		NET_CHARA	netChara;
		if ( receive( ( LPSTR )&netChara, sizeof( NET_CHARA ) ) <= 0 )	return	false;
		SetPlayerParam( myIndex, netChara.pos );

		return true;
	}

	//	脱退
	void	GameParam::CloseClient( void )
	{
		//	脱退メッセージ送信
		NET_OUT	netOut( myIndex );
		send( ( LPSTR )&netOut, sizeof( NET_OUT ) );
	}

//----------------------------------------------------------------------------------------------
//	データ送受信
//----------------------------------------------------------------------------------------------

	//	データ受信
	void	GameParam::Receive( void )
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
					ReceiveCharaInfo( data );
					break;

				case COMMANDS::SIGN_UP:		//	参加情報
					ReceiveSignUp( data );
					break;

				case COMMANDS::SIGN_OUT:		//	脱退情報
					ReceiveSignOut( data );
					break;
			}
		}
	}

	//	データ送信
	void	GameParam::Update( void )
	{
		//	全データ受信
		Receive();

		//	移動データ送信
		SendChraraInfo();
	}

//----------------------------------------------------------------------------------------------
//	データ送信
//----------------------------------------------------------------------------------------------

	//	移動情報送信
	void	GameParam::SendChraraInfo( void )
	{
		//	移動データ送信
		NET_CHARA	netChara( myIndex, playerManager->GetPlayer()->GetPos() );
		send( ( char*)&netChara, sizeof( netChara ) );
	}

//----------------------------------------------------------------------------------------------
//	データ受信
//----------------------------------------------------------------------------------------------

	//	キャラ情報受信
	void	GameParam::ReceiveCharaInfo( const LPSTR& data )
	{
		NET_CHARA*	netChara = ( NET_CHARA* )data;
		SetPlayerParam( netChara->id, netChara->pos );
	}

	//	サインアップ情報受信
	void	GameParam::ReceiveSignUp( const LPSTR& data )
	{
		NET_IN*	netIn = ( NET_IN* )data;
		SetPlayerInfo( netIn->id, netIn->name );
	}

	//	サインアウト情報受信
	void	GameParam::ReceiveSignOut( const LPSTR& data )
	{
		RemovePlayerInfo( ( ( NET_OUT* )data )->id ); 
	}

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

	//	プレイヤー情報設定
	void	GameParam::SetPlayerInfo( int id, char* name )
	{
		playerInfo[id].active = true;
		strcpy( playerInfo[id].name, name );
	}

	//	プレイヤー脱退
	void	GameParam::RemovePlayerInfo( int id )
	{
		playerInfo[id].active = false;
	}

	//	プレイヤーパラメータ設定
	void	GameParam::SetPlayerParam( int id, const Vector3& pos )
	{
		playerParam[id].pos    = pos;
		playerParam[id].angle  = 0.0f;
	}

	//	プレイヤーパラメータ設定
	void	GameParam::SetPlayerParam( int id, const PlayerParam& param )
	{
		playerParam[id].pos    = param.pos;
		playerParam[id].angle  = param.angle;
	}
