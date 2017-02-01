
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	<vector>
#include	<map>
#include	"GameParam.h"
#include	"Sound.h"
#include	"EnemyManager.h"
#include	"NetEnemyManager.h"
#include	"PlayerManager.h"
#include	"MagicManager.h"
#include	"LevelManager.h"
#include	"DrawShape.h"
#include	"Collision.h"

//****************************************************************************************
//
//	Collisionクラス
//
//****************************************************************************************

//--------------------------------------------------------------------------------------------
//	グローバル
//--------------------------------------------------------------------------------------------

#define	PLAYER_ATTACK_HIT_DIST		2.0f

//--------------------------------------------------------------------------------------------
//	初期化・解放
//--------------------------------------------------------------------------------------------

	//	コンストラクタ
	Collision::Collision( void ) : collisionMesh( nullptr ),
		myIndex( -1 )
	{

	}

	//	デストラクタ
	Collision::~Collision( void )
	{

	}

	//	初期化
	void	Collision::Initialize( int myIndex, LPSTR fileName )
	{
		collisionMesh = new iexMesh( fileName );
		this->myIndex = myIndex;
	}

	//	解放
	void	Collision::Release( void )
	{
		SafeDelete( collisionMesh );
	}

//--------------------------------------------------------------------------------------------
//	当たり判定
//--------------------------------------------------------------------------------------------

	//	全当たり判定
	void	Collision::AllCollision( void )
	{
		//	プレイヤーの攻撃判定
		for ( int player = 0; player < PLAYER_MAX; player++ )
		{
			//	生存チェック
			if ( gameParam->GetPlayerActive( player ) == false )		continue;

			//	プレイヤー攻撃当たり判定
			PlayerAttackCollision( player );

			if ( player == myIndex )
				EnemyAttackCollision( player );
		}

		//	魔法攻撃当たり判定
		MagicCollision();
	}

	//	「プレイヤー　→　敵」剣攻撃当たり判定
	void	Collision::PlayerAttackCollision( int player )
	{
		if ( myIndex != player )return;
		//	変数準備
		list<Enemy*>	 enemyList = enemyManager->GetList();
		bool	isHit = false;

		//	攻撃情報取得、攻撃中でなければスキップ
		AttackInfo	attackInfo = gameParam->GetAttackInfo( player );
		if ( attackInfo.attackParam == ATTACK_PARAM::NO_ATTACK )	return;

		//	敵との当たり判定
		for ( auto it = enemyList.begin(); it != enemyList.end(); it++ )
		{
			//	当たり判定用情報設定
			CollisionShape hitCollisionShape = ( *it )->GetCollisionInfo().collisionShape;
			CollisionShape attackCollisionShape =
				SetCollisionShape( 
				attackInfo.shape,
				attackInfo.vec1, 
				attackInfo.vec2, 
				attackInfo.radius );

			//	当たり判定チェック
			isHit = CheckCollision( attackCollisionShape, hitCollisionShape );

			//	当たっていればライフ計算
			if ( isHit == true )
			{
				if ((*it)->GetLifeInfo().active)
				{
					sound->PlaySE(SE::ATTACK_HIT1);
					//	ライフ計算
					(*it)->SetMode((*it)->DAMAGE);
					//	ライフ計算
					(*it)->GetLifeInfo().CulcLife( -gameParam->GetPlayerStatus().power );
					(*it)->LifeCheck();
				}
			}
		}
	}

	//	敵攻撃当たり判定
	void	Collision::EnemyAttackCollision( int player )
	{
		//	プレイヤーがアクティブでないときスキップ
		if ( playerManager->GetPlayer( player )->GetLifeInfo().active == false )	return;

		//	変数準備
		list<Enemy*>	 enemyList = enemyManager->GetList();
		bool	isHit = false;

		//	全敵回す
		for ( auto it = enemyList.begin(); it != enemyList.end(); it++ )
		{
			//	攻撃情報取得、攻撃中でなければスキップ
			AttackInfo	attackInfo = ( *it )->GetAttackInfo();
			if ( attackInfo.attackParam == ATTACK_PARAM::NO_ATTACK )	continue;

			CollisionShape attackcollsion;
			attackcollsion.shapeType = attackInfo.shape;
			attackcollsion.sphere = Sphere( attackInfo.vec1,attackInfo.radius );
			
			CollisionShape playerCollision = 
				playerManager->GetPlayer( player )->GetCollisionInfo().collisionShape;

			//	当たり判定チェック
			isHit = CheckCollision(
				attackcollsion,
				playerCollision );

			//	当たっていればライフ計算
			if ( isHit == true )
			{
				//SendSmallEnemyAttackHit( ( *it )->GetEnemyType() );
			}
		}
	}

	//	大型敵攻撃当たり判定
	void	Collision::BigEnemyAttackCollision( int player )
	{
		//	変数準備
		auto	 enemyList = netEnemyManager->GetList();
		bool	isHit = false;

		//	全敵回す
		for ( int i = 0; i < ( int )enemyList.size(); i++ )
		{
			//	攻撃情報取得、攻撃中でなければスキップ
			AttackInfo	attackInfo = enemyList[i]->GetAttackInfo();
			if ( attackInfo.attackParam == ATTACK_PARAM::NO_ATTACK )	continue;

			CollisionShape attackcollsion;
			attackcollsion.shapeType = attackInfo.shape;
			attackcollsion.sphere = Sphere( attackInfo.vec1, attackInfo.radius );

			CollisionShape playerCollision =
				playerManager->GetPlayer( player )->GetCollisionInfo().collisionShape;

			//	当たり判定チェック
			isHit = CheckCollision(
				attackcollsion,
				playerCollision );

			//	当たっていればライフ計算
			if ( isHit == true )
			{
				if ( playerManager->GetPlayer( player )->GetLifeInfo().active )
				{
					//SendSmallEnemyAttackHit( );
				}
			}
		}
	}

	//	「プレイヤー　→　敵」魔法当たり判定
	void	Collision::MagicCollision( void )
	{
		//	変数準備
		bool	isHit = false;
		std::vector<Magic*>	magicList = magicManager->GetList();
		std::list<Enemy*>		enemyList = enemyManager->GetList();

		//	全魔法回す
		for ( auto it = magicList.begin(); it != magicList.end(); it++)
		{
			int id = ( *it )->GetID();
			if ( id != gameParam->GetMyIndex() )		continue;

			//	敵との当たり判定
			for ( auto enemyIt = enemyList.begin(); enemyIt != enemyList.end(); enemyIt++ )
			{
				//	当たり判定用情報設定
				CollisionShape hitCollisionShape = ( *enemyIt )->GetCollisionInfo().collisionShape;
				CollisionShape attackCollisionShape = SetCollisionShape( SHAPE_TYPE::SPHERE,
					( *it )->GetPos(), Vector3( 0.0f, 0.0f, 0.0f ), ( *it )->GetRadius() );

				//	当たり判定チェック
				isHit = CheckCollision( attackCollisionShape, hitCollisionShape );

				//	当たっていればライフ計算
				if ( isHit == true )
				{
					//	ライフ計算
					if ( ( *enemyIt )->GetLifeInfo().active )
					{
						sound->PlaySE(SE::ATTACK_HIT2);
						//	ライフ計算
						( *enemyIt )->SetMode( ( *enemyIt )->DAMAGE );
						//	ライフ計算
						( *enemyIt )->GetLifeInfo().CulcLife( -gameParam->GetPlayerStatus().magicPower );
						( *enemyIt )->LifeCheck();
					}
				}
			}
		}
	}

	//	ヒットチェック
	bool	Collision::CheckCollision( const CollisionShape& shape1, const CollisionShape& shape2 )
	{
		//	組み合わせチェック
		COLLISION_PAIR collisionPair;
		collisionPair = GetCollisionPair( shape1.shapeType, shape2.shapeType );

		bool	isHit = false;
		switch ( collisionPair )
		{
		case COLLISION_PAIR::SPHEREVSSPHERE:
			isHit = SphereVSSphere( shape1.sphere, shape2.sphere );
			break;

		case COLLISION_PAIR::SPHEREVSCAPSULE:
			isHit = CapsuleVSSphere( shape2.capsule, shape1.sphere );
			break;

		case COLLISION_PAIR::CAPSULEVSSPHERE:
			isHit = CapsuleVSSphere( shape1.capsule, shape2.sphere );
			break;

		case COLLISION_PAIR::CAPSULEVSCAPSULE:
			isHit = CapsuleVSCapsule( shape1.capsule, shape2.capsule );
			break;

		default:
			break;
		}

		return	isHit;
	}

	//	形状組み合わせ
	Collision::COLLISION_PAIR	Collision::GetCollisionPair( char type1, char type2 )
	{
		COLLISION_PAIR	collisionPair;

		switch ( type1 )
		{
		case SHAPE_TYPE::SPHERE:
			switch ( type2 )
			{
			case SHAPE_TYPE::SPHERE:
				collisionPair = COLLISION_PAIR::SPHEREVSSPHERE;
				break;
				
			case SHAPE_TYPE::CAPSULE:
				collisionPair = COLLISION_PAIR::SPHEREVSCAPSULE;
				break;
			}
			break;

		case SHAPE_TYPE::CAPSULE:
			switch ( type2 )
			{
			case SHAPE_TYPE::SPHERE:
				collisionPair = COLLISION_PAIR::CAPSULEVSSPHERE;
				break;

			case SHAPE_TYPE::CAPSULE:
				collisionPair = COLLISION_PAIR::CAPSULEVSCAPSULE;
				break;
			}
			break;
		}

		return	collisionPair;
	}

	//	当たり判定形状設定
	CollisionShape	Collision::SetCollisionShape( char shapeType, const Vector3& vec1, const Vector3& vec2, float radius )
	{
		CollisionShape	collisionShape;
		ZeroMemory( &collisionShape, sizeof( CollisionShape ) );

		//	形状タイプ設定
		collisionShape.shapeType = ( SHAPE_TYPE )shapeType;

		switch ( shapeType )
		{
		case SHAPE_TYPE::SPHERE:
			collisionShape.sphere = Sphere( vec1, radius );
			break;

		case SHAPE_TYPE::CAPSULE:
			collisionShape.capsule = Capsule( vec1, vec2, radius );
			break;
		}

		return	collisionShape;
	}

//--------------------------------------------------------------------------------------------
//	材質判定
//--------------------------------------------------------------------------------------------

	//	現在立っている位置の材質取得( テクスチャの番号 )
	int		Collision::GetMaterial( iexMesh* obj, const Vector3& pos )
	{
		Vector3	out;
		float	d = 50.0f;
		Vector3	p = pos + Vector3( 0.0f, 2.0f, 0.0f );
		Vector3	v = Vector3( 0.0f, -1.0f, 0.0f );

		//	更新
		obj->Update();
		int index = obj->RayPick( &out, &p, &v, &d );
		if ( index == -1 )	return	-1;

		DWORD*	pAttr;
		obj->GetMesh()->LockAttributeBuffer( D3DLOCK_READONLY, &pAttr );

		DWORD	mat = pAttr[index];
		obj->GetMesh()->UnlockAttributeBuffer();

		return	mat;
	}

//--------------------------------------------------------------------------------------------
//	情報送信
//--------------------------------------------------------------------------------------------

	//	大型討伐情報送信
	void	Collision::SendBigHuntInfo( char enemyType )
	{
		struct
		{
			char com;
			char infoType;
			char enemyType;
		} huntInfo;
		
		//	情報設定
		huntInfo.com = SEND_COMMAND::ENEMY_INFO;
		huntInfo.infoType = SEND_ENEMY_COMMAND::BIG_ENEMY_HUNT;
		huntInfo.enemyType = enemyType;

		//	情報送信
		gameParam->send( ( char* )&huntInfo, sizeof( huntInfo ) );
	}

	//	小型討伐情報送信
	void	Collision::SendSmallHuntInfo( char enemyType )
	{
		struct HuntInfo
		{
			char com;
			char infoType;
			char enemyType;
		} huntInfo;

		//	情報設定
		huntInfo.com = SEND_COMMAND::ENEMY_INFO;
		huntInfo.infoType = SEND_ENEMY_COMMAND::SMALL_ENEMY_HUNT;
		huntInfo.enemyType = enemyType;

		//	送信
		gameParam->send( ( char* )&huntInfo, sizeof( huntInfo ) );
	}

	//	小型攻撃ヒット情報送信
	void	Collision::SendSmallEnemyAttackHit( char enemyType )
	{
		struct HuntInfo
		{
			char com;
			char infoType;
			char enemyType;
		} huntInfo;

		//	情報設定
		huntInfo.com = SEND_COMMAND::ENEMY_INFO;
		huntInfo.infoType = SEND_ENEMY_COMMAND::PLAYER_HIT;
		huntInfo.enemyType = enemyType;

		//	送信
		gameParam->send( ( char* )&huntInfo, sizeof( huntInfo ) );
	}

//--------------------------------------------------------------------------------------------
//	当たり判定
//--------------------------------------------------------------------------------------------

	//	距離判定
	bool	Collision::DistCheck( const Vector3& p1, const Vector3& p2, float dist )
	{
		Vector3 len = p1 - p2;
		float length = len.Length();

		if ( length < dist )	return true;
		return	false;
	}

	// 点と線分の距離の平方を返す(カプセル用)
	float	Collision::DistancePointSegmentSq( const Vector3& p1, const Vector3& l1p1, const Vector3& l1p2 )
	{
		Vector3 v1 = p1 - l1p1;
		Vector3 v2 = l1p2 - l1p1;
		float v1v2 = Vector3Dot(v1, v2);
		if (v1v2 <= 0.0f) return v1.LengthSq();
		float v2v2 = v2.LengthSq();
		if (v2v2 <= v1v2) {
			Vector3 v3 = p1 - l1p2;
			return v3.LengthSq();
		}
		return v1.LengthSq() - v1v2 * v1v2 / v2v2;
	}

	// 線分と線分の距離の平方を返す(カプセル用)
	float	Collision::DistanceSegmentSegmentSq( const Vector3& l1p1, const Vector3& l1p2, const Vector3& l2p1, const Vector3& l2p2 )
	{
		// ねじれの位置の判定
		Vector3 v1 = l1p2 - l1p1;
		Vector3 v2 = l2p2 - l2p1;
		Vector3 n;
		Vector3Cross(n, v1, v2);
		float nn = n.LengthSq();
		if (nn) {
			// 平行ではない
			Vector3 v12 = l2p1 - l1p1;
			float nv12 = Vector3Dot(n, v12);
			Vector3 vd = n * (nv12 / nn);
			Vector3 q1 = l2p1 - vd;
			Vector3 q2 = l2p2 - vd;
			Vector3 p1q1 = q1 - l1p1;
			Vector3 p1q2 = q2 - l1p1;
			Vector3 r1, r2;
			Vector3Cross(r1, v1, p1q1);
			Vector3Cross(r2, v1, p1q2);
			if (Vector3Dot(r1, r2) < 0) {
				Vector3 v3 = q2 - q1;
				Vector3 q1p1 = l1p1 - q1;
				Vector3 q1p2 = l1p2 - q1;
				Vector3Cross(r1, v3, q1p1);
				Vector3Cross(r2, v3, q1p2);
				if (Vector3Dot(r1, r2) < 0) {
					// ねじれの位置
					return nv12 * nv12 / nn;
				}
			}
		}
		// ねじれじゃない位置
		return min(
			min(DistancePointSegmentSq(l1p1, l2p1, l2p2),
			DistancePointSegmentSq(l1p2, l2p1, l2p2)),
			min(DistancePointSegmentSq(l2p1, l1p1, l1p2),
			DistancePointSegmentSq(l2p2, l1p1, l1p2))
			);
	}

	//	カプセル同士の当たり判定
	bool	Collision::CapsuleVSCapsule( const Capsule& capsule1, const Capsule& capsule2 )
	{
		float length = DistanceSegmentSegmentSq( 
			capsule1.p1, capsule1.p2, capsule2.p1, capsule2.p2 );

		if ( length <= ( capsule1.r + capsule2.r ) * ( capsule1.r + capsule2.r ) )	return	true;
		return	false;
	}

	//	カプセルと球の当たり判定
	bool	Collision::CapsuleVSSphere( const Capsule& capsule, const Sphere& sphere )
	{
		float length = DistancePointSegmentSq( sphere.center, capsule.p1, capsule.p2 );

		if ( length <= ( capsule.r + sphere.r ) * ( capsule.r + sphere.r ) )	return	true;
		return	false;
	}

	//	球と球の当たり判定
	bool	Collision::SphereVSSphere( const Sphere& sphere1, const Sphere& sphere2 )
	{
		Vector3 dist = sphere2.center - sphere1.center;
		float length = dist.Length();

		if ( length <= sphere1.r + sphere2.r )	return true;
		return	false;
	}




