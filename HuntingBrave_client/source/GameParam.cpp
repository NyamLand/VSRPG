
#include	"iextreme.h"
#include	"system\/System.h"
#include	"GameData.h"
#include	"GameManager.h"
#include	"PlayerManager.h"
#include	"GameParam.h"
#include	"sceneMatching.h"

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
			ZeroMemory(&pointInfo[id], sizeof(PointInfo));
			ZeroMemory(&matchingInfo[id], sizeof(MatchingInfo));
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
		SetPlayerPos( myIndex, netChara.pos );

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

				case COMMANDS::CHARA_RECEIVEDATA:	//必要情報全部
					ReceiveCharaDATA( data );
					break;

				case COMMANDS::CHAR_MOVE:	//	移動情報
					ReceiveCharaMove( data );
					break;

				case COMMANDS::GAME_INFO:	//	ゲーム情報
					ReceiveGameInfo( data );
					break;

				case COMMANDS::POINT_INFO:	//	点数情報
					ReceivePoint( data );
					break;

				case COMMANDS::MATCHING:		//	マッチング情報
					ReceiveMatching(data);
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
		//SendChraraInfo();

		//	移動データ送信
		SendMove();

		//	点数データ送信
		SendPoint();

		//マッチング状態送信
		SendMatching();
	}

//----------------------------------------------------------------------------------------------
//	データ送信
//----------------------------------------------------------------------------------------------

	//	移動情報送信
	void	GameParam::SendChraraInfo( void )
	{
		NET_CHARA	netChara( myIndex, 
			playerManager->GetPlayer( myIndex )->GetPos(),
			playerManager->GetPlayer( myIndex )->GetAngle(),
			0 );

		send( ( LPSTR )&netChara, sizeof( NET_CHARA ) );
	}

	//	移動情報送信
	void	GameParam::SendMove( void )
	{
		//	移動データ送信
		float axisX = 0.0f, axisY = 0.0f;
		if ( playerManager->GetPlayer( myIndex )->GetMode() == MODE::MOVE )
		{
			GetStickInput( axisX, axisY );
		}

		NET_MOVE	netMove( myIndex, axisX, axisY );
		send( ( LPSTR )&netMove, sizeof( netMove ) );
	}

	//	点数情報送信
	void	GameParam::SendPoint( void )
	{
		//	加算分が０ならスキップ
		if ( pointInfo[myIndex].addPoint == 0 )	return;

		//	情報格納
		NET_POINT	netPoint;
		netPoint.id = myIndex;
		netPoint.point = pointInfo[myIndex].addPoint;

		//	送信
		send( ( LPSTR )&netPoint, sizeof( netPoint ) );

		//	加算情報リセット
		pointInfo[myIndex].addPoint = 0;
	}

	//	マッチング送信
	void	GameParam::SendMatching(void)
	{
		NET_MATCHING netMatching;
		netMatching.id = myIndex;
		netMatching.isComplete = gameManager->GetIsComplete();
		send((LPSTR)&netMatching, sizeof(netMatching));
	}

//----------------------------------------------------------------------------------------------
//	データ受信
//----------------------------------------------------------------------------------------------

	//	キャラ情報受信
	void	GameParam::ReceiveCharaInfo( const LPSTR& data )
	{
		NET_CHARA*	netChara = ( NET_CHARA* )data;
		SetPlayerParam( netChara->id, netChara->pos, netChara->angle, netChara->motion );
	}

	//	ゲーム情報受信
	void	GameParam::ReceiveGameInfo( const LPSTR& data )
	{
		NET_GAME*	gameInfo = ( NET_GAME* )data;
		gameManager->SetTimer( gameInfo->limitTimer );
	}

	//	点数情報受信
	void	GameParam::ReceivePoint( const LPSTR& data )
	{
		NET_POINT*	netPoint = ( NET_POINT* )data;
		SetPointInfo( netPoint->id, netPoint->point );
	}

	//	マッチング情報
	void	GameParam::ReceiveMatching(const LPSTR& data)
	{
		NET_MATCHING*	netMatching = (NET_MATCHING*)data;
		SetMachingInfo(netMatching->id, netMatching->isComplete);
	}

	//*****************************************
	//		後でちゃんとする

	//受け取り情報全部
	void	GameParam::ReceiveCharaDATA(const LPSTR& data)
	{
		//NET_CHAR_RECEIVEDATA* d = (NET_CHAR_RECEIVEDATA*)data;
		////playerParam[client].axis = d->axis;
		//float	length = sqrtf(d->axisX * d->axisX + d->axisY * d->axisY) * 0.001f;

		//////	入力があれば移動処理
		//if (length >= 0.3f)
		//{
		//	Vector3 m = Vector3(sinf(d->angle), 0.0f, cosf(d->angle)) * 0.5;
		//	playerParam[client].pos += m;
		//}
	}


	//*****************************************


	//	コントローラー情報受信
	void	GameParam::ReceiveControllerAxis( int client, const LPSTR& data )
	{
		NET_CONTROLLE_AXIS* d = (NET_CONTROLLE_AXIS*)data;
		//playerParam[client].axisX = d->axisX;
		//playerParam[client].axisY = d->axisY;
	}

	//	キャラ移動量情報受信
	void	GameParam::ReceiveCharaMove( const LPSTR& data )
	{
		NET_CHARA_MOVE* netChara = ( NET_CHARA_MOVE* )data;
		SetPlayerMove( netChara->id, netChara->move );
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

		playerManager->SetPlayer( id );
	}

	//	点数情報設定
	void	GameParam::SetPointInfo( int id, int point )
	{
		pointInfo[id].point = point;
	}

	//	マッチング情報
	void	GameParam::SetMachingInfo(int id, bool isComplete)
	{
		matchingInfo[id].isComplete = isComplete;
	}

	//	加算情報設定
	void	GameParam::AddPoint( int id, int addPoint )
	{
		pointInfo[id].addPoint += addPoint;
	}

	//	プレイヤー脱退
	void	GameParam::RemovePlayerInfo( int id )
	{
		playerInfo[id].active = false;
	}

	//	プレイヤーパラメータ設定
	void	GameParam::SetPlayerPos( int id, const Vector3& pos )
	{
		playerParam[id].pos = pos;
		playerParam[id].angle  = 0.0f;
	}

	//	プレイヤーパラメータ設定
	void	GameParam::SetPlayerParam( int id, const Vector3& pos, float angle, int motion )
	{
		playerParam[id].pos = pos;
		playerParam[id].angle = angle;
		playerParam[id].motion = motion;
	}

	void	GameParam::SetPlayerMove(int id, const Vector3& move)
	{
		//playerParam[id].move = move;
		playerParam[id].angle = 0.0f;
	}

	//	プレイヤーパラメータ設定
	void	GameParam::SetPlayerParam( int id, const PlayerParam& param )
	{
		playerParam[id].pos = param.pos;
		//playerParam[id].move = param.move;
		playerParam[id].angle  = param.angle;
	}

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

	//	スティック入力情報取得( 返り値に入力の長さ、引数に入力値をかえす )
	float	GameParam::GetStickInput( float& outX, float& outY )
	{
		outX = ( float )input[0]->Get( KEY_AXISX ) * 0.001f;
		outY = -( float )input[0]->Get( KEY_AXISY ) * 0.001f;

		return	Vector3( outX, 0.0f, outY ).Length();
	}

