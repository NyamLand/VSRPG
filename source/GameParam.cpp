
#include	"iextreme.h"
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
			ZeroMemory( &playerInfo[id], sizeof( playerInfo[id] ) );
			ZeroMemory( &playerParam[id], sizeof( playerParam[id] ) );
		}

		//	関数ポインタ設定
		ReceiveFunction[DATA_MODE::POS] = &GameParam::PosReceive;
		ReceiveFunction[DATA_MODE::MOVE] = &GameParam::MoveReceive;
		ReceiveFunction[DATA_MODE::CHAT] = &GameParam::ChatReceive;
		ReceiveFunction[DATA_MODE::SIGN_UP] = &GameParam::SignUpReceive;
		ReceiveFunction[DATA_MODE::SIGN_OUT] = &GameParam::SignOutReceive;
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
		info.com = DATA_MODE::SIGN_UP;
		info.type = type;
		strcpy( info.name, name );

		//	サーバーにプレイヤー情報を送信
		SocketClient::Send( ( LPSTR )&info, sizeof( info ) );

		//	個人ＩＤ取得
		int	size = SocketClient::Receive( ( LPSTR )&info, sizeof( info ) );
		if ( size <= 0 )	return	false;
		myIndex = info.id;

		//	初期座標取得
		NET_POS netPos;
		netPos.com = DATA_MODE::POS;
		netPos.id = myIndex;
		SocketClient::Receive( ( LPSTR )&netPos, sizeof( netPos ) );
		playerManager->GetPlayer()->SetPos( netPos.pos );
		return	true;
	}

	//	脱退
	void	GameParam::CloseClient( void )
	{
		char	com = DATA_MODE::SIGN_OUT;
		SocketClient::Send( &com, sizeof( char ) );
	}

//----------------------------------------------------------------------------------
//	更新
//----------------------------------------------------------------------------------

	//	更新
	void	GameParam::Update( void )
	{
		//	全データ受信
		Receive();

		//	位置データ送信
		NET_POS	netData;

		//	プレイヤーの位置情報送信( 後で関数化 )
		netData.com = POS;
		netData.pos = playerManager->GetPlayer()->GetPos();
		SocketClient::Send( ( char* )&netData, sizeof( netData ) );
	}

//----------------------------------------------------------------------------------
//	データ送受信
//----------------------------------------------------------------------------------

	//	受信
	void	GameParam::Receive( void )
	{
		char data[256];

		//	データを受信
		int	size = SocketClient::Receive( data, 256 );
		if ( size <= 0 )	return;
		if ( data[0] == -1 )	return;

		//	先頭バイトで分岐
		( this->*ReceiveFunction[data[0]] )( data );
	}

	//	送信
	void	GameParam::Send( void )
	{

	}

//----------------------------------------------------------------------------------
//	各データ受信
//----------------------------------------------------------------------------------
	
	//	座標受信
	void	GameParam::PosReceive( LPSTR data )
	{
		SetPlayerParam(
			*( ( int* )&data[1] ),
			*( ( PlayerParam* )&data[5] ) );
	}

	//	移動値受信
	void	GameParam::MoveReceive( LPSTR data )
	{
		SetPlayerParam(
			*( ( int* )&data[1] ),
			*( ( PlayerParam* )&data[5] ) );
	}

	//	チャットデータ受信
	void	GameParam::ChatReceive( LPSTR data )
	{

	}

	//	参加情報受信
	void	GameParam::SignUpReceive( LPSTR data )
	{
		NET_INFO*	info;
		info = ( NET_INFO* )data;
		SetPlayerInfo( info->id, info->name, info->type );
	}

	//	退室情報受信
	void	GameParam::SignOutReceive( LPSTR data )
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