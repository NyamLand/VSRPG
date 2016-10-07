
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"PlayerManager.h"
#include	"UIParam.h"

//***************************************************************
//
//	UIParamクラス
//
//***************************************************************

//----------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------

UIParam*	UIParam = nullptr;

//----------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------

	//	コンストラクタ
	UIParam::UIParam( void )
	{
		//	プレイヤーデータ初期化
		for ( int id = 0; id < PLAYER_MAX; id++ ) playerInfo[id].active = false;

		//	チャット初期化
	}

	//	デストラクタ
	UIParam::~UIParam( void )
	{
		CloseClient();
	}

	//	クライアント初期化
	bool	UIParam::InitializeClient( LPSTR addr, int nPort, LPSTR name, int type )
	{
		//	クライアント初期化
		InitializeUDP( nPort, addr );

		//	タイプと名前の送信
		NET_INFO	info;
		info.com = RECEIVE_MODE::SIGN_UP;
		info.type = type;
		strcpy( info.name, name );

		//	サーバーにプレイヤー情報を送信
		SocketClient::Send( ( LPSTR )&info, sizeof( info ) );

		//	個人ＩＤしゅとく
		int	size = SocketClient::Receive( ( LPSTR )&info, sizeof( info ) );
		if ( size <= 0 )	return	false;
		myIndex = info.id;

		return	true;
	}

	//	脱退
	void	UIParam::CloseClient( void )
	{
		char	com = RECEIVE_MODE::SIGN_OUT;
		SocketClient::Send( &com, sizeof( char ) );
	}

//----------------------------------------------------------------------------------
//	更新
//----------------------------------------------------------------------------------

	//	更新
	void	UIParam::Update( void )
	{
		//	全データ受信
		Receive();

		//	位置データ送信
		NET_POS	netData;

		netData.com = POS;
		netData.pos = playerManager->GetPlayer()->GetPos();
		SocketClient::Send( ( char* )&netData, sizeof( netData ) );
		//int a = 0;
	}

//----------------------------------------------------------------------------------
//	データ送受信
//----------------------------------------------------------------------------------

	//	受信
	void	UIParam::Receive( void )
	{
		char data[256];

		//	データを受信
		int	size = SocketClient::Receive( data, 256 );
		if ( size <= 0 )
		{
			return;
		}
		if ( data[0] == -1 )
		{
			return;
		}
		//	先頭バイトで分岐
		switch ( data[0] )
		{
		case RECEIVE_MODE::MOVE:	//	キャラデータ
			SetPlayerParam( 
				*( ( int* )&data[1] ),
				*( ( PlayerParam* )&data[5] ) );
			break;

		case RECEIVE_MODE::CHAT:	//	チャット
			break;

		case RECEIVE_MODE::SIGN_UP:	//	新規参入
			{
				NET_INFO*	info;
				info = ( NET_INFO* )data;
				SetPlayerInfo( info->id, info->name, info->type );
			}
			break;

		case RECEIVE_MODE::SIGN_OUT:	//	退室
			break;
		}	
	}

	//	送信
	//void	UIParam::Send( PlayerParam playerParam )
	//{
	//	
	//}

//----------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------

	//	プレイヤー情報設定
	void	UIParam::SetPlayerInfo( int id, LPSTR name, int type )
	{
		playerInfo[id].active = true;
		playerInfo[id].type = type;
		strcpy( playerInfo[id].name, name );
	}

	//	プレイヤーパラメータ設定
	void	UIParam::SetPlayerParam( int id, Vector3& pos, float angle, int motion )
	{
		playerParam[id].pos = pos;
		playerParam[id].angle = angle;
		playerParam[id].motion = motion;
	}

	//	プレイヤーパラメータ設定
	void	UIParam::SetPlayerParam( int id, PlayerParam& param )
	{
		playerParam[id].pos = param.pos;
		playerParam[id].angle = param.angle;
		playerParam[id].motion = param.motion;
		printf("x = %f y = %f z = %f\n", playerParam[id].pos.x, playerParam[id].pos.y, playerParam[id].pos.z );
	}

//----------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------

