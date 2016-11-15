
#include	"iextreme.h"
#include	"GameData.h"
#include	"GameManager.h"
#include	"PlayerManager.h"
#include	"InputManager.h"
#include	"GameParam.h"

//***************************************************************
//
//	GameParamクラス
//
//***************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

GameParam*	gameParam = nullptr;

//	入力情報
#define	MIN_INPUT_STICK		0.3f

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
			ZeroMemory( &pointInfo[id], sizeof( PointInfo ) );
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
		SignUp signUp( -1, name );
		send( ( char* )&signUp, sizeof( signUp ) );

		//	個人ID取得
		if( receive( ( char* )&signUp, sizeof( signUp ) ) <= 0 ) return false;
		myIndex = signUp.id;

		//	初期座標取得
		ReceiveCharaData	receiveCharaData;
		if ( receive( ( LPSTR )&receiveCharaData, sizeof( receiveCharaData ) ) <= 0 )	return	false;
		SetPlayerParam( myIndex, receiveCharaData.pos, receiveCharaData.angle, receiveCharaData.motion );
		return true;
	}

	//	脱退
	void	GameParam::CloseClient( void )
	{
		//	脱退メッセージ送信
		SignOut	signOut( myIndex );
		send( ( LPSTR )&signOut, sizeof( SignOut ) );
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
			if( data[COMMAND] == RECEIVE_COMMAND::NO_COMMAND ) break;

			//	先頭バイト（コマンド）による処理分岐
			switch( data[COMMAND] )
			{
			case RECEIVE_COMMAND::CHARA_INFO:	//	移動情報
				ReceiveCharaInfo( data );
				break;

			case RECEIVE_COMMAND::GAME_INFO:	//	ゲーム情報
				ReceiveGameInfo( data );
				break;

			case RECEIVE_COMMAND::POINT_INFO:	//	点数情報
				ReceivePointInfo( data );
				break;

			case COMMANDS::SIGN_UP:		//	参加情報
				ReceiveSignUpInfo( data );
				break;

			case COMMANDS::SIGN_OUT:		//	脱退情報
				ReceiveSignOutInfo( data );
				break;
			}
		}
	}

	//	データ送信
	void	GameParam::Update( void )
	{
		//	全データ受信
		Receive();

		//	キャラクター情報送信
		SendPlayerInfo();

		//	入力データ送信
		SendInputInfo();

		//	点数データ送信
		SendPointInfo();
	}

//----------------------------------------------------------------------------------------------
//	データ送信
//----------------------------------------------------------------------------------------------

	//	情報送信
	void	GameParam::SendPlayerInfo( void )
	{
		//	スティック入力情報取得
		float axisX = 0.0f, axisY = 0.0f;
		GetStickInput( axisX, axisY );

		//	フレーム情報取得
		int	frame = playerManager->GetPlayer( myIndex )->GetFrame();

		//	送信情報設定
		SendPlayerData	sendPlayerData( 
			myIndex, axisX, axisY, frame );

		send( ( LPSTR )&sendPlayerData, sizeof( SendPlayerData ) );
	}

	//	入力情報送信
	void	GameParam::SendInputInfo( void )
	{
		//	入力情報取得
		int		inputType = 0;
		int		buttonType = inputManager->GetInput( inputType );
		
		//	入力がある時だけ送信
		if ( inputType == InputManager::NO_INPUT )		return;
		
		//	送信情報設定
		SendInputData	sendInputData( 
			myIndex, buttonType, inputType );

		//	送信
		send( ( LPSTR )&sendInputData, sizeof( SendInputData ) );
	}

	//	点数情報送信
	void	GameParam::SendPointInfo( void )
	{
		//	加算分が０ならスキップ
		if ( pointInfo[myIndex].addPoint == 0 )	return;

		//	情報格納
		SendPointData	sendPointData(
			myIndex,
			pointInfo[myIndex].addPoint );

		//	送信
		send( ( LPSTR )&sendPointData, sizeof( sendPointData ) );

		//	加算情報リセット
		pointInfo[myIndex].addPoint = 0;
	}

//----------------------------------------------------------------------------------------------
//	データ受信
//----------------------------------------------------------------------------------------------

	//	キャラ情報受信
	void	GameParam::ReceiveCharaInfo( const LPSTR& data )
	{
		ReceiveCharaData*	receiveCharaData = ( ReceiveCharaData* )data;
		SetPlayerParam( 
			receiveCharaData->id, 
			receiveCharaData->pos, 
			receiveCharaData->angle, 
			receiveCharaData->motion );
	}

	//	ゲーム情報受信
	void	GameParam::ReceiveGameInfo( const LPSTR& data )
	{
		ReceiveGameData*	receiveGameData = ( ReceiveGameData* )data;
		gameManager->SetTimer( receiveGameData->limitTimer );
	}

	//	点数情報受信
	void	GameParam::ReceivePointInfo( const LPSTR& data )
	{
		ReceivePointData*	receivePointData = ( ReceivePointData* )data;
		SetPointInfo( receivePointData->id, receivePointData->point );
	}

	//	サインアップ情報受信
	void	GameParam::ReceiveSignUpInfo( const LPSTR& data )
	{
		SignUp*	signUp = ( SignUp* )data;
		SetPlayerInfo( signUp->id, signUp->name );
	}

	//	サインアウト情報受信
	void	GameParam::ReceiveSignOutInfo( const LPSTR& data )
	{
		SignOut*	signOut = ( SignOut* )data;

		RemovePlayerInfo( signOut->id ); 
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
	void	GameParam::SetPlayerParam( int id, const Vector3& pos, float angle, int motion )
	{
		playerParam[id].pos = pos;
		playerParam[id].angle = angle;
		playerParam[id].motion = motion;
	}

	//	プレイヤーパラメータ設定
	void	GameParam::SetPlayerParam( int id, const PlayerParam& param )
	{
		playerParam[id].pos = param.pos;
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

