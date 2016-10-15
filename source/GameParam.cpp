
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
		netIn.com = COMMANDS::SIGN_UP;
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
		playerManager->GetPlayer()->SetPos( Vector3( netChara.x, netChara.y, netChara.z ) );
		return	true;
	}

	//	脱退
	void	GameParam::CloseClient( void )
	{
		NET_OUT	netOut;
		netOut.com = SIGN_OUT;
		netOut.id = myIndex;
		SocketClient::Send( ( LPSTR )&netOut, sizeof( NET_OUT ) );
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
		NET_CHARA	netChara;

		//	プレイヤーの位置情報送信( 後で関数化 )
		netChara.com = COMMANDS::CHARA_INFO;
		netChara.id = myIndex;
		netChara.x = playerManager->GetPlayer()->GetPos().x;
		netChara.y = playerManager->GetPlayer()->GetPos().y;
		netChara.z = playerManager->GetPlayer()->GetPos().z;
		netChara.angle = playerManager->GetPlayer()->GetAngle();
		SocketClient::Send( ( LPSTR )&netChara, sizeof( NET_CHARA ) );
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
			if ( size <= 0 )	
			{ 
				printf( "size = %d\n", size );
				return; 
			}

			//	先頭アドレスが不正ならばループを抜ける
			if ( data[COMMAND] == NO_COMMAND )	{ return; }

			//	先頭バイトで分岐
			switch ( data[COMMAND] )
			{
			case COMMANDS::CHARA_INFO:
				{
					NET_CHARA*	netChara = ( NET_CHARA* )&data;
					SetPlayerParam( netChara->id, Vector3( netChara->x, netChara->y, netChara->z ), netChara->angle );
				}
				break;

			case COMMANDS::SIGN_UP:
				{
					NET_IN*	netIn = ( NET_IN* )&data;
					SetPlayerInfo( netIn->id, netIn->name );
					printf( "%dP %sが参加しました。\n", netIn->id, netIn->name );
				}
				break;

			case COMMANDS::SIGN_OUT:
				{
					NET_OUT*	netOut = ( NET_OUT* )&data;
					playerInfo[netOut->id].active = false;
					printf( "%dP %sさんがログアウトしました。\n", netOut->id, playerInfo[netOut->id].name );
				}
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

	}

//----------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------

	//	プレイヤー情報設定
	void	GameParam::SetPlayerInfo( int id, const LPSTR name )
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
	void	GameParam::SetPlayerParam( int id, PlayerParam& param )
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