
#include	"iextreme.h"
#include	<vector>
#include	"Random.h"
#include	"GameData.h"
#include	"GlobalFunction.h"
#include	"GameParam.h"
#include	"PlayerManager.h"
#include	"UIManager.h"
#include	"EnemyManager.h"

//***************************************************************
//
//	EnemyManagerクラス
//
//***************************************************************

//-------------------------------------------------------------------------------------
//	グローバル
//-------------------------------------------------------------------------------------

//	定数
#define	APPEND_INTERVAL		3
#define	ENEMY_MAX			5
#define APPEND_RADIUS		15.0f
#define APPEND_RADIUS_		220.0f		//自陣以外

#define	MOFFU_INIT_LIFE	10
#define	WOLF_INIT_LIFE		20
#define SHADOW_INIT_LIFE	30

#define	MOFFU_LIFE_UP_PARAM		25
#define	WOLF_LIFE_UP_PARAM		30
#define	SHADOW_LIFE_UP_PARAM	40


#define	TIMER_RESET	10.0f
#define	MINUTE	60


//-------------------------------------------------------------------------------------
//	初期化・解放
//-------------------------------------------------------------------------------------

	//	コンストラクタ
	EnemyManager::EnemyManager( void ):
		appendOK( true )
	{
		//リスト初期化
		enemylist.clear();

		//	オブジェクト初期化
		for ( int i = 0; i < ENEMY_TYPE::TYPE_MAX; i++ )
		{
			org[i] = nullptr;
		}
	}

	//	デストラクタ
	EnemyManager::~EnemyManager( void )
	{
		Release();
	}

	//	初期化
	bool	EnemyManager::Initialize( void )
	{
		//リスト初期化
		enemylist.clear();

		//	モデル読み込み
		Load();
		
		//	ライフ初期化
		lifeUpParam[ENEMY_TYPE::MOFFU] = MOFFU_INIT_LIFE;
		lifeUpParam[ENEMY_TYPE::WOLF] = WOLF_INIT_LIFE;
		lifeUpParam[ENEMY_TYPE::SHADOW] = SHADOW_INIT_LIFE;
		timer = new Timer();
		timer->Start( TIMER_RESET );
	
		return	true;
	}

	//	解放
	void	EnemyManager::Release( void )
	{
		for ( auto it = enemylist.begin(); it != enemylist.end(); )
		{
			it = enemylist.erase( it );
		}

		for ( int i = 0; i < ENEMY_TYPE::TYPE_MAX; i++ )
		{
			SafeDelete( org[i] );
		}

		SafeDelete( timer );
	}

	//	オブジェクト読み込み
	void	EnemyManager::Load( void )
	{
		org[ENEMY_TYPE::WOLF] = new iex3DObj( "DATA/CHR/Enemy/wolf/wolf.IEM" );
		org[ENEMY_TYPE::MOFFU] = new iex3DObj( "DATA/CHR/Enemy/mofumofu/moffu.IEM" );
		org[ENEMY_TYPE::SHADOW] = new iex3DObj("DATA/CHR/Enemy/shadow/shadow.IEM");
	}

//-------------------------------------------------------------------------------------
//	更新・描画
//-------------------------------------------------------------------------------------

	//	更新
	void	EnemyManager::Update( void )
	{
		if ( timer->Update() )
		{
			if ( ( int )gameManager->GetTime() % MINUTE == 0 )
			{
				LifeUP();
			}
		}

		int		enemyNum = 0;

		for ( auto it = enemylist.begin(); it != enemylist.end(); )
		{
			//	座標チェック
			PosCheck( *it );
			PlayerPosCheck( *it );

			//	更新
			( *it )->Update();
		
			//	生存チェック
			bool isAlive = ( *it )->GetLifeInfo().isAlive;

			//	死亡していたらリストから削除
			if ( !isAlive )
			{
				//gameParam->SendHuntInfo((*it)->GetEnemyType());
				it = enemylist.erase( it );
				continue;
			}

			//	敵数加算
			enemyNum++;

			//	次へ
			it++;
		}

		//	一定時間ごとに敵を生成
		if ( enemyNum < ENEMY_MAX )	AddRegularTimeIntervals();
	}

	//	描画
	void	EnemyManager::Render( void )
	{
		for ( auto it = enemylist.begin(); it != enemylist.end(); it++ )
		{
			( *it )->Render();
		}
	}

	//	HP描画
	void	EnemyManager::RenderHp( void )
	{
		for ( auto it = enemylist.begin(); it != enemylist.end(); it++ )
		{
			( *it )->BarRender();
		}
	}

//-------------------------------------------------------------------------------------
//	動作関数
//-------------------------------------------------------------------------------------
	
	//	リストに追加
	void	EnemyManager::Append( const Vector3& pos, char type )
	{
		Enemy* enemy = nullptr;

		switch ( type )
		{
		case WOLF:
			enemy = new Wolf();
			//enemy->GetLifeInfo().maxLife = 80.0f;
			break;

		case MOFFU:
			enemy = new Moffu();
			//enemy->GetLifeInfo().maxLife = 20.0f;
			break;

		case SHADOW:
			enemy = new Shadow();
			break;

		default:
			return;
		}

		//	初期化
		enemy->SetEnemyType( type );
		enemy->SetObj( org[type]->Clone() );
		enemy->Initialize( lifeUpParam[type] );
		enemy->SetPos( pos );
		

		//	リストに追加
		enemylist.push_back( enemy );
	}

	//	座標チェック（ 近ければ遠ざける ）
	void	EnemyManager::PosCheck( Enemy* enemy )
	{
		for ( auto it = enemylist.begin(); it != enemylist.end(); it++ )
		{
			//	自分VS自分は除外
			if ( ( *it ) == enemy )	continue;

				//	自分→相手へのベクトル
				Vector3	vec = enemy->GetPos() - (*it)->GetPos();
				vec.y = 0.0f;
				float		length = vec.Length();

				float collisionDist = enemy->GetCollisionInfo().radius + (*it)->GetCollisionInfo().radius;
				//	近い場合は離す
				if (length < collisionDist)
				{
					//	ベクトル正規化
					vec.Normalize();

					//	離す
					(*it)->SetPos(enemy->GetPos() - vec * collisionDist);
				}
			}
		
	}

	//	プレイヤーとの座標チェック
	void	EnemyManager::PlayerPosCheck( Enemy* enemy )
	{
		//	自分→相手へのベクトル
		for (int p = 0; p < PLAYER_MAX; p++)
		{
			//	存在チェック
			if (!gameParam->GetPlayerActive(p))	continue;
			if (enemy->GetMode() == enemy->MODE::DEAD)continue;

			//	プレイヤーへのベクトルを求める
			Vector3	pPos = playerManager->GetPlayer(p)->GetPos();
			Vector3	vec = pPos - enemy->GetPos();
			vec.y = 0.0f;
			float		length = vec.Length();

			float collisionDist = enemy->GetCollisionInfo().radius + playerManager->GetPlayer(p)->GetCollisionInfo().radius;
			//	近い場合は離す
			if (length <  collisionDist)
			{
				//	ベクトル正規化
				vec.Normalize();

				//	離す
				enemy->SetPos(pPos - vec * collisionDist);
			}
			
		
		}
	}

	//	一定時間ごとに敵を生成
	void	EnemyManager::AddRegularTimeIntervals( void )
	{

		int id = gameParam->GetMyIndex();

		if ( ( int )gameManager->GetTime() % APPEND_INTERVAL != 0 )
		{
			//	生成フラグをtrueにする
			appendOK = true;
			return;
		}

		if ( !appendOK )	return;
		
		//	出現座標の設定
		float randX = random->GetFloat(-APPEND_RADIUS, APPEND_RADIUS);
		float randZ = random->GetFloat(-APPEND_RADIUS, APPEND_RADIUS);
		Vector3	appendPos = gameParam->GetPlayerParam(id).pos + Vector3(randX, 0.0f, randZ);

		float	length = Vector3(Vector3(0.0f, 0.0f, 0.0f) - appendPos).Length();
		if (length > APPEND_RADIUS_)	return;

		//	リストに追加
		Append(appendPos, random->GetInt(WOLF, SHADOW));

		//	生成フラグをfalseにする
		appendOK = false;
		
	}

	//	ライフ上昇
	void	EnemyManager::LifeUP( void )
	{
		timer->Start( TIMER_RESET );
		lifeUpParam[ENEMY_TYPE::MOFFU] += MOFFU_LIFE_UP_PARAM;
		lifeUpParam[ENEMY_TYPE::WOLF] += WOLF_LIFE_UP_PARAM;
		lifeUpParam[ENEMY_TYPE::SHADOW] += SHADOW_LIFE_UP_PARAM;
	}

//-------------------------------------------------------------------------------------
//	情報設定
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
//	情報取得
//-------------------------------------------------------------------------------------

	//	リスト取得
	list<Enemy*>&	EnemyManager::GetList( void )
	{
		return	enemylist;
	}
