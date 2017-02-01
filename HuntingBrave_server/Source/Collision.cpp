
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
//	Collision�N���X
//
//****************************************************************************************

//--------------------------------------------------------------------------------------------
//	�O���[�o��
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
//	�������E���
//--------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	Collision::Collision( GameParam* gameParam ) : 
		gameParam( gameParam ), collisionMesh( nullptr )
	{
		collisionMesh = new iexRayMesh( "DATA/STAGE/stage_atari.IMO" );
	}

	//	�f�X�g���N�^
	Collision::~Collision( void )
	{
		if ( collisionMesh != nullptr )
		{
			delete	collisionMesh;
			collisionMesh = nullptr;
		}
	}

//--------------------------------------------------------------------------------------------
//	�����蔻��
//--------------------------------------------------------------------------------------------

	//	�S�����蔻��
	void	Collision::AllCollision( void )
	{
		for ( int player = 0; player < PLAYER_MAX; player++ )
		{
			//	����������Ȃ����̂̓X�L�b�v
			bool isActive = gameParam->GetPlayerActive( player );
			if (  isActive == false )		continue;

			for ( int target = 0; target < PLAYER_MAX; target++ )
			{
				//	�������m�̓X�L�b�v�A�A�N�e�B�u��ԂłȂ��v���C���[�̓X�L�b�v
				if ( player == target )		continue;
				if ( gameParam->GetPlayerActive( target ) == false )		continue;

				//	�v���C���[�̍U������
				PlayerAttackCollision( player, target );

				//	�v���C���[���m�̍��W����
				PlayerPosCheck( player, target );
			}
			
			//	�v���C���[VS�G
			PlayerToEnemyCollision( player );

			//	���@�����蔻��
			MagicCollision( player );
		}
	}

	//	�v���C���[�ԍ��W����
	void	Collision::PlayerPosCheck( int player, int target )
	{
		//	����������ւ̃x�N�g��
		Vector3	vec = gameParam->GetPlayerParam( player ).pos - gameParam->GetPlayerParam( target ).pos;
		vec.y = 0.0f;
		float		length = vec.Length();

		float collisionDist = 3.0f;

		//	�߂��ꍇ�͗���
		if ( length < collisionDist )
		{
			//	�x�N�g�����K��
			vec.Normalize();

			//	����
			gameParam->GetPlayerParam( target ).pos =
				( gameParam->GetPlayerParam( player ).pos - vec * collisionDist );
		}
	}

	//	�v���C���[VS�v���C���[�����蔻��
	void	Collision::PlayerAttackCollision( int player, int target )
	{
		if ( gameParam->GetLifeInfo( target ).active == false )		return;

		//	�ϐ�����
		bool	isHit = false;
		Vector3	pos = gameParam->GetPlayerParam( target ).pos;

		//	�U�����擾�A�U�����łȂ���΃X�L�b�v
		AttackInfo	attackInfo = gameParam->GetAttackInfo( player );
		if ( attackInfo.attackParam == AttackInfo::NO_ATTACK )		return;

		//	�`��擾
		CollisionShape colShape1 = SetCollisionShape( attackInfo.shapeType, attackInfo.vec1, attackInfo.vec2, attackInfo.radius );
		CollisionShape colShape2 = SetCollisionShape( CAPSULE, pos, pos + Vector3( 0.0f, 2.5f, 0.0f ), 1.5f );

		//	�����蔻��`�F�b�N
		isHit = CheckCollision(	colShape1, colShape2 );

		//	�������Ă���΃��C�t�v�Z
		if ( isHit == true )
		{
			//	�q�b�gSE���M
			SendHitSE( SE_TYPE::ATTACK_SE );

			//	�p���[�v�Z
			int power = gameParam->GetPlayerStatus( player ).power;
			if ( attackInfo.attackParam == ATTACK2 )	power = ( int )( ( float )power * 1.2f );

			//	�_���[�W�v�Z
			int damage = power - gameParam->GetPlayerStatus( target ).defense;
			if ( damage <= 0 )	damage = 5;

			//	���C�t�v�Z
			bool isAlive = gameParam->GetLifeInfo( target ).CulcLife( -damage );
			if( isAlive )playerManager->GetPlayer( target )->SetMode( MODE::DAMAGE );
			else
			{
				//	�v���C���[�����S������
				playerManager->GetPlayer( target )->SetDeath();
				
				//	�o���l���Z
				levelManager->CalcExpPlayer( player, target );
				levelManager->SendExp( player );

				//	�L�����𑗐M����
				gameParam->SendKillInfo( player, target );
			}
		}
	}

	//	�v���C���[VS�G�����蔻��
	void	Collision::PlayerToEnemyCollision( int player )
	{
		//	�ϐ�����
		bool	isHit = false;
		auto enemyList = enemyManager->GetList();

		//	�U�����擾�A�U�����łȂ���΃X�L�b�v
		AttackInfo	attackInfo = gameParam->GetAttackInfo( player);
		if ( attackInfo.attackParam == AttackInfo::NO_ATTACK )		return;
		CollisionShape colShape1 = SetCollisionShape( attackInfo.shapeType, attackInfo.vec1, attackInfo.vec2, attackInfo.radius);

		for ( int i = 0; i < enemyList.size(); i++ )
		{
			//	�����ɍ���Ȃ����̂̓X�L�b�v
			if ( !enemyList[i]->GetLifeInfo().active )	continue;
			if ( !enemyList[i]->GetHitEff( player ) )	continue;

			//	�`��擾
			Vector3	pos = enemyList[i]->GetPos();
			CollisionShape colShape2 = SetCollisionShape( CAPSULE, pos, pos + Vector3( 0.0f, 4.0f, 0.0f ), 1.5f );

			//	�����蔻��`�F�b�N
			isHit = CheckCollision( colShape1, colShape2 );

			if ( isHit )
			{
				enemyList[i]->SetHit( player );
				enemyList[i]->CalcLife( player );
			}
		}
	}

	//	���@�����蔻��
	void	Collision::MagicCollision( int player )
	{
		//	�A�N�e�B�u��ԂłȂ���΃X�L�b�v
		if ( gameParam->GetLifeInfo( player ).active == false )		return;

		//	�ϐ�����
		bool	isHit = false;
		std::vector<Magic*>	magicList = magicManager->GetList();
		Vector3	pos = gameParam->GetPlayerParam( player ).pos;
		CollisionShape	colShape2 = SetCollisionShape( SHAPE_TYPE::CAPSULE, pos, pos + Vector3( 0.0f, 2.5f, 0.0f ), 1.5f );

		//	�S���@��
		for ( auto it = magicList.begin(); it != magicList.end(); it++ )
		{
			//	�����ɍ���Ȃ����̂̓X�L�b�v
			if ( ( *it )->GetID() == player )	continue;

			//	�`��ݒ�
			CollisionShape	colShape1;
			colShape1 = SetCollisionShape( SHAPE_TYPE::SPHERE, ( *it )->GetPos(), Vector3( 0.0f, 0.0f, 0.0f ), ( *it )->GetRadius() );

			//	�G�ւ̖��@�����蔻��
			MagicCollisionToEnemy( player, colShape1 );

			//	�����蔻��`�F�b�N
			isHit = CheckCollision( colShape1, colShape2 );

			//	�������Ă���΃��C�t�v�Z
			if ( isHit == true )
			{
				//	�q�b�gSE���M
				SendHitSE( SE_TYPE::MAGIC_SE );

				//	���C�t�v�Z
				int damage = gameParam->GetPlayerStatus( ( *it )->GetID() ).magicAttack - gameParam->GetPlayerStatus( player ).magicDefense;
				if ( damage <= 0 )	damage = 5;
				bool isAlive = gameParam->GetLifeInfo( player ).CulcLife( -damage );
				if ( isAlive )playerManager->GetPlayer( player )->SetMode( MODE::DAMAGE );
				else 
				{
					//	�v���C���[�����S������
					playerManager->GetPlayer( player )->SetDeath();

					//	�L�����𑗐M
					gameParam->SendKillInfo( ( *it )->GetID(), player );
				}
			}
		}
	}

	//	���@�����蔻��i �G �j
	void	Collision::MagicCollisionToEnemy( int player, CollisionShape collisionShape1 )
	{
		//	�ϐ�����
		bool	isHit = false;
		auto enemyList = enemyManager->GetList();

		for (int i = 0; i < enemyList.size(); i++)
		{
			//	�����ɍ���Ȃ����̂̓X�L�b�v
			if ( !enemyList[i]->GetLifeInfo().active )	continue;
			if ( !enemyList[i]->GetHitEff( player ) )	continue;

			//	�`��擾
			Vector3	pos = enemyList[i]->GetPos();
			CollisionShape colShape2 = SetCollisionShape( CAPSULE, pos, pos + Vector3( 0.0f, 4.0f, 0.0f ), 1.5f );

			//	�����蔻��`�F�b�N
			isHit = CheckCollision( collisionShape1, colShape2 );

			if ( isHit )
			{
				enemyList[i]->SetHit( player );
				enemyList[i]->CalcLife( player );
			}
		}
	}

//--------------------------------------------------------------------------------------------
//	���M
//--------------------------------------------------------------------------------------------

	//	�q�b�g��SE��ޑ��M
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
//	�`�󂲂Ƃ̓����蔻��
//--------------------------------------------------------------------------------------------

	//	�q�b�g�`�F�b�N
	bool	Collision::CheckCollision( const CollisionShape& shape1, const CollisionShape& shape2 )
	{
		//	�g�ݍ��킹�`�F�b�N
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

	//	�`��g�ݍ��킹
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

	//	�����蔻��`��ݒ�
	CollisionShape	Collision::SetCollisionShape( char shapeType, const Vector3& vec1, const Vector3& vec2, float radius )
	{
		CollisionShape	collisionShape;
		ZeroMemory( &collisionShape, sizeof( CollisionShape ) );

		//	�`��^�C�v�ݒ�
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
//	�X�e�[�W���f���Ƃ̓����蔻��
//--------------------------------------------------------------------------------------------

	//	�ǔ���
	bool	Collision::CheckWall( Vector3& pos, Vector3& move, float dist )
	{
		const	float	DIST = 2.0f;	//	�ǂƂ̋���

		Vector3	givePos = pos;
		Vector3	giveVec( move.x, 1.0f, move.z );
		giveVec.Normalize();
		Vector3	takePos;
		
		if ( collisionMesh->RayPick( &takePos, &givePos, &giveVec, &dist ) != -1 )
		{
			float	disToWall = Vector3( Vector3( takePos.x, 0.0f, takePos.z ) - Vector3( pos.x, 0.0f, pos.z ) ).Length();
			if ( disToWall <= DIST )
			{
				//	�ړ���
				float	moveAmo = Vector3( move.x, 0.0f, move.z ).Length();
				
				//	�v���C���[���烌�C�̌����_�ւ̃x�N�g��
				Vector3	vPtoWall( takePos - pos );
				vPtoWall.y = 0.0f;	vPtoWall.Normalize();
				giveVec.y = 0.0f;	giveVec.Normalize();
				
				//	�@���̏���������߂�
				Vector3	crossUp;
				Vector3Cross( crossUp, giveVec, vPtoWall );
				crossUp.Normalize();
				
				//	�@���̏�����Ɩ@���̊O�ς��犊��������v�Z
				Vector3	crossSide;
				Vector3Cross( crossSide, crossUp, giveVec );
				crossSide.Normalize();
				
				//	�@���ƃv���[���[���烌�C�̌����_�ւ̃x�N�g���̓���
				float	dotNP( Vector3Dot( giveVec, vPtoWall ) );
				
				//	�ړ��ʂ̒���
				move.x = crossSide.x * moveAmo * ( dotNP + 1.0f );
				move.z = crossSide.z * moveAmo * ( dotNP + 1.0f );

				return	true;
			}
		}

		return	false;
	}

	//	������
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
//	�����蔻��
//--------------------------------------------------------------------------------------------

	//	��������
	bool	Collision::DistCheck( const Vector3& p1, const Vector3& p2, float dist )
	{
		Vector3 len = p1 - p2;
		float length = len.Length();

		if ( length < dist )	return true;
		return	false;
	}

	// �_�Ɛ����̋����̕�����Ԃ�(�J�v�Z���p)
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

	// �����Ɛ����̋����̕�����Ԃ�(�J�v�Z���p)
	float	Collision::DistanceSegmentSegmentSq( const Vector3& l1p1, const Vector3& l1p2, const Vector3& l2p1, const Vector3& l2p2 )
	{
		// �˂���̈ʒu�̔���
		Vector3 v1 = l1p2 - l1p1;
		Vector3 v2 = l2p2 - l2p1;
		Vector3 n;
		Vector3Cross(n, v1, v2);
		float nn = n.LengthSq();
		if (nn) {
			// ���s�ł͂Ȃ�
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
					// �˂���̈ʒu
					return nv12 * nv12 / nn;
				}
			}
		}
		// �˂��ꂶ��Ȃ��ʒu
		return min(
			min(DistancePointSegmentSq(l1p1, l2p1, l2p2),
			DistancePointSegmentSq(l1p2, l2p1, l2p2)),
			min(DistancePointSegmentSq(l2p1, l1p1, l1p2),
			DistancePointSegmentSq(l2p2, l1p1, l1p2))
			);
	}

	//	�J�v�Z�����m�̓����蔻��
	bool	Collision::CapsuleVSCapsule( const Capsule& capsule1, const Capsule& capsule2 )
	{
		float length = DistanceSegmentSegmentSq( 
			capsule1.p1, capsule1.p2, capsule2.p1, capsule2.p2 );

		if ( length <= ( capsule1.r + capsule2.r ) * ( capsule1.r + capsule2.r ) )	return	true;
		return	false;
	}

	//	�J�v�Z���Ƌ��̓����蔻��
	bool	Collision::CapsuleVSSphere( const Capsule& capsule, const Sphere& sphere )
	{
		float length = DistancePointSegmentSq( sphere.center, capsule.p1, capsule.p2 );

		if ( length <= ( capsule.r + sphere.r ) * ( capsule.r + sphere.r ) )	return	true;
		return	false;
	}

	//	���Ƌ��̓����蔻��
	bool	Collision::SphereVSSphere( const Sphere& sphere1, const Sphere& sphere2 )
	{
		Vector3 dist = sphere2.center - sphere1.center;
		float length = dist.Length();

		if ( length <= sphere1.r + sphere2.r )	return true;
		return	false;
	}




