
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
			playerParam[id].angle = 0.0f;
			playerParam[id].motion = 0;
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

			NET_MOVE	netMove;
			netMove.com = COMMANDS::CHARA_INFO;
			netMove.id = p;
			netMove.x = playerParam[p].pos.x;
			netMove.y = playerParam[p].pos.y;
			netMove.z = playerParam[p].pos.z;

			UDPServer::Send( client, ( LPSTR )&netMove, sizeof( NET_MOVE ) );
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
		int	size = sizeof( data );

		//	クライアントからのデータ受信とクライアント番号の受信
		client = UDPServer::Receive( data, &size );
		
		if ( client == -1 )		return	-1;

		//	各受信動作
		switch ( data[0] )
		{
		case COMMANDS::CHARA_INFO:
			{
				NET_MOVE*	move = ( NET_MOVE* )data;
				playerParam[client].pos = Vector3( move->x, move->y, move->z );
			}
			break;

		case COMMANDS::SIGN_UP:
			{
				//	受け取ったデータをクライアント情報に変換
				NET_INFO*	info = ( NET_INFO* )&data;
				SetPlayer( client, info->name, info->type );

				//	構造体のidメンバを設定
				info->id = client;

				//	クライアントに返信
				UDPServer::Send( client, ( LPSTR )info, sizeof( NET_INFO ) );

				int a = 0;
				//	初期座標を送信
				NET_MOVE*	netMove = ( NET_MOVE* )data;
				netMove->com = COMMANDS::CHARA_INFO;
				netMove->id = client;
				netMove->x = gameManager->GetInitPos( client ).x;
				netMove->y = gameManager->GetInitPos( client ).y;
				netMove->z = gameManager->GetInitPos( client ).z;
				UDPServer::Send( client, ( LPSTR )netMove, sizeof( NET_MOVE ) );

				//	クライアント全員にデータを送信
				for ( int p = 0; p < PLAYER_MAX; p++ )
				{
					if ( playerInfo[p].active == false )	continue;
					UDPServer::Send( p, ( LPSTR )info, sizeof( NET_INFO ) );
				}

				//	新規のクライアントに全員のデータを送信
				for ( int p = 0; p < PLAYER_MAX; p++ )
				{
					if ( playerInfo[p].active == false )	continue;
					info->id = p;
					info->type = playerInfo[p].type;

					strcpy( info->name, playerInfo[p].name );
					UDPServer::Send( client, ( LPSTR )info, sizeof( NET_INFO ) );
				}
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
			}
			break;
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
		Vector3	pos = gameManager->GetInitPos( id );
		playerParam[id].pos = pos;
		playerParam[id].angle = 0.0f;
		playerParam[id].motion = 1;
		//playerParam[id].move = Vector3( 0.0f, 0.0f, 0.0f );
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


