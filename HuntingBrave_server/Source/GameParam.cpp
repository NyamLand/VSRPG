
#include	"iextreme.h"
#include	"GameManager.h"
#include	"PlayerManager.h"
#include	"InputManager.h"
#include	<thread>
#include	"GameParam.h"

//*****************************************************************************************************************************
//
//		ゲームデータ管理
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

#define	INIT_LIFE		7
GameParam*	gameParam = nullptr;

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	GameParam::GameParam( void )
	{
		for( int id = 0 ; id < PLAYER_MAX ; id++ )
		{
			ZeroMemory( &playerInfo[id], sizeof( PlayerInfo ) );
			ZeroMemory( &playerParam[id], sizeof( PlayerParam ) );
			ZeroMemory( &pointInfo[id], sizeof( PointInfo ) );
			ZeroMemory( &lifeInfo[id], sizeof( LifeInfo ) );
			ZeroMemory( &matchingInfo[id], sizeof( MatchingInfo ) );
			lifeInfo[id].Initialize( INIT_LIFE );
		}
	}

	//	サーバー初期化
	bool GameParam::InitializeServer( void )
	{
		//	WinSock初期化
		WSADATA	wsaData;
		WSAStartup( MAKEWORD( 1, 1 ), &wsaData );
		bool successInit = Initialize( 7000 );

		if ( successInit )	printf( "サーバー初期化成功\n" );
		return successInit;
	}

//----------------------------------------------------------------------------------------------
//	データ送受信
//----------------------------------------------------------------------------------------------

	//	送信
	int	GameParam::Send( int client )
	{
		if( client == -1 ) return -1;

		//	全データ送信
		for ( int clientNum = 0; clientNum < PLAYER_MAX; clientNum++ )
		{
			//	アクティブでないプレイヤーはとばす
			if ( playerInfo[clientNum].active == false ) continue;

			//	移動情報送信
			SendCharaInfo( client, clientNum );
		}
		
		//	ゲーム情報送信
		SendGameInfo( client );

		//	終端通知
		char end = -1;
		send( client, &end, 1 );
		return client;
	}

	//	受信
	int	GameParam::Receive( void )
	{
		char	data[256];
		int	size = sizeof( data );
		int	client = receive( data, &size );
		if( client == -1 ) return -1;
		
		switch( data[COMMAND] )
		{
		case RECEIVE_COMMAND::PLAYER_INFO:		//	パラメータ情報
			client = ReceiveChara( client, data );
			break;

		case RECEIVE_COMMAND::ATTACK_INFO:		//	攻撃情報
			client = ReceiveAttackInfo( client , data );
			break;

		case RECEIVE_COMMAND::POINT_INFO:		//	点数情報
			client = ReceivePoint( client, data );
			break;

		case RECEIVE_COMMAND::INPUT_INFO:	//	入力情報
			client = ReceiveInput( client, data );
			break;

		case COMMANDS::MATCHING:	//	マッチング
			client = ReceiveMatching( client, data );
			break;

		case COMMANDS::SIGN_UP:	//	新規参入
			client = ReceiveSignUp( client, data );
			break;

		case COMMANDS::SIGN_OUT:	//	脱退
			client = ReceiveSignOut( client, data );
			break;
		}

		return client;
	}

//----------------------------------------------------------------------------------------------
//	送信処理
//----------------------------------------------------------------------------------------------

	//	キャラ情報送信
	void	GameParam::SendCharaInfo( int client, int player )
	{
		//	情報設定
		SendCharaData sendCharaData( player, 
			attackInfo[player].attackParam,
			playerParam[player].pos, 
			playerParam[player].angle,
			playerParam[player].motion,
			lifeInfo[player].life );

		//	送信
		send( client, ( LPSTR )&sendCharaData, sizeof( sendCharaData ) );
	}

	//	ゲーム情報送信
	void	GameParam::SendGameInfo( int client )
	{
		//	情報設定
		SendGameData	 sendGameData( gameManager->GetTimer()->GetLimitTime() ); 

		//	送信
		send( client, ( LPSTR )&sendGameData, sizeof( sendGameData ) );
	}

	//	点数情報送信
	void	GameParam::SendPointInfo( int client, int player )
	{
		//	情報設定
		SendPointData	sendPointData( player, pointInfo[player].point );
		
		//	送信
		send( client, ( char* )&sendPointData, sizeof( sendPointData ) );
	}

	//	マッチング情報送信
	void	GameParam::SendMatchingInfo( int client, int player )
	{
		//	情報設定
		Matching	matching( player, matchingInfo[player].isComplete );

		//	送信
		send( client, ( char* )&matching, sizeof( matching ) );
	}

	//	魔法情報送信
	void	GameParam::SendMagicInfo( int client, int index, const Vector3& pos )
	{
		SendMagicData		sendMagicData( index, pos );
		send( client, ( LPSTR )&sendMagicData, sizeof( sendMagicData ) );
	}

	//	魔法追加情報送信
	void	GameParam::SendMagicAppendInfo( int client, int id, const Vector3& pos )
	{
		SendMagicAppend sendMagicAppend( id, pos );
		send( client, ( LPSTR )&sendMagicAppend, sizeof( sendMagicAppend ) );
	}

	//	魔法消去情報送信
	void	GameParam::SendMagicEraseInfo( int client, int index )
	{
		SendMagicErase	sendMagicErase( index );
		send( client, ( LPSTR )&sendMagicErase, sizeof( sendMagicErase ) );
	}

//----------------------------------------------------------------------------------------------
//	受信処理
//----------------------------------------------------------------------------------------------

	//	キャラ情報受信
	int	GameParam::ReceiveChara( int client, const LPSTR& data )
	{
		ReceivePlayerData* receivePlayerData = ( ReceivePlayerData* )data;
		
		//	スティックの入力情報設定
		inputManager->SetAxis( client, receivePlayerData->axisX,	receivePlayerData->axisY );

		//	フレーム情報設定
		playerParam[client].frame = receivePlayerData->frame;

		return	client;
	}

	//	点数情報受信
	int	GameParam::ReceivePoint( int client, const LPSTR& data )
	{
		ReceivePointData*	receivePointData = ( ReceivePointData* )data;
		pointInfo[client].point += receivePointData->addPoint;
		
		//	全プレイヤーに送信
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			SendPointInfo( client, p );
		}

		return	-1;
	}

	//	攻撃情報受信
	int	GameParam::ReceiveAttackInfo( int client, const LPSTR& data )
	{
		ReceiveAttackData*	receiveAttackData = ( ReceiveAttackData* )data;
		switch ( receiveAttackData->shape )
		{
		case SHAPE_TYPE::SPHERE:
			attackInfo[client].collisionShape.SetSphere(
				Sphere(	receiveAttackData->attackPos1,
								receiveAttackData->radius ) );
			attackInfo[client].collisionShape.shapeType = SHAPE_TYPE::SPHERE;
			break;

		case SHAPE_TYPE::CAPSULE:
			attackInfo[client].collisionShape.SetCapsule( 
				Capsule( 	receiveAttackData->attackPos1, 
								receiveAttackData->attackPos2,
								receiveAttackData->radius ) );
			attackInfo[client].collisionShape.shapeType = SHAPE_TYPE::CAPSULE;
			break;
		}
		attackInfo[client].power = 1;
		return	-1;
	}

	//	入力情報取得
	int	GameParam::ReceiveInput( int client, const LPSTR& data )
	{
		ReceiveInputData*	receiveInputData = ( ReceiveInputData* )data;

		//	ボタンの入力情報設定
		inputManager->SetInput( client, 
			receiveInputData->keyType, receiveInputData->keyState );

		return	-1;
	}

	//	サインアップ情報受信
	int	GameParam::ReceiveSignUp( int client, const LPSTR& data )
	{
		//	名前保存
		SignUp* signUp = ( SignUp* )data;
		SetPlayer( client, signUp->name );

		//	IDを返信
		signUp->id = client;
		send( client, ( char* )signUp, sizeof( SignUp ) );

		//	初期座標を送信
		PlayerParam	initParam = gameManager->GetInitInfo( client );
		SendCharaData	sendCharaData( client, 
			AttackInfo::NO_ATTACK,
			initParam.pos, initParam.angle, initParam.motion, 
			lifeInfo[client].life );
		send( client, ( LPSTR )&sendCharaData, sizeof( sendCharaData ) );

		//	全員にデータ送信
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( playerInfo[p].active == false ) continue;
			send( p, ( char* )signUp, sizeof( SignUp ) );
		}

		//	全データ送信
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( playerInfo[p].active == false ) continue;
			signUp->id = p;
			strcpy( signUp->name, playerInfo[p].name );
			send( client, ( char* )signUp, sizeof( SignUp ) );
		}
		printf( "%dP %sさんが参加しました。\n", client + 1, signUp->name );

		return	client;
	}

	//	サインアウト情報受信
	int	GameParam::ReceiveSignOut( int client, const LPSTR& data )
	{
		//	プレイヤー解放
		ReleasePlayer( client );

		SignOut	signOut( client );

		//	ソケットを閉じる
		CloseClient( client );

		//	全員にデータ送信
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( playerInfo[p].active == false ) continue;
			send( p, ( char* )&signOut, sizeof( SignOut ) );
		}
		printf( "%dP %sさんが脱退しました。\n", client + 1, playerInfo[client].name );

		return	client;
	}

	//	マッチング情報受信
	int	GameParam::ReceiveMatching( int client, const LPSTR& data )
	{
		Matching*	matching = ( Matching* )data;
		matchingInfo[client].isComplete = matching->isComplete;

		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	アクティブでないプレイヤーはとばす
			if ( playerInfo[p].active == false ) continue;
			SendMatchingInfo( client, p );
		}

		return	-1;
	}

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

	//	プレイヤー情報設定
	void	GameParam::SetPlayer( int id, char* name )
	{
		//	プレイヤー情報設定
		playerInfo[id].active = true;
		strcpy( playerInfo[id].name, name );

		//	パラメータ初期化
		playerParam[id] = gameManager->GetInitInfo( id );
		playerManager->SetPlayer( id );
	}

	//	プレイヤー解放
	void	GameParam::ReleasePlayer( int id )
	{
		ZeroMemory( &playerInfo[id], sizeof( PlayerInfo ) );
		//playerManager->ReleasePlayer( id );
	}

	//	プレイヤーパラメータ設定
	void	GameParam::SetPlayerParam( int id, const Vector3& pos, float angle, int motion )
	{
		playerParam[id].pos    = pos;
		playerParam[id].angle  = angle;
		playerParam[id].motion = motion;
	}

	//	プレイヤーパラメータ設定
	void	GameParam::SetPlayerParam( int id, const PlayerParam& param )
	{
		playerParam[id].pos    = param.pos;
		playerParam[id].angle  = param.angle;
	}

	//	点数情報設定
	void	GameParam::SetPointInfo( int id, const PointInfo& pointInfo )
	{
		this->pointInfo[id] = pointInfo;
	}

