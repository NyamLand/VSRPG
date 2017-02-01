
#include	"iextreme.h"
#include	"system/Framework.h"
#include	<thread>
#include	<vector>
#include	"GlobalFunction.h"
#include	"Random.h"
#include	"Camera.h"
#include	"GameData.h"
#include	"GameManager.h"
#include	"PlayerManager.h"
#include	"InputManager.h"
#include	"MagicManager.h"
#include	"LevelManager.h"
#include	"PointManager.h"
#include	"NetEnemyManager.h"
#include	"UIManager.h"
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

namespace SE_TYPE
{
	enum 
	{
		ATTACK_SE,
		MAGIC_SE,
	};
}

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	GameParam::GameParam( void ) : playerName( nullptr ),
		myIndex( -1 ), inputAcceptance( true ), deathFlag( false )
	{
		//	プレイヤーデータ初期化
		for ( int id = 0; id < PLAYER_MAX; id++ )
		{
			ZeroMemory( &playerInfo[id], sizeof( PlayerInfo ) );
			ZeroMemory( &playerParam[id], sizeof( PlayerParam ) );
			ZeroMemory( &playerParam[id], sizeof( PlayerStatus ) );
			ZeroMemory( &matchingInfo[id], sizeof( MatchingInfo ) );
		}

		//	プレイヤー名初期化
		playerName = new PlayerName();
		playerName->Initialize();
	}

	//	デストラクタ
	GameParam::~GameParam( void )
	{
		SafeDelete( playerName );
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
			ZeroMemory( &matchingInfo[id], sizeof( MatchingInfo ) );
		}
		ZeroMemory( &playerStatus, sizeof( PlayerStatus ) );

		return	true;
	}
	
	//	クライアント初期化
	bool	GameParam::InitializeClient( char* addr, int nPort, int* name )
	{
		//	初期化
		Initialize();

		//	クライアント初期化
		InitializeUDP( nPort, addr );

		//	タイプと名前の送信
		char frontTitle = ( char )random->GetInt( 0, 19 );
		char backTitle = ( char )random->GetInt( 0, 9 );
		SignUp signUp( -1, name, frontTitle, backTitle );
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

		//	初期パラメータ受信
		char	data[30];
		if ( receive( data, sizeof( data ) ) <= 0 )	return	false;
		levelManager->Receive( data );

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

	//	データ送信
	void	GameParam::Send( void )
	{
		//	キャラクター情報送信
		SendPlayerInfo();

		//	入力情報送信
		SendInputInfo();

		//	debug用
		//if (KEY(KEY_TYPE::SELECT) == 3){
		//	char debug = COMMANDS::DEBUG;
		//	send(&debug, 1);
		//}
	}

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
				pointManager->Receive( data );
				break;

			case RECEIVE_COMMAND::CHARA_INFO:
				ReceiveCharaInfo( data );
				break;

			case RECEIVE_COMMAND::MAGIC_INFO:
				magicManager->Receive( data );
				break;

			case RECEIVE_COMMAND::CLASS_CHANGE_INFO:
				playerManager->Receive( data );
				break;

			case RECEIVE_COMMAND::STATUS_INFO:
				levelManager->Receive( data );
				break;

			case RECEIVE_COMMAND::ENEMY_INFO:
				//netEnemyManager->Receive( data );
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
		float axisX, axisY;
		axisX = axisY = 0.0f;
		inputManager->GetStickInputLeft( axisX, axisY );

		//	フレーム情報取得
		int frame = 0;
		if ( playerManager->GetPlayer( myIndex ) != nullptr )
		{
			frame =playerManager->GetPlayer( myIndex )->GetFrame();
		}

		//	カメラ方向設定
		Vector3	vEye( mainView->GetTarget() - mainView->GetPos() );
		float	cameraAngle = atan2f( vEye.x, vEye.z );

		//	送信
		SendPlayerData	sendPlayerData( axisX, axisY, cameraAngle, frame );
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

		//	メニューボタン入力
		CheckInputData( KEY_TYPE::START );
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

		if ( receiveCharaData->id == myIndex )
		{
			if ( !deathFlag )
			{
				if ( receiveCharaData->motion == MOTION_NUM::FALL )
				{
					sound->MuteVolume( BGM::MAIN );
				}

				if ( receiveCharaData->motion == MOTION_NUM::DEAD )
				{
					deathFlag = true;
					sound->PlayBGM( BGM::DEAD );
				}
			}
			else
			{
				if ( receiveCharaData->motion != MOTION_NUM::DEAD )
				{
					sound->MuteVolume( BGM::DEAD );
					sound->ResetVolume( BGM::MAIN );
					deathFlag = false;
				}
			}
		}

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
		playerName->SetName( signUp->id, signUp->name );
		LPSTR name = playerName->GetName( signUp->id );
		SetPlayerInfo( signUp->id, name, signUp->frontTitle, signUp->backTitle );
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

		case RESPONSE_COMMAND::KILL_INFO:
			{
				KillInfo*	killInfo = ( KillInfo* )data;
				uiManager->SetKillLog( killInfo->killer, killInfo->dead );
			}
			break;
			
		case RESPONSE_COMMAND::HIT_SE_TYPE:
			{
				switch ( data[2] )
				{
				case SE_TYPE::ATTACK_SE:
					sound->PlaySE( SE::ATTACK_HIT1 );
					break;

				case SE_TYPE::MAGIC_SE:
					sound->PlaySE( SE::MAGIC_HIT );
					break;
				}
			}
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
	void	GameParam::SetPlayerInfo( int id, char* name, char frontTitle, char backTitle )
	{
		playerInfo[id].active = true;
		strcpy( playerInfo[id].name, name );
		playerInfo[id].frontTitle = frontTitle;
		playerInfo[id].backTitle = backTitle;
	}

	//	マッチング情報設定
	void	GameParam::SetMatchingInfo( int id, bool isComplete )
	{
		matchingInfo[id].isComplete = isComplete;
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
