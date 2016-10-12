
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameManager.h"
#include	"GameParam.h"

//***************************************************************
//
//	GameParamクラス
//
//***************************************************************

//-------------------------------------------------------------------------------------
//	グローバル
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//	初期化・解放
//-------------------------------------------------------------------------------------

	//	コンストラクタ
	GameParam::GameParam( void )
	{
		//	初期化
		for ( int id = 0; id < PLAYER_MAX; id++ )
		{
			ZeroMemory( &playerInfo[id], sizeof( playerInfo[id] ) );			
			ZeroMemory( &playerParam[id], sizeof( playerInfo[id] ) );
			playerParam[id].pos = Vector3( -10.0f + 5.0f * id, 0.0f, 0.0f );
			playerParam[id].angle = 0.0f;
			playerParam[id].motion = 0;
		}

		//	関数ポインタ
		ReceiveFunction[DATA_MODE::POS] = &GameParam::PosReceive;
		ReceiveFunction[DATA_MODE::MOVE] = &GameParam::MoveReceive;
		ReceiveFunction[DATA_MODE::CHAT] = &GameParam::ChatReceive;
		ReceiveFunction[DATA_MODE::SIGN_UP] = &GameParam::SignUpReceive;
		ReceiveFunction[DATA_MODE::SIGN_OUT] = &GameParam::SignOutReceive;
	}

	//	デストラクタ
	GameParam::~GameParam( void )
	{

	}
	
	//	サーバー初期化
	bool	GameParam::InitializeServer( void )
	{
		WSADATA	wsaData;
		
		//	要求するWinSockのバージョン
		WSAStartup( MAKEWORD( 1, 1 ), &wsaData );

		//	ポート番号
		Initialize( PORT_NUM );

		return	true;
	}

//-------------------------------------------------------------------------------------
//	更新・描画
//-------------------------------------------------------------------------------------

	//	描画
	void	GameParam::Render( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			char str[256];
			sprintf_s( str, "%dP ", p + 1 );

			//	アクティブ状態なら情報表示
			if ( playerInfo[p].active )
			{
				//	アクティブ情報設定
				strcat( str, "active  " );

				//	名前設定
				strcat( str, playerInfo[p].name );
				
				//	座標設定
				Vector3 pos = playerParam[p].pos;
				char posInfo[256];
				sprintf_s( posInfo, "  pos : %.2f, %.2f, %.2f", pos.x, pos.y, pos.z );
				strcat( str, posInfo );
			}

			IEX_DrawText( str, 20, 100 + p * 30, 500, 200, 0xFFFFFF00 );
		}

	}

//-------------------------------------------------------------------------------------
//	受信・送信
//-------------------------------------------------------------------------------------

	//	送信
	int		GameParam::Send( int client )
	{
		//	全クライアントに各プレイヤーの情報を送信する
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	プレイヤーがアクティブ状態でなければスキップ
			if ( playerInfo[p].active == false )		continue;

			char	data[256];
			data[0] = DATA_MODE::POS;

			//	一番目にプレイヤー番号保存
			*( int* )&data[1] = p;
			
			//	五番目以降にパラメータ情報保存
			CopyMemory( &data[5], &playerParam[p], sizeof( PlayerParam ) );
			UDPServer::Send( client, data, sizeof( PlayerParam )+5 );

			if ( client == 1 )
			{
				printf( "aaan\n" );
			}
		}

		char	end = -1;
		UDPServer::Send( client, &end, 1 );

		return	client;
	}

	//	受信( ( 仮 ) 要関数化 )
	int		GameParam::Receive( void )
	{
		int		client = -1;
		char	data[256];

		int	size = sizeof( data );
		client = UDPServer::Receive( data, &size );

		if ( client == 1 )
		{
			printf( "aaaa\n" );
		}
		
		if ( client == -1 )		return	-1;

		int out;

		//	各受信動作
		switch ( data[0] )
		{
		case DATA_MODE::MOVE:
			out = MoveReceive( client, data );
			break;
			
		case DATA_MODE::POS:
			out = PosReceive( client, data );
			break;

		case DATA_MODE::CHAT:
			out = ChatReceive( client, data );
			break;

		case DATA_MODE::SIGN_UP:
			out = SignUpReceive( client, data );
			break;

		case DATA_MODE::SIGN_OUT:
			out = SignOutReceive( client, data );
			break;
		}
		return	out;
	}

//-------------------------------------------------------------------------------------
//	各受信動作関数
//-------------------------------------------------------------------------------------

	//	移動情報受信
	int		GameParam::MoveReceive( int client, LPSTR data )
	{
		NET_MOVE* d = ( NET_MOVE* )data;
		playerParam[client].move = Vector3( d->vx, 0.0f, d->vz );

		return	client;
	}

	//	位置情報取得
	int		GameParam::PosReceive( int client, LPSTR data )
	{
		NET_POS* d = ( NET_POS* )data;
		playerParam[client].pos = d->pos;

		return	client;
	}

	//	チャット情報取得
	int		GameParam::ChatReceive( int client, LPSTR data )
	{
		//	idにクライアントIDをセット
		NET_CHAT*	chat = ( NET_CHAT* )data;
		chat->id = client;

		//	全員にメッセージを送信
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	いなければスキップ
			if ( playerInfo[p].active == false )continue;

			UDPServer::Send( p, ( LPSTR )chat, sizeof( NET_CHAT ) );
		}

		//	chatならば-1をかえす
		return	-1;
	}

	//	サインアップ情報取得
	int		GameParam::SignUpReceive( int client, LPSTR data )
	{
		//	プレイヤーを登録する
		NET_INFO*	d = ( NET_INFO* )data;
		SetPlayer( client, d->name, d->type );

		//	構造体のidメンバを設定し送信者へ返信する
		d->id = client;
		UDPServer::Send( d->id, ( LPSTR )d, sizeof( NET_INFO ) );

		//	初期座標を送信
		NET_POS*	netPos = ( NET_POS* )data;
		netPos->id = client;
		netPos->pos = gameManager->GetInitPos( client );
		UDPServer::Send( client, ( LPSTR )netPos, sizeof( NET_POS ) );

		//	全員に情報送信
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( !playerInfo[p].active )continue;
			UDPServer::Send( p, ( LPSTR )d, sizeof( NET_INFO ) );
		}
		
		//	全員の情報を新規プレイヤーに送信
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	プレイヤーがいなければスキップ
			if ( !playerInfo[p].active )continue;

			//	構造体にコピー
			d->id = p;
			d->type = playerInfo[p].type;
			strcpy( d->name, playerInfo[p].name );

			//	送信
			UDPServer::Send( client, ( LPSTR )d, sizeof( NET_INFO ) );
		}
		
		return	client;
	}

	//	サインアウト情報取得
	int		GameParam::SignOutReceive( int client, LPSTR data )
	{
		//	クライアント脱退
		playerInfo[client].active = false;
		CloseClient( client );

		//	脱退情報を全クライアントへ送信
		NET_OUT	d;
		d.com = SIGN_OUT;
		d.id = client;

		//	全員にデータ送信
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( !playerInfo[p].active )	continue;
			UDPServer::Send( p, ( LPSTR )&d, sizeof( NET_OUT ) );
		}

		return	client;
	}

//-------------------------------------------------------------------------------------
//	情報設定
//-------------------------------------------------------------------------------------

	//	プレイヤー情報の設定
	void	GameParam::SetPlayer( int id, LPSTR name, int type )
	{
		//	id番目のプレイヤーをアクティブにし、情報を受け取る
		playerInfo[id].active = true;
		playerInfo[id].type = type;
		strcpy( playerInfo[id].name, name );
		
		//	初期位置設定
		Vector3	pos = Vector3( -10.0f + 5.0f * id, 0.0f, 0.0f );
		playerParam[id].pos = pos;
		playerParam[id].angle = 0.0f;
		playerParam[id].motion = 1;
		playerParam[id].move = Vector3( 0.0f, 0.0f, 0.0f );
	}

	//	プレイヤーパラメータの設定
	void	GameParam::SetPlayerParam( int id, Vector3& pos, float angle, int motion )
	{
		playerParam[id].pos = pos;
		playerParam[id].angle = angle;
		playerParam[id].motion = motion;
	}

	//	プレイヤーパラメータの設定
	void	GameParam::SetPlayerParam( int id, PlayerParam& param )
	{
		playerParam[id].pos = param.pos;
		playerParam[id].angle = param.angle;
		playerParam[id].motion = param.motion;
	}

//-------------------------------------------------------------------------------------
//	情報取得
//-------------------------------------------------------------------------------------

	//	プレイヤーパラメータ取得
	PlayerParam& GameParam::GetPlayerParam( int id )
	{
		return	playerParam[id];
	}
//-------------------------------------------------------------------------------------
//	更新・描画
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//	更新・描画
//-------------------------------------------------------------------------------------


