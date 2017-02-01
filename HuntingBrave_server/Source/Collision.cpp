
#include	"iextreme.h"
#include	<vector>
#include	"GlobalFunction.h"
#include	"GameParam.h"
#include	"EnemyManager.h"
#include	"PlayerManager.h"
#include	"MagicManager.h"
#include	"LevelManager.h"

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

Collision*	collision = nullptr;

namespace SE_TYPE
{
	enum
	{
		ATTACK_SE,
		MAGIC_SE
	};
}

//--------------------------------------------------------------------------------------------
//	初期化・解放
//--------------------------------------------------------------------------------------------

	//	コンストラクタ
	Collision::Collision( GameParam* gameParam ) : 
		gameParam( gameParam ), collisionMesh( nullptr )
	{
		collisionMesh = new iexRayMesh( "DATA/STAGE/stage_atari.IMO" );
	}

	//	デストラクタ
	Collision::~Collision( void )
	{
		if ( collisionMesh != nullptr )
		{
			delete	collisionMesh;
			collisionMesh = nullptr;
		}
	}

//--------------------------------------------------------------------------------------------
//	当たり判定
//--------------------------------------------------------------------------------------------

	//	全当たり判定
	void	Collision::AllCollision( void )
	{
		for ( int player = 0; player < PLAYER_MAX; player++ )
		{
			//	条件が合わないものはスキップ
			bool isActive = gameParam->GetPlayerActive( player );
			if (  isActive == false )		continue;

			for ( int target = 0; target < PLAYER_MAX; target++ )
			{
				//	自分同士はスキップ、アクティブ状態でないプレイヤーはスキップ
				if ( player == target )		continue;
				if ( gameParam->GetPlayerActive( target ) == false )		continue;

				//	プレイヤーの攻撃判定
				PlayerAttackCollision( player, target );

				//	プレイヤー同士の座標調整
				PlayerPosCheck( player, target );
			}
			
			//	プレイヤーVS敵
			PlayerToEnemyCollision( player );

			//	魔法当たり判定
			MagicCollision( player );
		}
	}

	//	プレイヤー間座標調整
	void	Collision::PlayerPosCheck( int player, int target )
	{
		//	自分→相手へのベクトル
		Vector3	vec = gameParam->GetPlayerParam( player ).pos - gameParam->GetPlayerParam( target ).pos;
		vec.y = 0.0f;
		float		length = vec.Length();

		float collisionDist = 3.0f;

		//	近い場合は離す
		if ( length < collisionDist )
		{
			//	ベクトル正規化
			vec.Normalize();

			//	離す
			gameParam->GetPlayerParam( target ).pos =
				( gameParam->GetPlayerParam( player ).pos - vec * collisionDist );
		}
	}

	//	プレイヤーVSプレイヤー当たり判定
	void	Collision::PlayerAttackCollision( int player, int target )
	{
		if ( gameParam->GetLifeInfo( target ).active == false )		return;

		//	変数準備
		bool	isHit = false;
		Vector3	pos = gameParam->GetPlayerParam( target ).pos;

		//	攻撃情報取得、攻撃中でなければスキップ
		AttackInfo	attackInfo = gameParam->GetAttackInfo( player );
		if ( attackInfo.attackParam == AttackInfo::NO_ATTACK )		return;

		//	形状取得
		CollisionShape colShape1 = SetCollisionShape( attackInfo.shapeType, attackInfo.vec1, attackInfo.vec2, attackInfo.radius );
		CollisionShape colShape2 = SetCollisionShape( CAPSULE, pos, pos + Vector3( 0.0f, 2.5f, 0.0f ), 1.5f );

		//	当たり判定チェック
		isHit = CheckCollision(	colShape1, colShape2 );

		//	当たっていればライフ計算
		if ( isHit == true )
		{
			//	ヒットSE送信
			SendHitSE( SE_TYPE::ATTACK_SE );

			//	パワー計算
			int power = gameParam->GetPlayerStatus( player ).power;
			if ( attackInfo.attackParam == ATTACK2 )	power = ( int )( ( float )power * 1.2f );

			//	ダメージ計算
			int damage = power - gameParam->GetPlayerStatus( target ).defense;
			if ( damage <= 0 )	damage = 5;

			//	ライフ計算
			bool isAlive = gameParam->GetLifeInfo( target ).CulcLife( -damage );
			if( isAlive )playerManager->GetPlayer( target )->SetMode( MODE::DAMAGE );
			else
			{
				//	プレイヤーを死亡させる
				playerManager->GetPlayer( target )->SetDeath();
				
				//	経験値加算
				levelManager->CalcExpPlayer( player, target );
				levelManager->SendExp( player );

				//	キル情報を送信する
				gameParam->SendKillInfo( player, target );
			}
		}
	}

	//	プレイヤーVS敵当たり判定
	void	Collision::PlayerToEnemyCollision( int player )
	{
		//	変数準備
		bool	isHit = false;
		auto enemyList = enemyManager->GetList();

		//	攻撃情報取得、攻撃中でなければスキップ
		AttackInfo	attackInfo = gameParam->GetAttackInfo( player);
		if ( attackInfo.attackParam == AttackInfo::NO_ATTACK )		return;
		CollisionShape colShape1 = SetCollisionShape( attackInfo.shapeType, attackInfo.vec1, attackInfo.vec2, attackInfo.radius);

		for ( int i = 0; i < enemyList.size(); i++ )
		{
			//	条件に合わないものはスキップ
			if ( !enemyList[i]->GetLifeInfo().active )	continue;
			if ( !enemyList[i]->GetHitEff( player ) )	continue;

			//	形状取得
			Vector3	pos = enemyList[i]->GetPos();
			CollisionShape colShape2 = SetCollisionShape( CAPSULE, pos, pos + Vector3( 0.0f, 4.0f, 0.0f ), 1.5f );

			//	当たり判定チェック
			isHit = CheckCollision( colShape1, colShape2 );

			if ( isHit )
			{
				enemyList[i]->SetHit( player );
				enemyList[i]->CalcLife( player );
			}
		}
	}

	//	魔法当たり判定
	void	Collision::MagicCollision( int player )
	{
		//	アクティブ状態でなければスキップ
		if ( gameParam->GetLifeInfo( player ).active == false )		return;

		//	変数準備
		bool	isHit = false;
		std::vector<Magic*>	magicList = magicManager->GetList();
		Vector3	pos = gameParam->GetPlayerParam( player ).pos;
		CollisionShape	colShape2 = SetCollisionShape( SHAPE_TYPE::CAPSULE, pos, pos + Vector3( 0.0f, 2.5f, 0.0f ), 1.5f );

		//	全魔法回す
		for ( auto it = magicList.begin(); it != magicList.end(); it++ )
		{
			//	条件に合わないものはスキップ
			if ( ( *it )->GetID() == player )	continue;

			//	形状設定
			CollisionShape	colShape1;
			colShape1 = SetCollisionShape( SHAPE_TYPE::SPHERE, ( *it )->GetPos(), Vector3( 0.0f, 0.0f, 0.0f ), ( *it )->GetRadius() );

			//	敵への魔法当たり判定
			MagicCollisionToEnemy( player, colShape1 );

			//	当たり判定チェック
			isHit = CheckCollision( colShape1, colShape2 );

			//	当たっていればライフ計算
			if ( isHit == true )
			{
				//	ヒットSE送信
				SendHitSE( SE_TYPE::MAGIC_SE );

				//	ライフ計算
				int damage = gameParam->GetPlayerStatus( ( *it )->GetID() ).magicAttack - gameParam->GetPlayerStatus( player ).magicDefense;
				if ( damage <= 0 )	damage = 5;
				bool isAlive = gameParam->GetLifeInfo( player ).CulcLife( -damage );
				if ( isAlive )playerManager->GetPlayer( player )->SetMode( MODE::DAMAGE );
				else 
				{
					//	プレイヤーを死亡させる
					playerManager->GetPlayer( player )->SetDeath();

					//	キル情報を送信
					gameParam->SendKillInfo( ( *it )->GetID(), player );
				}
			}
		}
	}

	//	魔法当たり判定（ 敵 ）
	void	Collision::MagicCollisionToEnemy( int player, CollisionShape collisionShape1 )
	{
		//	変数準備
		bool	isHit = false;
		auto enemyList = enemyManager->GetList();

		for (int i = 0; i < enemyList.size(); i++)
		{
			//	条件に合わないものはスキップ
			if ( !enemyList[i]->GetLifeInfo().active )	continue;
			if ( !enemyList[i]->GetHitEff( player ) )	continue;

			//	形状取得
			Vector3	pos = enemyList[i]->GetPos();
			CollisionShape colShape2 = SetCollisionShape( CAPSULE, pos, pos + Vector3( 0.0f, 4.0f, 0.0f ), 1.5f );

			//	当たり判定チェック
			isHit = CheckCollision( collisionShape1, colShape2 );

			if ( isHit )
			{
				enemyList[i]->SetHit( player );
				enemyList[i]->CalcLife( player );
			}
		}
	}

//--------------------------------------------------------------------------------------------
//	送信
//--------------------------------------------------------------------------------------------

	//	ヒット時SE種類送信
	void	Collision::SendHitSE( char seType )
	{
		static	struct
		{
			char com;
			char responseCom;
			char hitType;
		} sendInfo;

		sendInfo.com = COMMANDS::RESPONSE;
		sendInfo.responseCom = RESPONSE_COMMAND::HIT_SE_TYPE;
		sendInfo.hitType = seType;

		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			if ( gameParam->GetPlayerActive( i ) == false )		continue;

			gameParam->send( i, ( LPSTR )&sendInfo, sizeof( sendInfo ) );
		}
	}

//--------------------------------------------------------------------------------------------
//	形状ごとの当たり判定
//--------------------------------------------------------------------------------------------

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
		}

		return	isHit;
	}

	//	形状組み合わせ
	Collision::COLLISION_PAIR	Collision::GetCollisionPair( SHAPE_TYPE type1, SHAPE_TYPE type2 )
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
		case SPHERE:
			collisionShape.sphere = Sphere( vec1, radius );
			break;

		case CAPSULE:
			collisionShape.capsule = Capsule( vec1, vec2, radius );
			break;
		}

		return	collisionShape;
	}

//--------------------------------------------------------------------------------------------
//	ステージモデルとの当たり判定
//--------------------------------------------------------------------------------------------

	//	壁判定
	bool	Collision::CheckWall( Vector3& pos, Vector3& move, float dist )
	{
		const	float	DIST = 2.0f;	//	壁との距離

		Vector3	givePos = pos;
		Vector3	giveVec( move.x, 1.0f, move.z );
		giveVec.Normalize();
		Vector3	takePos;
		
		if ( collisionMesh->RayPick( &takePos, &givePos, &giveVec, &dist ) != -1 )
		{
			float	disToWall = Vector3( Vector3( takePos.x, 0.0f, takePos.z ) - Vector3( pos.x, 0.0f, pos.z ) ).Length();
			if ( disToWall <= DIST )
			{
				//	移動量
				float	moveAmo = Vector3( move.x, 0.0f, move.z ).Length();
				
				//	プレイヤーからレイの交差点へのベクトル
				Vector3	vPtoWall( takePos - pos );
				vPtoWall.y = 0.0f;	vPtoWall.Normalize();
				giveVec.y = 0.0f;	giveVec.Normalize();
				
				//	法線の上方向を求める
				Vector3	crossUp;
				Vector3Cross( crossUp, giveVec, vPtoWall );
				crossUp.Normalize();
				
				//	法線の上方向と法線の外積から滑る方向を計算
				Vector3	crossSide;
				Vector3Cross( crossSide, crossUp, giveVec );
				crossSide.Normalize();
				
				//	法線とプレーヤーからレイの交差点へのベクトルの内積
				float	dotNP( Vector3Dot( giveVec, vPtoWall ) );
				
				//	移動量の調整
				move.x = crossSide.x * moveAmo * ( dotNP + 1.0f );
				move.z = crossSide.z * moveAmo * ( dotNP + 1.0f );

				return	true;
			}
		}

		return	false;
	}

	//	床判定
	bool	Collision::CheckDown( Vector3& pos, Vector3& move )
	{
		Vector3	givePos( pos.x, pos.y + 1.5f, pos.z );
		Vector3	giveVec( 0.0f, -1.0f, 0.0f );
		Vector3	takePos;
		float	giveDist( 100.0f );

		if ( collisionMesh->RayPick( &takePos, &givePos, &giveVec, &giveDist ) != -1 )
		{
			if ( pos.y <= takePos.y ) 
			{
				pos.y = takePos.y;
				move.y = 0.0f;
				return	true;
			}
		}
		return	false;
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




