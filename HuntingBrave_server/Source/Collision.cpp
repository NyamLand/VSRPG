
#include	"iextreme.h"
#include	<vector>
#include	"GameParam.h"
#include	"EnemyManager.h"
#include	"PlayerManager.h"
#include	"MagicManager.h"
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

//--------------------------------------------------------------------------------------------
//	�������E���
//--------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	Collision::Collision( GameParam* gameParam ) : gameParam( gameParam )
	{
		
	}

	//	�f�X�g���N�^
	Collision::~Collision( void )
	{

	}

//--------------------------------------------------------------------------------------------
//	�����蔻��
//--------------------------------------------------------------------------------------------

	//	�S�����蔻��
	void	Collision::AllCollision( void )
	{
		//	�v���C���[�̍U������
		PlayerAttackCollision();

		//	���@�����蔻��
		MagicCollision();
	}

	//	�v���C���[�U�������蔻��
	void	Collision::PlayerAttackCollision( void )
	{
		//	�ϐ�����
		bool	isHit = false;

		//	�S�v���C���[��
		for ( int i = 0; i < PLAYER_MAX; i++ )
		{
			//	����������Ȃ����̂̓X�L�b�v
			if ( gameParam->GetPlayerActive( i ) == false )		continue;

			//	�U�����擾�A�U�����łȂ���΃X�L�b�v
			AttackInfo	attackInfo = gameParam->GetAttackInfo( i );
			if ( attackInfo.attackParam == AttackInfo::NO_ATTACK )		continue;

			//	�G�Ƃ̓����蔻��
			for ( int j = 0; j < PLAYER_MAX; j++ )
			{
				//	�������m�̓X�L�b�v�A�A�N�e�B�u��ԂłȂ��v���C���[�̓X�L�b�v
				if( j == i )		continue;
				if ( gameParam->GetPlayerActive( j ) == false )		continue;
				bool	active = gameParam->GetLifeInfo( j ).active;
				if ( active == false )		continue;	

				//	�`��擾
				CollisionShape	colShape1, colShape2;
				colShape1 = SetCollisionShape( attackInfo.shapeType, attackInfo.vec1, attackInfo.vec2, attackInfo.radius );
				Vector3	pos = gameParam->GetPlayerParam( j ).pos;
				colShape2 = SetCollisionShape( CAPSULE, pos, pos + Vector3( 0.0f, 2.5f, 0.0f ), 1.5f );

				//	�����蔻��`�F�b�N
				isHit = CheckCollision(	colShape1, colShape2 );

				//	�������Ă���΃��C�t�v�Z
				if ( isHit == true )
				{
					//	���C�t�v�Z
					gameParam->GetLifeInfo( j ).CulcLife( -attackInfo.power );
					playerManager->GetPlayer( j )->SetMode( MODE::DAMAGE );
				}
			}
		}
	}

	//	���@�����蔻��
	void	Collision::MagicCollision( void )
	{
		//	�ϐ�����
		bool	isHit = false;
		std::vector<Magic*>	magicList = magicManager->GetList();

		//	�S���@��
		for ( auto it = magicList.begin(); it != magicList.end(); it++ )
		{
			for ( int p = 0; p < PLAYER_MAX; p++ )
			{
				//	�����ɍ���Ȃ����̂̓X�L�b�v
				if ( ( *it )->GetID() == p )	continue;
				if ( gameParam->GetPlayerActive( p ) == false )		continue;
				bool	active = gameParam->GetLifeInfo( p ).active;
				if ( active == false )		continue;

				//	�`��ݒ�
				CollisionShape	colShape1, colShape2;
				colShape1 = SetCollisionShape( SHAPE_TYPE::SPHERE, 
					( *it )->GetPos(), Vector3( 0.0f, 0.0f, 0.0f ), ( *it )->GetRadius() );
				Vector3	pos = gameParam->GetPlayerParam( p ).pos;
				colShape2 = SetCollisionShape( SHAPE_TYPE::CAPSULE, pos, pos + Vector3( 0.0f, 2.5f, 0.0f ), 1.5f );

				//	�����蔻��`�F�b�N
				isHit = CheckCollision( colShape1, colShape2 );

				//	�������Ă���΃��C�t�v�Z
				if ( isHit == true )
				{
					//	���C�t�v�Z
					gameParam->GetLifeInfo( p ).CulcLife( -gameParam->GetAttackInfo( p ).power );
					playerManager->GetPlayer( p )->SetMode( MODE::DAMAGE );
				}
			}
		}
	}

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
//	�ގ�����
//--------------------------------------------------------------------------------------------

	//	���ݗ����Ă���ʒu�̍ގ��擾( �e�N�X�`���̔ԍ� )
	int		Collision::GetMaterial( iexMesh* obj, const Vector3& pos )
	{
		Vector3	out;
		float	d = 50.0f;
		Vector3	p = pos + Vector3( 0.0f, 2.0f, 0.0f );
		Vector3	v = Vector3( 0.0f, -1.0f, 0.0f );

		//	�X�V
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




