
#include	"iextreme.h"
#include	"PlayerManager.h"

//*****************************************************************************************************************************
//
//	PlayerManagerクラス
//
//*****************************************************************************************************************************

//----------------------------------------------------------------------------------------------
//	グローバル
//----------------------------------------------------------------------------------------------

PlayerManager*	playerManager = nullptr;

//----------------------------------------------------------------------------------------------
//	初期化・解放
//----------------------------------------------------------------------------------------------

	//	コンストラクタ
	PlayerManager::PlayerManager( GameParam* gameParam )
	{
		this->gameParam = gameParam;

		//	全プレイヤー初期化
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			player[p] = nullptr;
		}
	}

	//	デストラクタ
	PlayerManager::~PlayerManager( void )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			if ( player[p] != nullptr )
			{
				delete	player[p];
				player[p] = nullptr;
			}
		}
	}

//----------------------------------------------------------------------------------------------
//	更新
//----------------------------------------------------------------------------------------------

	//	更新
	void	PlayerManager::Update( int id )
	{
		PlayerParam	param = gameParam->GetPlayerParam( id );

		//	プレイヤー更新
		if (  gameParam->GetPlayerActive( id ) == false )
		{
			ReleasePlayer( id );
		}
		else
		{
			//	更新・情報を反映
			player[id]->Update( param );
			gameParam->SetPlayerParam( id, param.pos, param.angle, param.motion );
			PosCheck( id );
		}
	}

//----------------------------------------------------------------------------------------------
//	動作関数
//----------------------------------------------------------------------------------------------

	//	座標チェック
	void	PlayerManager::PosCheck( int client )
	{
		for ( int p = 0; p < PLAYER_MAX; p++ )
		{
			//	自分VS自分は除外
			if ( p == client )	continue;
			if ( gameParam->GetPlayerActive( p ) == false )		continue;

			//	自分→相手へのベクトル
			Vector3	vec = gameParam->GetPlayerParam( client ).pos - gameParam->GetPlayerParam( p ).pos;
			float		length = vec.Length();

			float collisionDist = 3.0f;

			//	近い場合は離す
			if ( length < collisionDist )
			{
				//	ベクトル正規化
				vec.Normalize();

				//	離す
				gameParam->GetPlayerParam( p ).pos = 
					( gameParam->GetPlayerParam( client ).pos - vec * collisionDist );
			}
		}
	}

//----------------------------------------------------------------------------------------------
//	情報設定
//----------------------------------------------------------------------------------------------

	//	プレイヤー設定
	void	PlayerManager::SetPlayer( int id )
	{
		//	存在チェック
		if ( player[id] != nullptr )	return;

		//	プレイヤー生成
		player[id] = new Player( id );
	}

	//	プレイヤー解放
	void	PlayerManager::ReleasePlayer( int id )
	{
		if ( player[id] != nullptr )
		{
			delete	player[id];
			player[id] = nullptr;
		}
	}

//----------------------------------------------------------------------------------------------
//	情報取得
//----------------------------------------------------------------------------------------------

	//	座標取得
	Vector3	PlayerManager::GetPos( int id )
	{
		return	Vector3( 0.0f, 0.0f, 0.0f );
	}

	//	プレイヤー取得
	Player*&	PlayerManager::GetPlayer( int id )
	{
		return	player[id];
	}
