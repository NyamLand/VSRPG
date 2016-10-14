
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
		NET_INFO	info;
		info.com = COMMANDS::SIGN_UP;
		info.id = -1;
		info.type = type;
		strcpy( info.name, name );

		//	サーバーにプレイヤー情報を送信
		SocketClient::Send( ( LPSTR )&info, sizeof( info ) );

		//	個人ＩＤ取得
		int	size = SocketClient::Receive( ( LPSTR )&info, sizeof( info ) );
		if ( size <= 0 )	return	false;
		myIndex = info.id;
		SetPlayerInfo( info.id, info.name, info.type );

		//	初期座標取得
		NET_MOVE netMove;
		netMove.com = COMMANDS::CHARA_INFO;
		netMove.id = myIndex;
		SocketClient::Receive( ( LPSTR )&netMove, sizeof( netMove ) );
		playerManager->GetPlayer()->SetPos( Vector3( netMove.x, 0.0f, netMove.z ) );
		return	true;
	}

	//	脱退
	void	GameParam::CloseClient( void )
	{
		char	com = COMMANDS::SIGN_OUT;
		SocketClient::Send( &com, sizeof( char ) );
	}

//----------------------------------------------------------------------------------
//	更新
//----------------------------------------------------------------------------------

	//	更新
	void	GameParam::Update( void )
	{
		//	全データ受信
		//Receive();

		//	位置データ送信
		NET_MOVE	netMove;

		//	プレイヤーの位置情報送信( 後で関数化 )
		netMove.com = COMMANDS::CHARA_INFO;
		netMove.id = myIndex;
		netMove.x = playerManager->GetPlayer()->GetPos().x;
		netMove.y = playerManager->GetPlayer()->GetPos().y;
		netMove.z = playerManager->GetPlayer()->GetPos().z;
		SocketClient::Send( ( LPSTR )&netMove, sizeof( NET_MOVE ) );

		printf( "座標を送信しました。\n" );
	}

//----------------------------------------------------------------------------------
//	データ送受信
//----------------------------------------------------------------------------------

	//	受信
	void	GameParam::Receive( void )
	{
		char data[256];

		//	データを受信
		//for (;;)
		{
			//	受信
			int	size = SocketClient::Receive( data, 256 );

			//	受信出来るサイズがなければループを抜ける
			if ( size <= 0 )	
			{ 
				printf( "size = %d\n", size );
				return; 
			}

			//	先頭アドレスが不正ならばループを抜ける
			if ( data[0] == -1 )	{ return; }

			//	先頭バイトで分岐
			switch ( data[0] )
			{
			case COMMANDS::CHARA_INFO:
				{
					NET_MOVE*	netMove = ( NET_MOVE* )data;
					SetPlayerParam( netMove->id, Vector3( netMove->x, 0.0f, netMove->z ), 0.0f, 0 );
					printf( "座標受信しました。\n" );
				}
				break;

			case COMMANDS::SIGN_UP:
				{
					NET_INFO*	info;
					info = ( NET_INFO* )data;

					SetPlayerInfo( info->id, info->name, info->type );

					printf( "サインアップしました。\n" );
				}
				break;

			case COMMANDS::SIGN_OUT:
				break;
			}
		}
	}

	//	送信
	void	GameParam::Send( void )
	{

	}

//----------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------

	//	プレイヤー情報設定
	void	GameParam::SetPlayerInfo( int id, LPSTR name, int type )
	{
		playerInfo[id].active = true;
		playerInfo[id].type = type;
		strcpy( playerInfo[id].name, name );
	}

	//	プレイヤーパラメータ設定
	void	GameParam::SetPlayerParam( int id, Vector3& pos, float angle, int motion )
	{
		playerParam[id].pos = pos;
		playerParam[id].angle = angle;
		playerParam[id].motion = motion;
	}

	//	プレイヤーパラメータ設定
	void	GameParam::SetPlayerParam( int id, PlayerParam& param )
	{
		playerParam[id].pos = param.pos;
		playerParam[id].angle = param.angle;
		playerParam[id].motion = param.motion;
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