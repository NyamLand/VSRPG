
#include	"iextreme.h"
#include	"GlobalFunction.h"
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
		for ( int id = 0; id < PLAYER_MAX; id++ )
		{
			playerInfo[id].active = false;

			playerParam[id].pos = Vector3( -10.0f + 5.0f * id, 0.0f, 0.0f );
			playerParam[id].angle = 0.0f;
			playerParam[id].motion = 0;
		}
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
			data[0] = 0;

			//	一番目にプレイヤー番号保存
			*( int* )&data[1] = p;
			
			//	五番目以降にパラメータ情報保存
			CopyMemory( &data[5], &playerParam[p], sizeof( PlayerParam ) );
			UDPServer::Send( client, data, sizeof( PlayerParam )+5 );
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
		
		if ( client == -1 )		return	-1;

		//	dataの０番目によって処理を変える
		switch ( data[0] )
		{
			//	移動情報受信
			case RECEIVE_MODE::MOVE:
				{
					NET_MOVE* d = ( NET_MOVE* )data;
					playerParam[client].move = Vector3( d->vx, 0.0f, d->vz );
				}
				break;

			//	チャット
			case RECEIVE_MODE::CHAT:
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

					//	チャットの場合クライアントではなく-１を返す
					return	-1;
				}
				break;

			case RECEIVE_MODE::SIGN_UP:
				{
					//	プレイヤーを登録する
					NET_INFO*	d = ( NET_INFO* )data;
					SetPlayer( client, d->name, d->type );

					//	構造体のidメンバを設定し送信者へ送信する
					d->id = client;
					UDPServer::Send( d->id, ( LPSTR )d, sizeof( NET_INFO ) );

					//	全員に情報送信
					for ( int p = 0; p < PLAYER_MAX; p++ )
					{
						if ( playerInfo[p].active == false )continue;
						UDPServer::Send( p, ( LPSTR )d, sizeof( NET_INFO ) );

						//	全員の情報を新規プレイヤーに送信
						for ( int p = 0; p < PLAYER_MAX; p++ )
						{
							//	プレイヤーがいなければスキップ
							if ( playerInfo[p].active == false )continue;

							//	構造体にコピー
							d->id = p;
							d->type = playerInfo[p].type;
							strcpy( d->name, playerInfo[p].name );
						
							//	送信
							UDPServer::Send( client, ( LPSTR )d, sizeof( NET_INFO ) );
						}
					}
				}
				break;

			case RECEIVE_MODE::SIGN_OUT:
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
						if ( playerInfo[p].active == false )	continue;
						UDPServer::Send( p, ( LPSTR )&d, sizeof( NET_OUT ) );
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

//-------------------------------------------------------------------------------------
//	更新・描画
//-------------------------------------------------------------------------------------


