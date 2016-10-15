
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
			ZeroMemory( &playerInfo[id], sizeof( PlayerInfo ) );			
			ZeroMemory( &playerParam[id], sizeof( PlayerParam ) );
			playerParam[id].pos = Vector3( -10.0f + 5.0f * id, 0.0f, 0.0f );
		}
	}
	
	//	サーバー初期化
	bool	GameParam::InitializeServer( void )
	{
		//	WinSock初期化
		WSADATA	wsaData;
		
		//	要求するWinSockのバージョン
		WSAStartup( MAKEWORD( 1, 1 ), &wsaData );

		//	UDPサーバー初期化
		bool out = Initialize( PORT_NUM );

		return	out;
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
		NET_CHARA	netChara;
		netChara.com = COMMANDS::CHARA_INFO;
		
		//	全クライアントに各プレイヤーの情報を送信する
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	プレイヤーがアクティブ状態でなければスキップ
			if ( playerInfo[p].active == false )		continue;

			Vector3	pos = playerParam[p].pos;
			netChara.id = p;
			netChara.x = pos.x;
			netChara.y = pos.y;
			netChara.z = pos.z;
			netChara.angle = playerParam[p].angle;

			UDPServer::Send( client, ( LPSTR )&netChara, sizeof( NET_CHARA ) );

			printf( "%dPに座標送信しました。\n", p + 1 );
		}

		//	コマンド終端を伝える
		char	end = -1;
		UDPServer::Send( client, &end, 1 );

		return	client;
	}

	//	受信( ( 仮 ) 要関数化 )
	int		GameParam::Receive( void )
	{
		int		client = -1;
		char	data[256];

		//	データサイズ取得
		//	クライアントからのデータ受信とクライアント番号の受信
		int	size = sizeof( data );
		client = UDPServer::Receive( data, &size );
		if ( size <= 0 )	return	-1;
		if ( client < 0 )	return	-1;
		
		//	各受信動作
		switch ( data[DATA_INFO::COMMAND] )
		{
		case COMMANDS::CHARA_INFO:
			{
				NET_CHARA*	netChara = ( NET_CHARA* )&data;
				playerParam[client].pos = Vector3( netChara->x, netChara->y, netChara->z );
				playerParam[client].angle = netChara->angle;
			}
			break;

		case COMMANDS::SIGN_UP:
			{
				//	受け取ったデータをクライアント情報に変換
				NET_IN* netIn= ( NET_IN* )&data;
				SetPlayer( client, netIn->name );

				//	構造体のidメンバを設定
				netIn->id = client;

				//	クライアントに返信
				UDPServer::Send( client, ( LPSTR )netIn, sizeof( NET_IN ) );

				//	初期座標を送信
				NET_CHARA	netChara;
				netChara.com = COMMANDS::CHARA_INFO;
				netChara.id = client;
				netChara.x = gameManager->GetInitPos( client ).x;
				netChara.y = gameManager->GetInitPos( client ).y;
				netChara.z = gameManager->GetInitPos( client ).z;
				netChara.angle = 0.0f;
				UDPServer::Send( client, ( LPSTR )&netChara, sizeof( NET_CHARA ) );

				//	クライアント全員にデータを送信
				for ( int p = 0; p < PLAYER_MAX; p++ )
				{
					if ( playerInfo[p].active == false )	continue;
					UDPServer::Send( p, ( LPSTR )netIn, sizeof( NET_IN ) );
				}

				//	新規のクライアントに全員のデータを送信
				for ( int p = 0; p < PLAYER_MAX; p++ )
				{
					if ( playerInfo[p].active == false )	continue;

					netIn->id = p;
					strcpy( netIn->name, playerInfo[p].name );
					UDPServer::Send( client, ( LPSTR )netIn, sizeof( NET_IN ) );
				}

				printf( "%dPが参戦しました。\n", client + 1 );
			}
			break;

		case COMMANDS::SIGN_OUT:
			{
				//	プレイヤーアクティブをfalseにする
				playerInfo[client].active = false;

				//	クライアントを閉じる
				CloseClient( client );

				NET_OUT	out;
				out.com = COMMANDS::SIGN_OUT;
				out.id = client;

				//	全員に情報送信
				for ( int p = 0; p < PLAYER_MAX; p++ )
				{
					if ( playerInfo[p].active == false )	continue;
					UDPServer::Send( p, ( LPSTR )&out, sizeof( NET_OUT ) );
				}

				printf( "%dPが脱退しました。\n", client + 1 );
			}
			break;
		}
		return	client;
	}

//-------------------------------------------------------------------------------------
//	情報設定
//-------------------------------------------------------------------------------------

	//	プレイヤー情報の設定
	void	GameParam::SetPlayer( int id, const LPSTR name )
	{
		//	id番目のプレイヤーをアクティブにし、情報を受け取る
		playerInfo[id].active = true;
		strcpy( playerInfo[id].name, name );
		
		//	初期位置設定
		Vector3	pos = gameManager->GetInitPos( id );
		playerParam[id].pos = pos;
		playerParam[id].angle = 0.0f;
	}

	//	プレイヤーパラメータの設定
	void	GameParam::SetPlayerParam( int id, const Vector3& pos, float angle )
	{
		playerParam[id].pos = pos;
		playerParam[id].angle = angle;
	}

	//	プレイヤーパラメータの設定
	void	GameParam::SetPlayerParam( int id, const PlayerParam& param )
	{
		playerParam[id].pos = param.pos;
		playerParam[id].angle = param.angle;
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


