
#include	"iextreme.h"
#include	"system/Framework.h"
#include	<thread>
#include	"GameData.h"
#include	"GameManager.h"
#include	"PlayerManager.h"
#include	"InputManager.h"
#include	"MagicManager.h"
#include	"LevelManager.h"
#include	"Sound.h"
#include	"sceneTitle.h"
#include	"sceneMatching.h"
#include	"sceneMain.h"
#include	"sceneResult.h"
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

		//	関数ポインタ
		ReceiveFunction[RECEIVE_COMMAND::GAME_INFO] = &GameParam::ReceiveGameInfo;
		ReceiveFunction[RECEIVE_COMMAND::POINT_INFO] = &GameParam::ReceivePointInfo;
		ReceiveFunction[RECEIVE_COMMAND::CHARA_INFO] = &GameParam::ReceiveCharaInfo;
		ReceiveFunction[RECEIVE_COMMAND::MAGIC_INFO] = &GameParam::ReceiveMagicInfo;
		ReceiveFunction[RECEIVE_COMMAND::MAGIC_APPEND] = &GameParam::ReceiveMagicAppendInfo;
		ReceiveFunction[RECEIVE_COMMAND::MAGIC_ERASE] = &GameParam::ReceiveMagicEraseInfo;
		ReceiveFunction[RECEIVE_COMMAND::LEVEL_INFO] = &GameParam::ReceiveLevelInfo;
		ReceiveFunction[RECEIVE_COMMAND::EXP_INFO] = &GameParam::ReceiveExpInfo;
	}

	//	デストラクタ
	GameParam::~GameParam( void )
	{
		CloseClient();
	}

	//	初期化
	bool	GameParam::Initialize( void )
	{
		//	プレイヤーデータ初期化
		for ( int id = 0; id < PLAYER_MAX; id++ )
		{
			ZeroMemory( &playerInfo[id], sizeof( PlayerInfo ) );
			ZeroMemory( &playerParam[id], sizeof( PlayerParam ) );
			ZeroMemory( &pointInfo[id], sizeof( PointInfo ) );
			ZeroMemory( &matchingInfo[id], sizeof( MatchingInfo ) );
		}

		return	true;
	}
	
	//	クライアント初期化
	bool	GameParam::InitializeClient( char* addr, int nPort, char* name )
	{
		//	初期化
		Initialize();

		//	クライアント初期化
		InitializeUDP( nPort, addr );

		//	タイプと名前の送信
		SignUp signUp( -1, name );
		send( ( char* )&signUp, sizeof( signUp ) );

		//	個人ID取得
		if( receive( ( char* )&signUp, sizeof( signUp ) ) <= 0 ) return false;
		myIndex = signUp.id;

		//	返答
		Response	response( RESPONSE_COMMAND::SIGN_UP );
		send( ( LPSTR )&response, sizeof( response ) );

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
			case RECEIVE_COMMAND::GAME_INFO:
				ReceiveGameInfo( data );
				break;

			case RECEIVE_COMMAND::POINT_INFO:
				ReceivePointInfo( data );
				break;

			case RECEIVE_COMMAND::CHARA_INFO:
				ReceiveCharaInfo( data );
				break;

			case RECEIVE_COMMAND::MAGIC_INFO:
				ReceiveMagicInfo( data );
				break;

			case RECEIVE_COMMAND::MAGIC_APPEND:
				ReceiveMagicAppendInfo( data );
				break;

			case RECEIVE_COMMAND::MAGIC_ERASE:
				ReceiveMagicEraseInfo( data );
				break;

			case RECEIVE_COMMAND::LEVEL_INFO:
				ReceiveLevelInfo( data );
				break;

			case RECEIVE_COMMAND::EXP_INFO:
				ReceiveExpInfo( data );
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

			case COMMANDS::RESPONSE:
				ReceiveResponse( data );
				break;

			default:
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

		//	入力情報送信
		SendInputInfo();
	}

//----------------------------------------------------------------------------------------------
//	データ送信
//----------------------------------------------------------------------------------------------

	//	プレイヤー情報送信
	void	GameParam::SendPlayerInfo( void )
	{
		//	スティック入力情報取得
		float axisX = 0.0f, axisY = 0.0f;
		inputManager->GetStickInputLeft( axisX, axisY );

		//	フレーム情報取得
		int	frame = 0;
		if ( playerManager->GetPlayer( myIndex ) != nullptr )
		{
			frame = playerManager->GetPlayer( myIndex )->GetFrame();
		}

		//	送信
		SendPlayerData	sendPlayerData( axisX, axisY, frame  );
		send( ( LPSTR )&sendPlayerData, sizeof( sendPlayerData ) );
	}

	//	攻撃情報送信
	void	GameParam::SendAttackParam( void )
	{
		//	情報設定
		AttackInfo	atkInfo = attackInfo[myIndex];
		SendAttackData	sendAttackData( atkInfo.shape, atkInfo.radius, atkInfo.vec1, atkInfo.vec2 );

		//	送信
		send( ( LPSTR )&sendAttackData, sizeof( sendAttackData ) );
	}

	//	マッチング状態送信
	void	GameParam::SendMatching( void )
	{
		Matching	matching( myIndex, true );
		send( ( LPSTR )&matching, sizeof( matching ) );
	}

	//	入力情報送信
	void	GameParam::SendInputInfo( void )
	{
		//	回避ボタン入力
		CheckInputData( KEY_TYPE::A );

		//	剣攻撃ボタン入力
		CheckInputData( KEY_TYPE::B );
		
		//	魔法攻撃ボタン入力
		CheckInputData( KEY_TYPE::X );

		//	Yボタン入力
		CheckInputData( KEY_TYPE::Y );
	}

	//	討伐情報送信
	void	GameParam::SendHuntInfo( char enemyType )
	{
		SendHuntData	sendHuntData( enemyType );
		send( ( LPSTR )&sendHuntData, sizeof( sendHuntData ) );
	}

	//	サインアウト送信
	void	GameParam::SendSignOut( void )
	{

	}

	//	応答コマンド送信
	void	GameParam::SendResponseInfo( char com )
	{
		Response		response( com );
		send( ( LPSTR )&response, sizeof( response ) );
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
	
	//	魔法情報受信
	void	GameParam::ReceiveMagicInfo( const LPSTR& data )
	{
		ReceiveMagicData	* receiveMagicData = ( ReceiveMagicData* )data;
		magicManager->SetPos( receiveMagicData->index, receiveMagicData->pos );
	}

	//	魔法追加情報受信
	void	GameParam::ReceiveMagicAppendInfo( const LPSTR& data )
	{
		ReceiveMagicAppend*	receiveMagicAppend = ( ReceiveMagicAppend* )data;
		magicManager->Append( 
			receiveMagicAppend->id,
			receiveMagicAppend->pos, 
			receiveMagicAppend->angle );
	}

	//	魔法消去情報受信
	void	GameParam::ReceiveMagicEraseInfo( const LPSTR& data )
	{
		ReceiveMagicErase*	receiveMagicErase = ( ReceiveMagicErase* )data;
		magicManager->Erase( receiveMagicErase->index );
	}

	//	レベル情報受信
	void	GameParam::ReceiveLevelInfo( const LPSTR& data )
	{
		ReceiveLevelData* receiveLevelData = ( ReceiveLevelData* )data;
		levelManager->SetLevelInfo( receiveLevelData->levelType, receiveLevelData->level );
	}

	//	経験値情報受信
	void	GameParam::ReceiveExpInfo( const LPSTR& data )
	{
		ReceiveExpData*	receiveExpdata = ( ReceiveExpData* )data;
		levelManager->SetExp( receiveExpdata->exp );
	}

//----------------------------------------------------------------------------------------------
//	ログイン関連受信
//----------------------------------------------------------------------------------------------

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
		sound->PlaySE( SE::JOIN );
	}

	//	サインアウト情報受信
	void	GameParam::ReceiveSignOutInfo( const LPSTR& data )
	{
		SignOut*	signOut = ( SignOut* )data;

		RemovePlayerInfo( signOut->id ); 
	}

	//	返答情報受信
	void	GameParam::ReceiveResponse( const LPSTR& data )
	{
		Response*	response = ( Response* )data;

		switch ( response->responseCom )
		{
		case	RESPONSE_COMMAND::SIGN_UP:
			break;

		case RESPONSE_COMMAND::CHANGE_SCENE:
			gameManager->SetChangeSceneFrag( true );
			break;

		case RESPONSE_COMMAND::GAME_START:
			break;
		}
	}

//----------------------------------------------------------------------------------------------
//	動作関数
//----------------------------------------------------------------------------------------------

	//	キー情報チェック
	void	GameParam::CheckInputData( char keyType )
	{
		char keyState = ( char )KEY( keyType );
		if ( keyState == KEY_STATE::STAY || 
			keyState == KEY_STATE::NO_INPUT )	return;

		//	送信
		SendInputData	sendInputData( keyType, keyState );
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
