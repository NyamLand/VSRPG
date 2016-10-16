
#include	"iextreme.h"
#include	<thread>
#include	"GlobalFunction.h"
#include	"PlayerManager.h"
#include	"GameParam.h"

//***************************************************************
//
//	GameParamクラス
//
//***************************************************************

//----------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------

GameParam*	gameParam = nullptr;

//----------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------

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
	bool	GameParam::InitializeClient( LPSTR addr, int nPort, LPSTR name, int type )
	{
		//	クライアント初期化
		InitializeUDP( nPort, addr );

		//	タイプと名前の送信
		NET_IN		netIn;
		netIn.id = -1;
		strcpy( netIn.name, name );

		//	サーバーにプレイヤー情報を送信
		SocketClient::Send( ( LPSTR )&netIn, sizeof( netIn ) );

		//	個人ＩＤ取得
		int	size = SocketClient::Receive( ( LPSTR )&netIn, sizeof( netIn ) );
		if ( size <= 0 )	return	false;
		myIndex = netIn.id;
		SetPlayerInfo( netIn.id, netIn.name );

		//	初期座標取得
		NET_CHARA netChara;
		SocketClient::Receive( ( LPSTR )&netChara, sizeof( netChara ) );
		playerManager->GetPlayer()->SetPos( netChara.pos );
		return	true;
	}

	//	脱退
	void	GameParam::CloseClient( void )
	{
		NET_OUT	netOut;
		netOut.id = myIndex;
		SocketClient::Send( ( LPSTR )&netOut, sizeof( NET_OUT ) );
	}

//----------------------------------------------------------------------------------
//	更新
//----------------------------------------------------------------------------------

	//	更新
	void	GameParam::Update( void )
	{
	}

//----------------------------------------------------------------------------------
//	データ送受信
//----------------------------------------------------------------------------------

	//	受信
	void	GameParam::Receive( void )
	{
		char data[256];

		//	データを受信
		for (;;)
		{
			//	受信
			int	size = SocketClient::Receive( data, 256 );

			//	受信出来るサイズがなければループを抜ける
			if ( size <= 0 )	return; 

			//	先頭アドレスが不正ならばループを抜ける
			if ( data[COMMAND] == NO_COMMAND )	{ return; }

			//	先頭バイトで分岐
			switch ( data[COMMAND] )
			{
			case COMMANDS::CHARA_INFO:
				CharaInfoReceive( data );
				break;

			case COMMANDS::SIGN_UP:
				SignUpReceive( data );
				break;

			case COMMANDS::SIGN_OUT:
				SignOutReceive( data );
				break;

			default:
				printf( "????\n" );
				break;
			}
		}
	}

	//	送信
	void	GameParam::Send( void )
	{
		//	位置データ送信
		SendCharaData();
	}

//----------------------------------------------------------------------------------
//	受信処理
//----------------------------------------------------------------------------------

	//	キャラデータ受信
	void	GameParam::CharaInfoReceive( const LPSTR& data )
	{
		NET_CHARA*	netChara = ( NET_CHARA* )data;
		SetPlayerParam( netChara->id, netChara->pos, netChara->angle );
	}

	//	サインアップ受信
	void	GameParam::SignUpReceive( const LPSTR& data )
	{
		NET_IN*	netIn = ( NET_IN* )data;
		SetPlayerInfo( netIn->id, netIn->name );
		printf( "%dP %sが参加しました。\n", netIn->id, netIn->name );
	}

	//	サインアウト受信
	void	GameParam::SignOutReceive( const LPSTR& data )
	{
		NET_OUT*	netOut = ( NET_OUT* )data;
		playerInfo[netOut->id].active = false;
		printf( "%dP %sさんがログアウトしました。\n", netOut->id, playerInfo[netOut->id].name );
	}

//----------------------------------------------------------------------------------
//	送信処理
//----------------------------------------------------------------------------------

	//	位置データ送信
	void	GameParam::SendCharaData( void )
	{
		//	位置データ送信
		NET_CHARA	netChara;

		//	プレイヤーの位置情報送信( 後で関数化 )
		netChara.id = myIndex;
		netChara.pos = playerManager->GetPlayer()->GetPos();
		netChara.angle = playerManager->GetPlayer()->GetAngle();
		SocketClient::Send( ( LPSTR )&netChara, sizeof( NET_CHARA ) );
	}

//----------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------

	//	プレイヤー情報設定
	void	GameParam::SetPlayerInfo( int id, const LPSTR& name )
	{
		playerInfo[id].active = true;
		strcpy( playerInfo[id].name, name );
	}

	//	プレイヤーパラメータ設定
	void	GameParam::SetPlayerParam( int id, const Vector3& pos, float angle )
	{
		playerParam[id].pos = pos;
		playerParam[id].angle = angle;
	}

	//	プレイヤーパラメータ設定
	void	GameParam::SetPlayerParam( int id, const PlayerParam& param )
	{
		playerParam[id].pos = param.pos;
		playerParam[id].angle = param.angle;
	}

//----------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------

	//	各プレイヤー情報取得
	PlayerInfo	GameParam::GetPlayerInfo( int id )const
	{
		return	playerInfo[id];
	}

	//	各プレイヤーパラメータ取得
	PlayerParam GameParam::GetPlayerParam( int id )const
	{
		return	playerParam[id];
	}

	//	自分のId取得
	PlayerInfo	GameParam::GetMyInfo( int id )const
	{
		return	playerInfo[id];
	}

	//	自分のID取得( Player番号 )
	int		GameParam::GetMyIndex( void )const
	{
		return	myIndex;
	}