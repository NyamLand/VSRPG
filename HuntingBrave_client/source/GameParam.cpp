
#include	"iextreme.h"
#include	"GameData.h"
#include	"GameManager.h"
#include	"PlayerManager.h"
#include	"InputManager.h"
#include	<thread>
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
	GameParam::GameParam( void ) : myIndex( -1 ), inputAcceptance( true )
	{
		//	プレイヤーデータ初期化
		for ( int id = 0; id < PLAYER_MAX; id++ )
		{
			ZeroMemory( &playerInfo[id], sizeof( PlayerInfo ) );
			ZeroMemory( &playerParam[id], sizeof( PlayerParam ) );
			ZeroMemory( &pointInfo[id], sizeof( PointInfo ) );
			ZeroMemory( &matchingInfo[id], sizeof( MatchingInfo ) );
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
		SetPlayerParam( myIndex, 
			receiveCharaData.pos, receiveCharaData.angle, 
			receiveCharaData.motion, receiveCharaData.life );
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

			case COMMANDS::MATCHING:
				ReceiveMatching( data );
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

		//	点数データ送信
		SendPointInfo();

		//	攻撃データ送信
		SendAttackParam();

		//	マッチング情報送信
		SendMatching();

		//	入力情報送信
		SendInputInfo();
	}

//----------------------------------------------------------------------------------------------
//	データ送信
//----------------------------------------------------------------------------------------------

	//	情報送信
	void	GameParam::SendPlayerInfo( void )
	{
		//	スティック入力情報取得
		float axisX = 0.0f, axisY = 0.0f;
		inputManager->GetStickInputLeft( axisX, axisY );

		//	フレーム情報取得
		int	frame = playerManager->GetPlayer( myIndex )->GetFrame();

		//	送信情報設定
		SendPlayerData	sendPlayerData( axisX, axisY, frame  );

		send( ( LPSTR )&sendPlayerData, sizeof( sendPlayerData ) );
	}

	//	点数情報送信
	void	GameParam::SendPointInfo( void )
	{
		//	加算分が０ならスキップ
		if ( pointInfo[myIndex].addPoint == 0 )	return;

		//	情報格納
		SendPointData	sendPointData( pointInfo[myIndex].addPoint );

		//	送信
		send( ( LPSTR )&sendPointData, sizeof( sendPointData ) );

		//	加算情報リセット
		pointInfo[myIndex].addPoint = 0;
	}

	//	攻撃情報送信
	void	GameParam::SendAttackParam( void )
	{
		//	情報設定
		AttackInfo	atkInfo = attackInfo[myIndex];
		SendAttackData	sendAttackData( atkInfo.pos1, atkInfo.pos2, atkInfo.radius );

		//	送信
		send( ( LPSTR )&sendAttackData, sizeof( sendAttackData ) );
	}

	//	マッチング状態送信
	void	GameParam::SendMatching( void )
	{
		Matching	matching;
		matching.id = myIndex;
		matching.isComplete = gameManager->GetIsComplete();
		send( ( LPSTR )&matching, sizeof( matching ) );
	}

	//	入力情報送信
	void	GameParam::SendInputInfo( void )
	{
		//	剣攻撃ボタン状態送信
		CheckInputData( KEY_TYPE::B );
		
		//	魔法攻撃ボタン状態送信
		CheckInputData( KEY_TYPE::A );

		//	
	}

//----------------------------------------------------------------------------------------------
//	データ受信
//----------------------------------------------------------------------------------------------

	//	キャラ情報受信
	void	GameParam::ReceiveCharaInfo( const LPSTR& data )
	{
		//	受信情報
		ReceiveCharaData*	receiveCharaData = ( ReceiveCharaData* )data;

		//	情報設定
		attackInfo[receiveCharaData->id].attackParam = 
			receiveCharaData->attackParam;

		SetPlayerParam( 
			receiveCharaData->id, 
			receiveCharaData->pos, 
			receiveCharaData->angle, 
			receiveCharaData->motion,
			receiveCharaData->life );
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

	//	マッチング情報
	void	GameParam::ReceiveMatching( const LPSTR& data )
	{
		Matching*	matching = ( Matching* )data;
		SetMatchingInfo( matching->id, matching->isComplete );
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
//	動作関数
//----------------------------------------------------------------------------------------------

	//	入力チェック＆送信
	void	GameParam::CheckInputData( int key )
	{
		//	入力チェック
		int inputType = KEY( key );
		if ( inputType == 0 )	return; 

		//	送信
		SendInputData		sendInputData( key, inputType );
		send( ( LPSTR )&sendInputData, sizeof( sendInputData ) );
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

	//	マッチング情報設定
	void	GameParam::SetMatchingInfo( int id, bool isComplete )
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
	void	GameParam::SetPlayerParam( int id, const Vector3& pos, float angle, int motion, int life )
	{
		playerParam[id].pos = pos;
		playerParam[id].angle = angle;
		playerParam[id].motion = motion;
		playerParam[id].life = life;
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
